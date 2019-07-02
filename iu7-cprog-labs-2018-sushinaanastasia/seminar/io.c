#include"io.h"

double **mtr_allocate(int n, int m)
{
	if (n <= 0 || m <= 0)
		return NULL;
	double **data = malloc(n * sizeof(double *)); 
	
	if (!data)
		return NULL;
	
	for (int i = 0; i < n; i++)
	{
		data[i] = malloc(m * sizeof(double));
		if (!(data[i]))
		{
			mtr_free(data, i - 1);
			return NULL;
		}
	}
	return data;
}

void mtr_free(double **ptrs, int n)
{
	if (!ptrs || n <= 0)
		return;
	for (int i = 0; i < n; i++)
		free(ptrs[i]);
	free(ptrs);
}

int mtr_read(const char *fname, double ***pmtr, int *pn, int *pm)
{
	int rc = OK; 
	double buf;
    FILE *f = fopen(fname, "r");
	
	if (f)
	{
		if (fscanf(f, "%d %d", pn, pm) == 2)
		{
			if (*pn > 0 && *pm > 0)
			{
				double **data = mtr_allocate(*pn, *pm);
				if (data)
				{
					for (int i = 0; i < *pn && rc == OK; i++)
					{
						for (int j = 0; j < *pm && rc == OK; j++)
						{
							if (fscanf(f, "%lf", &buf) == 1)
								data[i][j] = buf;
							else 
								rc = ERR_IO;
						}
					}
					if (rc == OK)
					{
						*pmtr = data; 
					}
					else
						mtr_free(data, *pn);
				}
				else
					rc = ERR_MEMORY;
			}
			else 
				rc = ERR_IO;
		}
		else
			rc = ERR_IO;
		fclose(f);
	}
	else
		rc = ERR_FILE;
	return rc;
}

void mtr_print(double **pmtr, int n, int m)
{
	if (!pmtr || n < 0 || m < 0)
	    return;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%lf ", pmtr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}