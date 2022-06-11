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

// Prototypes
void hello();
int gen_random();
void WrongArg();

int count_lines(char *);
void stripper(char []);
double decTime(char []);