#ifndef _IO_H_
#define _IO_H_

#include <stdio.h>
#include <assert.h>

#define N 20

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_PARAM 3

int array_read(FILE *f, int *a, int *n);

void array_print(const int *a, int n);

#endif