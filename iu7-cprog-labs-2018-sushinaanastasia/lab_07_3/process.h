#ifndef __PROCESS_H__
#define __PROCESS_H__

#include<stdio.h>


int cmp_int(const void *l, const void *r);

int cmp_char(const void *l, const void *r);

int cmp_float(const void *l, const void *r);

void find_left(char *a, char *pi, size_t size, char *k, char **left, 
    int (*compar)(const void*, const void*));

void swap(void *l, void *r, size_t size);

void mysort(void *base, size_t nmemb, size_t size,
    int (*compar)(const void*, const void*));

#endif