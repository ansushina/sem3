#ifndef __PROCESS_H__
#define __PROCESS_H__

#include <stdio.h>
#include"io.h"

struct keys
{
	int n;
	int people;
};

int read_all(char * filename, struct country *all, int *n);

void find(char *filename, char *mainland, char *turism);

void sort1(struct country *all, int n, int *m);

void sort2(struct country *all, int n, struct keys *k, int *m);

void sort3(struct country *all, int n, struct keys *k, int *m);
int delete(char *filename);

#endif 