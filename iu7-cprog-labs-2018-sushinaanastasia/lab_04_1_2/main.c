/*
Написать программу, которая запрашивает у пользователя элементы целочисленного
статического массива и выполняет его обработку. Максимальное количество элементов,
которое может ввести пользователь, равно 10.
Найдите среднее арифметическое отрицательных элементов массива.
*/

#include <stdio.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_NO_OTR 3

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
int read_array(int *a, int *n)
{
    int x;
    *n = 0;
    printf("Input numbers: ");

    while (scanf("%d", &x) == 1)
    {
        if (*n == N)
            return ERR_RANGE;
        a[*n] = x;
        *n += 1;
    }
    if (*n > 0)
        return OK;
    return ERR_IO;
}
*/
/*
Функция поиска среднего арифметического отрицательных чисел
a - массив
n - длина массива
p - указатель на среднее арифметическое
sum - сумма отрицательных элементов
notr - количество отрицательных элементов
*/
int sr_ar_otr(const int *a, int n, float *p)
{
    int sum = 0;
    int notr = 0;

    for (int i = 0; i < n; i++)
    {
        if (a[i] < 0)
        {
            sum += a[i];
            notr += 1;
        }
    }
    if (notr > 0)
    {
        *p = (float) sum / notr;
        return OK;
    }
    else
        return ERR_NO_OTR;
}
/*
 Обработка ошибочных ситуаций
rc - код ошибки
a - массив
n - длина массива
sr - среднее арифметическое
*/
int main(void)
{
    int rc = OK;
    int a[N];
    int n;
    float sr;

    rc = read_array(a, &n);
    if (rc == OK)
    {
        rc = sr_ar_otr(a, n, &sr);
        if (rc == OK)
        {
            printf("Sredde arifmet otricat = %f\n", sr);
        }
        else
        {
            printf("No otricat in array!\n");
        }
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
