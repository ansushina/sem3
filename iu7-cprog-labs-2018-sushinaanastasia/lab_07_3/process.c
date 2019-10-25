#include "process.h"
#include"errors.h"
#include<stdlib.h>
#include"io.h"

/**
 * @brief cmp_int
 * Сравнение целых
 * @param l [in] - указатель на левый элемент
 * @param r [in] - указатель на правый элемент
 * @return Возвращает положительное число, если l>r, и отрицательные в обратном случае.
 */
int cmp_int(const void *l, const void *r)
{
	const int *li = l;
	const int *ri = r;
	
	return *li - *ri;
}

/**
 * @brief cmp_char
 * Сравнение символов
 * @param l [in] - указатель на левый элемент
 * @param r [in]  - указатель на правый элемент
 * @return Возвращает положительное число, если l>r, и отрицательные в обратном случае.
 */
int cmp_char(const void *l, const void *r)
{
	const char *li = l;
	const char *ri = r;
	
	return *li - *ri;
}

/**
 * @brief cmp_float
 * Сравнение дробных
 * @param l [in] - указатель на левый элемент
 * @param r [in] - указатель на правый элемент
 * @return Возвращает положительное число, если L>R, и отрицательное в обратном случае
 */
int cmp_float(const void *l, const void *r)
{
	const double *li = l;
	const double *ri = r;
	
	if (*li - *ri > 0)
		return 1;
	else
		return -1;
}

/**
 * @brief swap
 * Меняет местами два элемента
 * @param l [in] - указатель на левый элемент
 * @param r [in] - указатель на правый элемент
 * @param size [in] - размер элемента
 */
void swap(void *l, void *r, size_t size)
{
	char *lc = l;
	char *rc = r;
	char *l_end = lc + size;
	char k;
	
	for (char *pi = lc; pi < l_end; pi++)
	{
		k = *pi;
		*pi = *rc;
		*rc = k;
		rc++;
	}
}

/**
 * @brief find_left
 * Бинарный поиск места для элемента
 * @param a [in] - указатель на первый элемент массива
 * @param pi [in] - указатель на обрабатываемый элемент массива
 * @param size [in] - размер элемента
 * @param k [in] - элемент 
 * @param l [out] - указатель на место вставки нового элемента
 */

void find_left(char *a, char *pi, size_t size, char *k, char **l, 
    int (*compar)(const void*, const void*))
{
	char *right;
	char *left;
	char *z;
	
	left = a;
	right = pi;
			
	while (left <= right)
	{
        z = left + size * ((right - left) / 2 / size);
		if (compar(z, k) < 0)
		    left = z + size;
		else 
		    right = z - size;
	}
	*l = left;
}

/**
 * @brief mysort
 * Сортировка бинарными вставками
 * @param base [in] - безтиповой указатель на начало массива
 * @param nmemb [in] - размер массива
 * @param size [in] - размер элемента
 */
void mysort(void *base, size_t nmemb, size_t size, 
    int (*compar)(const void*, const void*))
{
	char *a = base;
	char *a_after = a + nmemb * (size);
	char *k = malloc(size);
	char *left = a;
	char *p;
	
	for (char *pi = a + size; pi < a_after; pi += size)
	{
		if (compar(pi - size, pi) > 0)
		{
			p = k;
		    for (char *pj = pi; pj < pi + size; pj++)
		    {
			    *p = *pj;
				p++;
		    }
			
            find_left(a, pi, size, k, &left, compar);
		    for (char *pj = pi - size; pj >= left; pj -= size)
		    {
				swap(pj, pj + size, size);
		    }
			
			p -= size;
			for (char *pk = left; pk < left + size; pk++)
			{
				*pk = *p;
				p++;
			}
		}
	}
	free(k);
}



