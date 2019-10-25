#ifndef __IO_H__
#define __IO_H__

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define N 30
#include<stdio.h>

struct b
{
	char name[N+1];
	char author[N+1];
};

typedef struct node node_t;

struct node
{
    void *data;
	node_t *next;
};

node_t *create_struct(void *data);

node_t *add_struct(node_t *head, node_t *pj);

void free_list(node_t *head);

int read_data(FILE *f, struct b *data);

int count_n(FILE *f );

int read_data_from_file(FILE *f, node_t **head, struct b **d);

void print_to_file(FILE *f, node_t *head);

#endif
