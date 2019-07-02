/*
Вычислить значение x[0] + x[0]*x[1] +x[0]*x[1]*x[2]+...+x[0]*x[1]*x[2]...x[m],
где x[i] - элементы массива x из n элементов, m - индекс первого
отрицательного элемента этого массива либо число n-1,
если такого элемента в массиве нет.
*/

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
    int n = 0, a;

    while (n < N && fscanf(f, "%d", pbeg) == 1)
    {
        n++;
        pbeg++;
    }
    if (n == N && fscanf(f, "%d", &a) == 1)
    {
		*pend = pbeg;
        return ERR_RANGE;
    }
    *pend = pbeg;
    return OK;
}

/*
Получить значение
pbeg - указатель на нулевой элемент массива
pend - указатель на запоследнйи элемент
sum - значение
el - элемент
*/
void get_sum(const int *pbeg, const int *pend, int *sum)
{
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

/*
Обработка ошибочных ситуаций
argc - количество параметров
argv - параметры
f - файл
x - массив
sum - значение
rc - код ошибки
rend - указатель на запоследний элемент
*/
int main(int argc, char **argv)
{
    FILE *f;
    int x[N];
    int sum;
    int rc;
    int *pend;

    if (argc != 2)
    {
        printf("main.exe <file-name>!\n");
        return ERR_PARAM;
    }

    f = fopen(argv[1], "r");
    if (f)
    {
        rc = read_array_new(f, x, &pend);
        fclose(f);
        if (rc == ERR_RANGE)
            printf("More then hundred elements in file!\n");
		if (x != pend)
		{
            get_sum(x, pend, &sum);
            printf("sum = %d", sum);
		}
		else
		{
			rc = ERR_IO;
			printf("No elements in file!\n");
		}
    }
    else
    {
        rc = ERR_IO;
        printf("File can't be open!");
    }


    return rc;
}
