#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct node node_t;

struct node
{
	unsigned int n; 
	node_t *next;
};

int read_number(FILE *f, node_t **head);

node_t *create_st(unsigned int n);

node_t *add_st(node_t *head, node_t *newst);

void free_list(node_t *head);

unsigned int make_number(node_t *head);

void print_st(node_t *head);

#endif