#ifndef __IO_H__
#define __IO_H__

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

size_t my_strlen(const char *str);

int my_strcmp(const char *a, const char *b);

ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);

void print_str(FILE *f, const char *a);

#endif
