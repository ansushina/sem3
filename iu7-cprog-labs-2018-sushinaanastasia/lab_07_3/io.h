#ifndef __IO_H__
#define __IO_H__

#include<stdio.h>

int count_n(FILE *f);

int read_array(FILE *f, int *pa, int n);

int read_a(FILE *f, int **pa, int **pe);

void print_array(FILE *f, const int *pa, const int *pe);

#endif