#ifndef ACTIVITY_STRUCT_H
#define ACTIVITY_STRUCT_H

#include "parselib.h"
#define ONE_DAY 86400

#endif

// Activity structure
struct Activity {
    char *type;
    time_t date;
    double dist;
    double time;
    int hr;
    int rss;
    struct Activity *next;

};

typedef struct Activity Activity;

// Function Prototypes
Activity *make_node(char *, char *, double, double, int);
void print_activity(Activity *);
void free_activity(Activity *);
void free_activity_list(Activity *);
void add_node(Activity **head, char *act_type, time_t date, double act_dist, double act_time, int act_hr, int lacthr);
void print_list(Activity *); 
int *consolidate_rss(Activity *start, int size);
int *consolidate_time(Activity *start, int size);
time_t num_days(Activity *start);
void reverse_ll(Activity **start);