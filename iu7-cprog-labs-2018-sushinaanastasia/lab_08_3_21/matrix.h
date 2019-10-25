#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdlib.h>
#include <assert.h>

double **allocate_matrix(int n, int m);

void free_matrix(double **data, int n);

#endif 