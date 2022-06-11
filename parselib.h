#ifndef PARSELIB_H
#define PARSELIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <errno.h>
#include <math.h>
#include <time.h>

#endif

// Activity structure
typedef struct ActivityTag {
    char *type;
    char *date;
    double dist;
    double time;
    int hr;
    struct Activity *next;

} Activity;

// Prototypes
void hello();
int gen_random();
void WrongArg();