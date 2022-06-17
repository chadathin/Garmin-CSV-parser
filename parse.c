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
    // So now, we have a linked list of activity nodes
    // First, I'd like to find the number of dates covered
    int days = num_days(head);
    printf("DAYS: %d\n", days);
    if (days < CHRONIC_SIZE) {
        fprintf(stderr, "Must have at least %d data points.\n", CHRONIC_SIZE);
        fflush(stderr);
        exit(3);
    }

    // Then, I'd like to combine RSS scores from the same date
    int *stresses = consolidate_rss(head, days);
    printf("STRESSES\n");
    print_array(stresses, days, 0);

    // Now, we have an array of RSSs for EACH DAY in the CSV
    // They are in reverse chronological order (i[0] = MOST RECENT, i[n-1] = OLDEST)
    // so we need to reverse them, so they ARE in chronoligical order
    printf("\n\nREV STRESSES:\n");
    reverse(stresses, days);
    print_array(stresses, days, 0);

    // We can calculate chronic and acute RSS loads to find RSB

    int wdays = days-CHRONIC_SIZE+1;
    int *chronics = sliding_window_average(CHRONIC_SIZE, stresses, days);
    int *acutes = sliding_window_average(ACUTE_SIZE, stresses, days);
    int *rsbs = (int *)malloc((wdays)*sizeof(int));

    int i;
    for (i = 0; i < wdays; i++) {
        *(rsbs + i) = *(chronics + i) - *(acutes + i);
    }

    printf("\n\nRSBS\n");
    print_array(rsbs, wdays, 0);



    int *time_arr = consolidate_time(head, days);
    
    reverse(time_arr, days);
    printf("\n\nREV TIMES:\n");
    print_array(time_arr, days, 1);
    printf("wdays: %d\n", wdays);
    int *times = sliding_window_sum(ACUTE_SIZE, time_arr, days);
    
    printf("\n\nSLIDING TIMES:");

    print_array(times, wdays, 0);


    

    


    

    

    
   

    free_activity_list(head);
    free(stresses);
    free(chronics);
    free(acutes);
    free(rsbs);


    return 0;
}