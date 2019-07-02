#include <stdio.h>
#include <assert.h>

#define N 100

#define OK 0
#define ERR_IO 1
#define ERR_PARAM 2
#define ERR_RANGE 3

/*
Чтение массива из файла
f - файл
pbeg - указатель на нулевой элемент массива
pend - указатель на запоследний элемент
n - кол-во элементов
a - лишний элемент
*/
int read_array_new(FILE *f, int *pbeg, int **pend)
{
	assert(f != NULL);
	assert(pbeg != NULL);
    int n = 0, a;

    while (n < N && fscanf(f, "%d", pbeg) == 1)
    {
        n++;
        pbeg++;
    }
    if (n == N && fscanf(f, "%d", &a) == 1)
    {
        return ERR_RANGE;
    }
    *pend = pbeg;
    return OK;
}