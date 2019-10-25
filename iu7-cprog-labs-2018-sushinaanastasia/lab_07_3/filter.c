#include "filter.h"
#include"errors.h"
#include<stdlib.h>

/**
 * @brief find_otr
 * Находит указатель на последнее отрицательное
 * @param pb [in] - указатель на первый элемент массива
 * @param pe [in] - указатель на запоследний элемент массива
 * @param p [out] - указатель на отрицательный элемент или запоследний элемент массива
 */
void find_otr(const int *pb, const int *pe, const int **p)
{
	*p = pe;
	for (const int *pi = pb; pi < pe; pi++)
	{
		if (*pi < 0) 
			*p = pi;
	}
}

/**
 * @brief copy
 * Переписывает часть массива в новый
 * @param pb_src [in] - старый массив
 * @param pb_dst [in]  - новый массив
 * @param p [in]  - указатель на запоследний элемент
 */
void copy(const int *pb_src, int *pb_dst, const int *p)
{
	for (pb_src = pb_src; pb_src < p; pb_src++)
	{
		*pb_dst = *pb_src;
		pb_dst++;
	}
}

/**
 * @brief key
 * Функция фильтр
 * Записывает в новый массив элементы старого до последнего отлицательного
 * @param pb_src [in] - указатель на первый элемент первого массива
 * @param pe_src [in] - указатель на эпоследний элемента первого массива
 * @param pb_dst [out] - указатель на первый элемент второго массива
 * @param pe_dst [out] - указатель на эпоследний элемента второго массива
 * @return Возвращает Ok, если ошибок не было,
ERR_EMPTY, если передан пустой маассив,
ERR_NULL, если массив не передан,
ERR_FILTER, если после применения фильтра не осталось элелементов в массиве
ERR_MEMORY, если память не выделилась
 */
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
	int rc = OK;
	const int *p = NULL;
	if (pb_src == NULL)
		return ERR_NULL;
	if (pe_src == NULL)
		return ERR_NULL;
	if (pe_src == pb_src)
       return ERR_EMPTY;
    if (pe_src < pb_src)
		return ERR_EMPTY;
  
	find_otr(pb_src, pe_src, &p);
	if (p > pb_src)
	{
	    int *buf = malloc((p - pb_src) * sizeof(int));
	    if (buf)
	    {
		    copy(pb_src, buf, p);
		    *pb_dst = buf;
		    *pe_dst = *pb_dst + (p - pb_src);
	    }
	    else
		    rc = ERR_MEMORY;
	}
	else 
		rc = ERR_FILTER;
	return rc;
}
