#include "parselib.h"
#include "actstr.h"

Activity *make_node(char *type, char *date, double dist, double time, int hr) {
    // A function to make a new Activity struct
    // Returns pointer to the new Activity struct created
    Activity *new = malloc(sizeof(Activity));
    new->type = type;
    new->date = date;
    new->dist = dist;
    new->time = time;
    new->hr = hr;
    new->next = NULL;

    return new;

}

void print_activity(Activity *out) {
    printf("============= ACTIVITY =============\n");
    printf("Type: %s\n", out->type);
    printf("Date: %s\n", out->date);
    printf("Dist: %f\n", out->dist);
    printf("Time: %f\n", out->time);
    printf("HR: %d\n", out->hr);
    printf("\n");
}

void free_activity(Activity *done) {
    free(done);
}

void free_activity_list(Activity *curr) {
    Activity *n = curr->next;
    while (curr->next != NULL) {
        free_activity(curr);
        curr = n;
        n = curr->next;
    }
}