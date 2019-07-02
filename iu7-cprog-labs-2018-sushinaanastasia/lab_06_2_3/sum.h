#ifndef __SUM_H__
#define __SUM_H__

#include <stdio.h>
#include <assert.h>

#define N 100

#define OK 0
#define ERR_IO 1
#define ERR_PARAM 2
#define ERR_RANGE 3

void get_sum(const int *pbeg, const int *pend, int *sum);

#endif 