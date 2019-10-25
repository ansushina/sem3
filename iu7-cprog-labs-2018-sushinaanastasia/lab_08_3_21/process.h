#ifndef __PROCESS_H__
#define __PROCESS_H__


void make_same(double **a, double **b, int n, int m);

void make_sort(int *a, int n);

//int find_main(int *p2, double **a, int n, int k);

void make_normal(double **a, int m, int i);

void make_diff(double **a, int m, int j, int i);

void make_answer(double **a, int n, int m, double **b, int *p2);

int do_gauss(double **a, int n, int m, double ***b);

#endif 
