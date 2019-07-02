#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>
#include <assert.h>

#define N 100

#define OK 0
#define ERR_IO 1
#define ERR_PARAM 2
#define ERR_RANGE 3

int read_array_new(FILE *f, int *pbeg, int **pend);

#endif 