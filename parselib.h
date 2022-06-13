#ifndef PARSELIB_H
#define PARSELIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <errno.h>
#include <math.h>
#include <time.h>


#define MAX_LINE 1024
#define TOK_SIZE 16

#endif

// #include "actstr.h"

// Prototypes
void hello();
int gen_random();
void WrongArg();

int count_lines(char *);
void stripper(char []);
double decTime(char []);
int calc_rss(int, int, double);

void print_array(int *arr, int size, int filter);
time_t get_epoch(char *date);
void reverse(int *list, int len);