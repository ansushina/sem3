#ifndef __PROCESS_H__
#define __PROCESS_H__

#define EPS 0.000001

double calc_avg(const double *a, int n);

void sort(double **mtr, int n, int m);

int find_first_zero(const double *a, int n);

int find_last_ucg(const double *a, int n);

void change(double **mtr, int n, int m);

#endif