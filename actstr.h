#ifndef ACTIVITY_STRUCT_H
#define ACTIVITY_STRUCT_H

#include "parselib.h"

#endif

// Activity structure
struct Activity {
    char *type;
    char *date;
    double dist;
    double time;
    int hr;
    struct Activity *next;

};

typedef struct Activity Activity;

// Function Prototypes
Activity *make_node(char *, char *, double, double, int);
void print_activity(Activity *);
void free_activity(Activity *);
void free_activity_list(Activity *);
