
#include "sum.h"

/*
Получить значение
pbeg - указатель на нулевой элемент массива
pend - указатель на запоследнйи элемент
sum - значение
el - элемент
*/
void get_sum(const int *pbeg, const int *pend, int *sum)
{
	assert(pbeg != NULL);
	assert(pend != NULL); 
    assert(pbeg != pend);
    int el = 1;

    *sum = 0;
    while (pbeg < pend)
    {
        el *= *pbeg;
        *sum += el;
        if (*pbeg < 0)
            break;
        pbeg++;
    }
}