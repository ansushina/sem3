#ifndef __IO_H__
#define __IO_H__

#define OK 0
#define ERR_IO 0
#define ERR_FILE 1
#define ERR_MEMORY 2
#define ERR_PARAM 3
#define ERR_NULL 4
#define ERR_MTR 5

#include<stdio.h>
#include<stdlib.h>

double **allocate_matrix(int n, int m);

void free_matrix(double **matrix, int n);

int read_matrix(char *fname, double ***matrix, int *pn, int *pm);

void print_matrix(double **matrix, int n, int m);

void print_array(double *array, int n);

#endif