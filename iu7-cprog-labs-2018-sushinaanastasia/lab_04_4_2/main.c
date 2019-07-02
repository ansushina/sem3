/*
Написать программу, которая запрашивает у пользователя элементы целочисленного
статического массива и выполняет его обработку. Максимальное количество элементов,
которое может ввести пользователь, равно 10.
Отсортировать массив методом вставок.
*/

#include <stdio.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_NO 3

#define N 10

/*
Считать массив
a - массив
x - текущий элемент
n - длина массива
*/
int read_array(int *a, int *n)
{
    int x;
    printf("Input N: ");

    if (scanf("%d", n) == 1)
    {
        if (*n <= 10 && *n > 0)
        {
            printf("Input numbers: ");
            for (int i = 0; i < *n; i++)
            {
                if (scanf("%d", &x) != 1)
                    return ERR_IO;
                a[i] = x;
            }
        }
        else
            return ERR_RANGE;
    }
    else
        return ERR_IO;
    return OK;
}

/*
Печать массива
a - массив
i - счетчик
n - длина массива
*/
void print_array(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("a[%d] = %d\n", i, a[i]);
    }
}

/*
Сокртировка вставками
a - массив
p - указатель на длину
min - текущий минимум
imin - номер текущего минимума
*/
void sort(int *a, int n)
{
    int min;
    int imin;

    for (int i = 0; i < n; i++)
    {
        min = a[i];
        imin = i;
        for (int j = i; j < n; j++)
        {
            if (a[j] < min)
            {
                min = a[j];
                imin = j;
            }
        }
        a[imin] = a[i];
        a[i] = min;
    }
}

/*
Обработка ошибочных ситуаций
rc - код ошибки
a - исходный массив
n - длина исходного массива
*/
int main(void)
{
    int rc = OK;
    int a[N];
    int n;

    rc = read_array(a, &n);
    if (rc == OK)
    {
        sort(a, n);
        printf("Array was sorted!\n");
        print_array(a, n);
    }
    else if (rc == ERR_RANGE)
    {
        printf("N must be less then ten and more then zero!");
    }
    else
    {
        printf("Input error\n");
    }

    return rc;
}
