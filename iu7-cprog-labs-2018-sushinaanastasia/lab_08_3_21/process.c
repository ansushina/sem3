#include"process.h"
#include"errors.h"
#include"matrix.h"
#include"io.h"
#include<math.h>

/**
 * @brief make_same
 * Заполняет матрицу б элементами матрицы а
 * @param a [in] - первая матрица
 * @param b [in] - вторая матрица
 * @param n [in] - количество строк матрицы
 * @param m [in] - количество столбцов матрицы
 */
void make_same(double **a, double **b, int n, int m)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			b[i][j] = a[i][j];
}
/**
 * @brief make_sort
 * Создает отсортированный массив
 * @param a [in] - массив
 * @param n [in] - количество элементов
 */
void make_sort(int *a, int n)
{
	for (int i = 0; i < n; i++)
		a[i] = i;
}

/**
 * @brief swap1
 * Меняет местами строки
 * @param a [in] - массив
 * @param n [in] - количество элементов
 * @param i [in] - номер первой строки
 * @param j [in] - номер второй строки
 */
void swap1(double **a, int n, int i, int j)
{
	double *swap;
	
	swap = a[i];
	a[i] = a[j];
    a[j] = swap;
}

/**
 * @brief swap2
 * Меняет местами столбцы
 * @param a [in] - массив
 * @param n [in] - количество элементов
 * @param i [in] - номер первого столбца
 * @param j [in] - номер второго столбца
 */
void swap2(double **a, int n, int i, int j)
{
	double swap;
	for (int u = 0; u < n; u++)
	{
		swap = a[u][i];
		a[u][i] = a[u][j];
		a[u][j] = swap;
	}
}

/**
 * @brief make_diff
 * Вычитает из jой строки iую
 * @param a [in] - матрица
 * @param m [in] - количество столбцов
 * @param j [in] - номер строки
 * @param i [in] - номер главной строки
 */
void make_diff(double **a, int m, int j, int i)
{
	double u = -a[j][i];
	//printf("u %lf ", u);
	for (int k = i; k < m; k++)
		a[j][k] += u * a[i][k];	
}

/**
 * @brief make_normal
 * Нормализирует строку
 * @param a [in] - матрица
 * @param m [in] - количество столбцов
 * @param i [in] - номер строки
 */
void make_normal(double **a, int m, int i)
{
	double d = a[i][i];
	for (int j = i; j < m; j++)
		a[i][j] /= d;
}

/**
 * @brief make_answer
 * Сичтают стоблец решений
 * @param a [in] - матрица
 * @param n [in] - количество строк
 * @param m [in] - количество столбцов
 * @param b [in] - матрица решений
 * @param p2 [in] - массив индексов столбцов
 */
void make_answer(double **a, int n, int m, double **b, int *p2)
{
	b[p2[n - 1]][0] = a[n - 1][n];
	for (int i = n - 2; i >= 0; i--)
	{
		//printf(" %d ", i);
		for (int k = i + 1; k < n; k++)
			b[p2[i]][0] -= a[i][k] * b[p2[k]][0];
		b[p2[i]][0] += a[i][n];
	}
}

/**
 * @brief find_main
 * Поиск главного элемента(2)
 * @param p2 [in] - массив индексов столбцов
 * @param a [in] - матрица
 * @param n [in] - количество строк матрицы
 * @param k [in] - номер активной строки
 * @return rc - код ошибки
 */
int find_main1(int *p2, double **a, int n, int k)
{
	int t1 = k, t2 = k;
	int swap;
	double max = a[k][k];
	for (int i = k; i < n; i++)
		for (int j = k; j < n; j++)
            if (fabs(a[i][j]) > max)
		    {
			    max = fabs(a[i][j]);
			    t1 = i;
				t2 = j;
		    }		
	if (fabs(max) < EPS)
		return ERR_GAUSS;
	
	swap = p2[k];
	p2[k] = p2[t2];
	p2[t2] = swap;
	
	swap1(a, n, k, t1);
	swap2(a, n, k, t2);
	
	return OK;
}

/**
 * @brief gauss
 * Реализует метод Гаусса
 * @param u [in] - матрица
 * @param p1 [in] - массив индексов строк
 * @param p2 [in] - массив индексов столбцов
 * @param n [in] - количество строк
 * @param m [in] - количество столбцов
 * @param b [in] - столбец решений
 * @return rc - код ошибки
 */
int gauss(double **u, int *p2, int n, int m,
    double **b)
{
	for (int i = 0; i < n; i++)
	{
		if (find_main1(p2, u, n, i) != OK)
			return ERR_GAUSS;
		make_normal(u, m, i);
		for (int j = i + 1; j < n; j++)
			make_diff(u, m, j, i);
	}
	zero_matrix(b, n, 1);
	make_answer(u, n, m, b, p2);
	return OK;
}

/**
 * @brief do_gauss
 * Реализует метод Гаусса и выполняет проверку некорректных ситуаций
 * @param a [in] - матрица
 * @param n [in] - количество строк
 * @param m [in] - количество столбцов
 * @param b [out] - матрица решений
 * @return
 */
int do_gauss(double **a, int n, int m, double ***b)
{
	double **u; 
	int *p2;
	int rc = OK;
	
	if (n <= 0)
		return ERR_NULL;
	
	if (a == NULL)
		return ERR_NULL;
	
	if (n != m - 1)
		return ERR_GAUSS;
	
	//if (proverka(a, n) == ERR_GAUSS)
	//	return ERR_GAUSS;
	
	u = allocate_matrix(n, m);
	if (u)
	{
	    p2 = malloc(m * sizeof(int));
	    if (p2)
		{
	        *b = allocate_matrix(n, 1);
	        if (*b)
            {
                make_same(a, u, n, m);
	            make_sort(p2, m);
						
				rc = gauss(u, p2, n, m, *b);
				if (rc != OK)
					free_matrix(*b, n);
			}
			else
				rc = ERR_MEMORY;
			free(p2);
		}
		else
			rc = ERR_MEMORY;
		free_matrix(u, n);
	}
	else 
		rc = ERR_MEMORY;
	
	return rc;
}
