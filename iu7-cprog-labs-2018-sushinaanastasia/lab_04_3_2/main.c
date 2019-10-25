/*
Написать программу, которая запрашивает у пользователя элементы целочисленного
статического массива и выполняет его обработку. Максимальное количество элементов,
которое может ввести пользователь, равно 10.
Удалите из исходного массива все элементы, которые являются полными квадратами.
*/

#include <stdio.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_NO 3

#define N 10

#define YES 0
#define NO 1

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
void print_array(const int *a, int n)
{
    printf("New array: \n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", a[i]);
    }
}

/*
Определяет, является ли число полным квадратом
t - число
k - счетчик
*/
int is_kvadrat(int t)
{
    int k = 2;
    if (t == 1 || t == 0)
        return YES;
    while (k < t)
    {
        if (t == k * k)
            return YES;
        k++;
    }
    return NO;
}

/*
Удаляет число из массива
a - массив
i - номер элемента
n - длина массива
j - счетчик
*/
void udalit(int *a, int i, int n)
{
    for (int j = i; j < n; j++)
        a[j] = a[j + 1];
}

/*
Удаление полных квадратов из массива
a - массив
p - указатель на длину
count - кол-во удаленных жлементов
t - текущий элемент
k - счетчик
*/
int delete_kvadrat(int *a, int *p)
{
    int count = 0, k;

    for (int i = 0; i < *p; i++)
    {
        k = is_kvadrat(a[i - count]);
        if (k == YES)
        {
            udalit(a, i - count, *p - count);
            count += 1;
        }
    }
    *p -= count;
    if (count == 0)
        return ERR_NO;
    return OK;
}

/*
Обработка ошибочных ситуаций
rc - код ошибки
a - исходный массив
x - элемент массива
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
        rc = delete_kvadrat(a, &n);
        if (rc == OK)
        {
            printf("Array changed!\n");
            print_array(a, n);
        }
        else
        {
            printf("No polnii kvadrat!\n");
        }
    }
    else if (rc == ERR_RANGE)
    {
        printf("N must be less then ten and more then zero!");
    }
    else
    {
        printf("Imput error\n");
    }

    return rc;
}
