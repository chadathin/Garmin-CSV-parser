#include "parselib.h"
#include "actstr.h"


int main(int argc, char *argv[]) {

    FILE *in; 
    int lthr = -1;
    int data_point;
    char buff[MAX_LINE] = {0};

    char *read;
    char *tok;

    char act_type[TOK_SIZE];
    time_t act_date;
    double act_dist, act_time;
    int act_hr;
    int nodes = 0;

    Activity *head = NULL;

    // Expects two CL args: .csv filename and lthr
    if (argc != 3 || ((lthr = atoi(argv[2])) == 0)) {
        WrongArg();
        exit(1);
    }

    // Make sure at least a POSITIVE number is entered
    if (lthr < 1) {
        WrongArg();
        exit(1);
    }

    // open activities file
    if ((in = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "%s:%s\n", argv[1], strerror(errno));
        fflush(stderr);
        exit(2);
    }

    // do this first one to get it out of the way 
    if ((read = fgets(buff, MAX_LINE, in)) == NULL) {                 
        fprintf(stderr, "%s", "Unable to read line\n");
        exit(2);
    };             

    // Now, start reading line after line
    while(fgets(buff, MAX_LINE, in)) {

        data_point = 0;
        // memset(act_date, '\0', TOK_SIZE);
        memset(act_type, '\0', TOK_SIZE);

        if (read == NULL) {
            fprintf(stderr, "%s", "Unable to read line\n");
            exit(2);
        };
        
        // gets activity type ("Running, Cycling, Indoor Running")
        tok = strtok(buff, ",");
        if (!strcmp(tok, "Running")) {      // make sure we're reading only running activies

            strcpy(act_type, tok);
            data_point++;

            while (data_point < 8 && (tok = strtok(NULL, ",")) != NULL) {

                // If we ran into a wierd comma, advance tok by one
                if (strlen(tok) < 3) {
                    tok = strtok(NULL, ",");
                }

                // otherwise, save current tok if needed
                switch(data_point) {
                    case 1:                 // date
                        
                        act_date = get_epoch(tok);
                        // printf("NODE[%d]: DATA POINT[%d]: TOK[%s] EPOCH -> %ld\n", nodes, data_point, tok, act_date);
                        // strncpy(act_date, tok, 10);
                        data_point++;
                        break;
                    case 4:                 // distance
                        stripper(tok);
                        act_dist = atof(tok);
                        // printf("NODE[%d]: DATA POINT[%d]: DISTANCE -> %f\n", nodes, data_point, act_dist);
                        data_point++;
                        break;
                    case 6:                 // time
                        stripper(tok);
                        act_time = decTime(tok);
                        // printf("NODE[%d]: DATA POINT[%d]: DURATION -> %f\n", nodes, data_point, act_time);
                        data_point++;
                        break;
                    case 7:                 // avg hr
                        stripper(tok);
                        act_hr = atoi(tok);
                        // printf("NODE[%d]: DATA POINT[%d]: AVG HR -> %d\n", nodes, data_point, act_hr);
                        data_point++;
                        break;
                    default:
                        data_point++;
                };
            }

            add_node(&head, act_type, act_date, act_dist, act_time, act_hr, lthr);
            nodes++;
        }
    };


    // close activities file
    fclose(in);

		print_list(head);
	
    // reverse our activities linked list 
    // so it's in chronological order
    reverse_ll(&head);

    
    // So now, we have a linked list of activity nodes
    // First, I'd like to find the number of dates covered
    int days = num_days(head);
    
    // If there aren't about dates to calculate 
    // a chronic training status
    if (days < CHRONIC_SIZE) {
        fprintf(stderr, "Must have at least %d data points.\n", CHRONIC_SIZE);
        fflush(stderr);
        free_activity_list(head);
        exit(3);
    }
    // Combine times from the same date
    int *times = consolidate_time(head, days);

    // Then, I'd like to combine RSS scores from the same date
    int *stresses = consolidate_rss(head, days);
		print_array(stresses, days, 0);

    
    // Don't need linked list anymore
    free_activity_list(head);


    // Now, we have an array of RSSs for EACH DAY in the CSV
    // They are in chronological order (i[0] = OLDEST, i[n-1] = NEWEST)

    // We can calculate chronic and acute RSS loads to find RSB
    int wdays = days-CHRONIC_SIZE+1;

    // Tabulate Running Stress Balances
    int *rsbs = rsb(stresses, CHRONIC_SIZE, ACUTE_SIZE, days);

    // Tabulate sliding window sums of weekly time
    int *tbal = sliding_window_sum(ACUTE_SIZE, times, days);

    // Get date and time to creat filename
    char *fname = get_date_time();

    // Add file type
    strcat(fname, ".rsb");

    // Open output file
    FILE *output = fopen(fname, "w");
    int nwritten;

    // Output header
    nwritten = fprintf(output, "%s:\n", get_date_time());
    nwritten = fprintf(output, "LTHR: %d\n\n", lthr);

    // Output stress scores
    nwritten = fprintf(output, "Running Stress Scores (oldest -> newest):\n");
    print_to_file(stresses, days, output);
    
    // Output Running Stress Balances
    nwritten = fprintf(output, "\nRunning Stress Balances (oldest -> newest):\n");
    print_to_file(rsbs, wdays, output);

    // Output sliding window times
    nwritten = fprintf(output, "\nSeven-Day Sliding Window of Times (oldest -> newest):\n");
    print_to_file(tbal, (days-ACUTE_SIZE+1), output);

    // close output file
    fclose(output);


    free(times);
    free(stresses);
    free(rsbs);
    free(tbal);
    
    


    return 0;
}