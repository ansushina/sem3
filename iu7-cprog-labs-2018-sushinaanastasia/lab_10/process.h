#ifndef __PROCESS_H__
#define __PROCESS_H__

#include<stdio.h>
#include<stdlib.h>
#include"io.h"

void *pop_front(node_t **head);

void insert(node_t **head, node_t *elem, node_t *before);

int count(node_t *head);

int cmp_structs(const void *a1, const void *b1);

void front_back_split(node_t *head, node_t **back);

node_t *reverse(node_t *head);

node_t *sorted_merge(node_t **head_a, node_t **head_b,
    int (*comparator)(const void *, const void *));

node_t *sort(node_t *head, int (*comparator)(const void *, const void *));

#endif