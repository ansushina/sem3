#include"matrix.h"
#include<stdio.h>

/**
 * @brief allocate_matrix
 * Выделяет память под матрицу
 * @param n [in] - количество строк
 * @param m [in] - количество столбцов
 * @return data возвращает матрицу
 */
/*double **allocate_matrix(int n, int m)
{
	if (n == 0 || m == 0)
		return NULL;
	double **data = calloc(n, sizeof(double*));
	if (!data)
		return NULL;
	
	for (int i = 0; i < n; i++)
	{
		data[i] = calloc(m, sizeof(double));
		
		if (!data[i])
		{
			free_matrix(data, n);
			
			return NULL;
		}
	}
	
	return data;
}*/

//другая реализация выделение памяти
double **allocate_matrix(int n, int m)
{
	if (n == 0 || m == 0)
		return NULL;
	double **data = calloc(n + 1, sizeof(double*));
	if (!data)
		return NULL;
	
	double *base = calloc(n * m, sizeof(double));
	if (!base)
	{
		free(data);
		return NULL;
	}
	for (int i = 0; i < n; i++)
	{
		data[i] = base + i * m;
	}
	
	data[n] = base;
	
	return data;
}

/**
 * @brief free_matrix
 * Освобождает память из-под матрицы
 * @param data [in] - матрица
 * @param n [in] - количество строк
 */
/*void free_matrix(double **data, int n)
{
	assert(data != NULL);
	assert(n != 0);
	for (int i = 0; i < n; i++)
		free(data[i]);
	free(data);
}*/
//другая реализация очистки памяти

void free_matrix(double **data, int n)
{
	assert(data != NULL);
	assert(n != 0);
	free(data[n]);
	free(data);
}
