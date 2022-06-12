#include "parselib.h"
#include "actstr.h"

void print_activity(Activity *out) {
    printf("[%s, %ld, %f, %f, %d, %d]", out->type, out->date, out->dist, out->time, out->hr, out->rss);
    // printf("\n");
}

void free_activity(Activity *done) {
    free(done->type);
    // free(done->date);
    free(done);
}

void free_activity_list(Activity *curr) {
    while (curr != NULL) {
        free_activity(curr);
        
        curr = curr->next;
    }
}

void add_node(Activity **head, char *act_type, time_t act_date, double act_dist, double act_time, int act_hr, int lacthr) {
    
    Activity *new = (Activity *)malloc(sizeof(Activity));
    
    new->type = calloc(strlen(act_type)+1, sizeof(char));
    strcpy(new->type, act_type);
    

    new->date = act_date;
    new->dist = act_dist;
    new->time = act_time;
    new->hr = act_hr;
    new->rss = calc_rss(act_hr, lacthr, act_time);
    new->next = NULL;
    
    // If the list is empty, add node at the head
    if (*head == NULL) {
        *head = new;
    } else {

        // otherwise, find the last node

        Activity *last = *head;
        while (last->next != NULL) {
            
            last = last->next;
        }
        last->next = new;
    }


}

void print_list(Activity *curr) {
    int i = 0;
    while (curr != NULL) {
        printf("NODE[%d]:", i);
        print_activity(curr);
        printf("\n");
        i++;
        curr = curr->next;
    }
}

time_t num_days(Activity *start) {
    time_t first;
    time_t last;

    time_t diff;
    double days;

    first = start->date;
    printf("First: %ld\n", first);
    while (start->next != NULL) {
        start = start->next;
    }
    last = start->date;
    printf("Last: %ld\n", last);

    diff = first - last;
    printf("Diff: %ld\n", diff);
    days = (double)diff / (double)ONE_DAY;
    printf("Days Calc: %f\n", days);
    return days+1;

}


int *consolidate(Activity *start, int size){
    int index = 0;
    int stress_score = 0;
    int *out = (int *)malloc(size*sizeof(int));
    memset(out, 0, size*sizeof(int));
    Activity *curr = start;
    time_t diff = 0;

    // Traverse the list
    while (curr->next != NULL) {
        stress_score += curr->rss;
        // check if the next day is the same day
        diff = (curr->date - curr->next->date)/(time_t)86400;
        switch (diff) {
            case 0:     // "tomorrow" is actually the same day
                curr = curr->next;
                break;
            default:    // one or more days have passed
                out[index] = stress_score;
                index += diff;
                stress_score = 0;
                curr = curr->next;
                break;


        }
        

        // add 
        // stress_score += start->rss;
    }

        out[index] = (stress_score += curr->rss);
    
    return out;

}