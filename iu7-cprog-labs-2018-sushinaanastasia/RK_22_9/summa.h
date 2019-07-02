#ifndef _SUMMA_H_
#define _SUMMA_H_

#include <stdio.h>
#include <assert.h>

#define N 20

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_PARAM 3

int get_summa(const int *a, int n1, const int *b, int n2, int *c, int *n3);

void reverse( int *a, int n, int *c);

#endif