#include "parselib.h"
#include "actstr.h"

void print_activity(Activity *out) {
    printf("[%s, %s, %f, %f, %d, %d]", out->type, out->date, out->dist, out->time, out->hr, out->rss);
    // printf("\n");
}

void free_activity(Activity *done) {
    free(done->type);
    free(done->date);
    free(done);
}

void free_activity_list(Activity *curr) {
    while (curr != NULL) {
        free_activity(curr);
        
        curr = curr->next;
    }
}

void add_node(Activity **head, char *act_type, char *act_date, double act_dist, double act_time, int act_hr, int lacthr) {
    
    Activity *new = (Activity *)malloc(sizeof(Activity));

    new->type = calloc(strlen(act_type)+1, sizeof(char));
    strcpy(new->type, act_type);
    

    new->date = calloc(strlen(act_date)+1, sizeof(char));
    strncpy(new->date, act_date, 10);
    new->dist = act_dist;
    new->time = act_time;
    new->hr = act_hr;
    new->rss = calc_rss(act_hr, lacthr, act_time);
    
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