#include"multiply.h"
#include"matrix.h"
#include"errors.h"
#include"io.h"

/**
 * @brief get_mul
 * Считает произведение
 * @param a [in] - первая матрица
 * @param b [in] - вторая матрица
 * @param c [in] - матрица ответа
 * @param n [in] - количество строк новой матрицы
 * @param m [in] - количество столбцов новой матрицы
 * @param n2 [in] - количество строк второй матрицы
 */
void get_mul(double **a, double **b, double **c, int n, int m, int n2)
{
	zero_matrix(c, n, m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			for (int r = 0; r < n2; r++)
				c[i][j] += a[i][r] * b[r][j];
}

/**
 * @brief multiply
 * Считает произведение и обрабатывает ошибки
 * @param a [in] - первая матрица
 * @param n1 [in] - количество строк первой матрицы
 * @param m1 [in] - количество столбцов первой матрицы
 * @param b [in] - вторая матрица
 * @param n2 [in] - количество строк второй матрицы
 * @param m2 [in] - количество столбов второй матрицы
 * @param c [out] - матрица результата
 * @return rc - код ошибки
 */
int multiply(double **a, int n1, int m1, double **b, int n2, int m2, double ***c)
{
	if (a == NULL || b == NULL)
		return ERR_NULL;
	if (n2 <= 0 || n1 <= 0 || m2 <= 0)
		return ERR_NULL;
	
	if (n2 == m1)
	{
		double **buf = allocate_matrix(n1, m2);
		if (buf)
		{
			*c = buf;
			get_mul(a, b, *c, n1, m2, n2);
		}
		else
			return ERR_MEMORY;
	}
	else
		return ERR_MULT;
	return OK;
}
