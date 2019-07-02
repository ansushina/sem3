#ifndef __GETLINE_H__
#define __GETLINE_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

size_t my_strlen(const char *str);
int my_strcmp(const char *a, const char *b);
void my_strcpy(char *str1, char *str2);
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);

#endif 