#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"process.h"
#include"getline.h"
#define N 50

int read_filename(char *filename);

int read_data(FILE *f,  char **title, char **author, unsigned short *year, char **country);

int read_data_from_file(FILE *f, film_st **head, film_st *sort_head[MAX_SORT_INDX], 
    film_st *head_filter[MAX_FILTER_INDX]);
	
void print_normal(FILE *f, film_st *head);
void print_sort(FILE *f, film_st *head, int i);
void print_filter(FILE *f, film_st *head, int i);

#endif 
