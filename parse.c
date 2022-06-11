#include "parselib.h"
#include "actstr.h"


int main(int argc, char *argv[]) {

    FILE *in; 
    int lthr = -1;
    int lines;
    int data_point;
    char buff[MAX_LINE] = {0};
    char *read;
    char *tok;
    char act_type[TOK_SIZE], act_date[TOK_SIZE];
    double act_dist, act_time;
    int act_hr;

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
    if (read = fgets(buff, MAX_LINE, in)) {                 
        if (read == NULL) {
            fprintf(stderr, "%s", "Unable to read line\n");
            exit(2);
        };
    };             

    // Now, start reading line after line
    while(read = fgets(buff, MAX_LINE, in)) {

        data_point = 0;
        memset(act_date, '\0', TOK_SIZE);
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
                        strncpy(act_date, tok, 10);
                        data_point++;
                        break;
                    case 4:                 // distance
                        stripper(tok);
                        act_dist = atof(tok);
                        data_point++;
                        break;
                    case 6:                 // time
                        stripper(tok);
                        act_time = decTime(tok);
                        data_point++;
                        break;
                    case 7:                 // avg hr
                        stripper(tok);
                        act_hr = atoi(tok);
                        data_point++;
                        break;
                    default:
                        data_point++;
                };

                
            }
            Activity *new = make_node(act_type, act_date, act_dist, act_time, act_hr);
            print_activity(new);
        

        }

            
    };


    // close activities file
    fclose(in);

    return 0;
}