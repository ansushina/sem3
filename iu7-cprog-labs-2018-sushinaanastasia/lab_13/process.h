#ifndef __PROCESS_H__
#define __PROCESS_H__

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define MAX_SORT_INDX 3
#define MAX_FILTER_INDX 2

typedef struct film film_st;
struct film
{
    char *title;
    char *author;
    unsigned short year;
    char *country;
    struct list_head sort[MAX_SORT_INDX];
    struct list_head filter[MAX_FILTER_INDX];
    film_st *next;
};

film_st *add(film_st *head, film_st *new, film_st *sort_head[MAX_SORT_INDX], 
    film_st *head_filter[MAX_FILTER_INDX]);
	
int cmp_year(const void *right, const void *left);

int cmp_country(const void *right, const void *left);

int cmp_title(const void *right, const void *left);

int filter1(const void *el);

int filter2(const void *el);

film_st *create_struct(char *title, char *author, unsigned short year, char *country);

film_st *add_sort(film_st *head, film_st *new, int i, int (*compar)(const void*, const void*));

film_st *add_filter(film_st *head, film_st *new, int i, int (*f)(const void*));

void add_in_list(film_st *new, film_st *sort_head[MAX_SORT_INDX], 
    film_st *head_filter[MAX_FILTER_INDX]);
	
film_st *add_st(film_st *head, film_st *new);

void del_from_list(film_st *p, film_st *sort_head[MAX_SORT_INDX], 
    film_st *head_filter[MAX_FILTER_INDX]);
	
film_st *del_st(film_st *head, char *title, film_st *sort_head[MAX_SORT_INDX], 
    film_st *head_filter[MAX_FILTER_INDX]);
	
void free_list(film_st *head);

void change_data(film_st *head, film_st *sort_head[MAX_SORT_INDX], 
    film_st *head_filter[MAX_FILTER_INDX]);
	
void change(film_st *head, film_st *sort_head[MAX_SORT_INDX], 
    film_st *head_filter[MAX_FILTER_INDX],
	char *title, char *author, unsigned short year, char *country);

#endif 
