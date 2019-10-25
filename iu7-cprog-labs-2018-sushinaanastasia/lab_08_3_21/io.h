#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>

void zero_matrix(double **a, int n, int m);

int read_matrix(const char *fname, double ***a, int *n, int *m);

int print_matrix(const char *fname, double **a, int n, int m);

#endif 