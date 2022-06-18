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
#define CHRONIC_SIZE 42
#define ACUTE_SIZE  7

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
void fprint_array(float *arr, int size, int filter);
time_t get_epoch(char *date);
void reverse(int *list, int len);
int *sliding_window_average(int wsize, int *arr, int asize);
int *sliding_window_sum(int wsize, int *arr, int asize);
int *rsb(int *stress, int c_win, int a_win, int size);