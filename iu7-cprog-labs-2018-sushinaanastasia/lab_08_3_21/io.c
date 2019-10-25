
#include "io.h"
#include "matrix.h"
#include "errors.h"
/**
 * @brief zero_matrix
 * заполняет матрицу нулями
 * @param a [in] - матрица
 * @param n [in] - количество строк
 * @param m [in] - количество столбцов
 */
void zero_matrix(double **a, int n, int m)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
            a[i][j] = 0;			
}
/**
 * @brief read_matrix
 * чтение матрицы
 * @param fname [in] - имя файла
 * @param a [out] - матрица
 * @param n [out] - количество строк
 * @param m [ont] - количество столбцов
 * @return код ошибки
 */
int read_matrix(const char *fname, double ***a, int *n, int *m)
{
	FILE *f;
	int count;
	double **buf;
	int i, j; 
	double k;
	int rc = OK, u;
	
	f = fopen(fname, "r");
	
	if (!f)
		return ERR_FILE;
	
	if (fscanf(f, "%d %d %d", n, m, &count) == 3)
	{
		if (*n > 0 && *m > 0 && count >= 0)
		{
			buf = allocate_matrix(*n, *m);
			if (buf)
			{
				//zero_matrix(buf, *n, *m);
				u = 0;
				while (u < count && rc == OK)
				{
					if (fscanf(f, "%d %d %lf", &i, &j, &k) == 3)
					{
						if (i <= *n && j <= *m && i > 0 && j > 0)
						{
							if (buf[i - 1][j - 1] == 0)
							{
						        buf[i - 1][j - 1] = k;
								u++;
							}
						}
						else
							rc = ERR_READ;
					}
					else 
						rc = ERR_READ;
				}
				if (rc != OK)
					free_matrix(buf, *n);
				else 
					*a = buf;
			}
			else
				rc = ERR_MEMORY;
		}
		else 
			rc = ERR_RANGE;
	}
	else
		rc = ERR_READ;
	
	fclose(f);
	return rc;
}

/**
 * @brief print_matrix
 * печатает матрицу
 * @param fname [in] - имя файла
 * @param a [in] - матрица
 * @param n [in] - количество строк
 * @param m [in] - количество столбцов
 * @return код ошибки
 */
int print_matrix(const char *fname, double **a, int n, int m)
{
	FILE *f;
	if (a == NULL)
		return ERR_NULL;
	
	f = fopen(fname, "w");
	if (!f)
		return ERR_FILE;
	
	fprintf(f, "%d %d\n", n, m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			fprintf(f, "%lf ", a[i][j]);
		fprintf(f, "\n");
	}
	fclose(f);
	
	return OK;
}
