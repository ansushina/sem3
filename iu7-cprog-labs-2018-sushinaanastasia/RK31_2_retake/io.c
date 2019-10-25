#include"io.h"


double **allocate_matrix(int n, int m)
{
	if (!n || !m || n < 0 || m < 0)
		return NULL;
	
	double **data = calloc(n, sizeof(double *));
	
	if (!data)
		return NULL;
	
	for (int i = 0; i < n; i++)
	{
		data[i] = malloc(m * sizeof(double));
		if (!(data[i]))
		{
			free_matrix(data, i - 1);
			return NULL;
		}
	}
	return data;
}

void free_matrix(double **matrix, int n)
{
	for (int i =0; i < n; i++)
		free(matrix[i]);
	free(matrix);
}

int read_matrix(char *fname, double ***matrix, int *pn, int *pm)
{
	int rc = OK;
    double k; 	
	FILE *f =  fopen(fname, "r");
	if (f)
	{
		if (fscanf(f, "%d %d", pn, pm) == 2 && *pn > 0 && *pm > 0)
		{
			double **buf = allocate_matrix(*pn, *pm);
           	if (buf)
			{
				for (int i = 0; i < *pn && rc == OK; i++)
				{
					for (int j = 0;j < *pm && rc == OK; j++)
					{
						if (fscanf(f, "%lf", &k) == 1)
						{
							buf[i][j] = k;
						}
						else 
						{
							rc = ERR_IO;
						}
					}
				}
				if (rc == OK)
				{
					*matrix = buf;
				}
				else
					free_matrix(buf, *pn);
			}
			else 
				rc = ERR_MEMORY;
		}
		else
			rc = ERR_IO;
	}
	else
	{
		rc = ERR_FILE;
	}
	return rc;
}

void print_matrix(double **matrix, int n, int m)
{
	printf("Matrix:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%lf ", matrix[i][j]);
		}
		printf("\n");
	}
}

void print_array(double *array, int n)
{
	printf("array: \n");
	for (int i = 0; i < n; i++)
	{
		printf("%lf ", array[i]);
	}
}


