#ifndef __PROCESS_H__
#define __PROCESS_H__

#include<stdio.h>
#include<stdlib.h>

int is_search(const char *a, const char *b, int len);

int count_search(const char *source, const char *search, int len1, int len2);

void insert_replace(char *buf, const char *replace, int len3);

char *str_replace(const char *source, const char *serach, const char *replace);

#endif