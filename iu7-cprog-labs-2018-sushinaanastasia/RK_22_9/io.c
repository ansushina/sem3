#include "io.h"

int array_read(FILE *f, int *a, int *n)
{
	assert(a != NULL);
	
	if (fscanf(f, "%d", n) != 1)
		return ERR_IO;
	if (*n > N || *n <= 0)
		return ERR_RANGE;
	
	for (int i = 0; i < *n; i++)
	{
		if (fscanf(f, "%d", &a[i]) != 1)
			return ERR_IO;
		if (a[i] < 0 || a[i] > 9)
			return ERR_RANGE;
	}
	return OK;
}

void array_print(const int *a, int n)
{
	for (int i = 0; i < n; i++)
			printf("%d ", a[i]);
}