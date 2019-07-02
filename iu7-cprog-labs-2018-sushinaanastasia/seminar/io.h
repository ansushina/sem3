#ifndef __IO_H__
#define __IO_H__

#include<stdio.h>
#include<stdlib.h>

#define OK 0
#define ERR_IO 1
#define ERR_FILE 2
#define ERR_PARAM 3
#define ERR_MEMORY 4

double **mtr_allocate(int n, int m);

void mtr_free(double **ptrs, int n);

int mtr_read(const char *fname, double ***pmtr, int *pn, int *pm);

void mtr_print(double **pmtr, int n, int m);

#endif


