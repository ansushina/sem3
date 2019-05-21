#ifndef __IO_H__
#define __IO_H__

#define N 20
#define ERR_IO 1
#define M 50
#include <stdio.h>

struct country
{
	char name[N+1];
	int people;
	char capital[N+1];
	char mainland[N+1];
    char turism[N+1];
	union
	{
		struct
		{
			int n;
			char type[N+1];
		} ex;
		struct
		{
			char season[N+1];
			int tw;
			int ta;
			int time;
		} beach;
		struct
		{
			char type[N+1];
			int cost;
		} sport;
	} tur;
};

void p();

int read_new(struct country *a);

void print_a(struct country a);

int save(char *filename, struct country a);

int read(char *filename, struct country a);

int read_txt(FILE *f, struct country *a);

int save_txt(char *filename, struct country a);
#endif 