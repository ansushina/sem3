#include "sum.h"
#include "matrix.h"
#include "errors.h"

/**
 * @brief get_sum
 * Считает сумму матриц
 * @param a [in] - первая матрица
 * @param b [in] - вторая матрица
 * @param c [in] - матрица результата
 * @param n [in] - количество строк
 * @param m [in] - количество столбцов
 */
void get_sum(double **a, double **b, double **c, int n, int m)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			c[i][j] = a[i][j] + b[i][j];
}

/**
 * @brief sum
 * Считает сумму и обрабаывает некорректные ситуации
 * @param a [in] - первая матрица
 * @param n1 [in] - количество строк
 * @param m1 [in] - количество столбцов
 * @param b [in] - вторая матрица
 * @param n2 [in] - количество строк
 * @param m2 [in] - количество столбцов
 * @param c [out] - матрица результата
 * @return код ошибки
 */
int sum(double **a, int n1, int m1, double **b, int n2, int m2, double ***c)
{
	if (a == NULL || b == NULL)
		return ERR_NULL;
	if (n1 <= 0 || m1 <= 0)
		return ERR_SUM;
		
	if (n1 == n2 && m1 == m2)
	{
		double **buf = allocate_matrix(n1, m1);
		if (buf)
		{
			*c = buf;
			get_sum(a, b, *c, n1, m1);
		}
		else
			return ERR_MEMORY;
	}
	else
		return ERR_SUM;
	return OK;
}
