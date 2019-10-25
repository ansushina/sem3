#include"io.h"
#include <stdlib.h>
#include"errors.h"

/**
 * @brief count_n
 * Подсчет количества элементов
 * @param f [in] - файл
 * @return колличество элементов n
 */
int count_n(FILE *f)
{
	int n = 0, k;
	while (fscanf(f, "%d", &k) == 1)
		n++;
	return n;
}

/**
 * @brief read_array
 * Считывание массива
 * @param f [in] - файл
 * @param pa [in,out] - указатель на массив
 * @param n [in] - количество элементов
 * @return Возвращает Ok, если ошибок не было, ERR_IO, если произошла ошибка считывания
 */
int read_array(FILE *f, int *pa, int n)
{
	for (int i = 0; i < n; i++)
		while (fscanf(f, "%d", pa + i) != 1)
			return ERR_IO;
	return OK;
}

/**
 * @brief read_a
 * Создание массива и считывание его из файла
 * @param f [in] - файл
 * @param pa [out] - указатель на первый элемент массива
 * @param pe [out] - указатель на запоследний элемент массива
 * @return Возвращает OK, если ошибок не было, ERR_EMPTY если файл пустой,
ERR_MEMORY, если не удалось выделить паменять.
 */
int read_a(FILE *f, int **pa, int **pe)
{
	int n, rc;
	int *buf;
	rewind(f);
	n = count_n(f);
	if (n > 0)
	{
	    buf = malloc(n * sizeof(int));
	    if (buf)
	    {
			rewind(f);
			rc = read_array(f, buf, n);
			if (rc == OK)
			{
				*pa = buf;
				*pe = *pa + n;
			}
			else
				free(buf);
	    }
	    else 
		    rc = ERR_MEMORY;
	}
	else
		rc = ERR_EMPTY;
	return rc;
}


/**
 * @brief print_array
 * печать массива
 * @param f [in] - файл
 * @param pa [in] - указатель на первый элемент
 * @param pe [in] - указатель на запоследний элемент
 */
void print_array(FILE *f, const int *pa, const int *pe)
{
	for (const int *pi = pa; pi < pe; pi++)
		fprintf(f, "%d ", *pi);
}
