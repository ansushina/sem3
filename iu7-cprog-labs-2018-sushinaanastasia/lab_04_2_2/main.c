/*
Написать программу, которая запрашивает у пользователя элементы целочисленного
статического массива и выполняет его обработку. Максимальное количество элементов,
которое может ввести пользователь, равно 10.
Поместите в новый массив элементы исходного массива который начинаются
и заканчиваются на одну и ту же цифру.
*/

#include <stdio.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_NO 3

#define YES 0
#define NO 1

#define N 10
#define TEN 10
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
first - первая цифра
last - последняя цифра
t - текущее значение элемента
*/
int first_and_last(int t)
{
    int first, last;

    last = t % TEN;
    t = t / TEN;
    while (t > 0)
    {
        first = t % TEN;
        t = t / TEN;
    }
    if (first == last)
        return YES;
    return NO;
}

/*
Сздание нового массива
a - исходный массив
n1 - длина исходного массива
b - новый массив
p - указатель на длину нового массива
*/
int new_array(const int *a, int n1, int *b, int *p)
{
    *p = 0;
    for (int i = 0; i < n1; i++)
    {
        if (first_and_last(a[i]) == YES)
        {
            b[*p] = a[i];
            *p += 1;
        }
    }
    if (*p == 0)
        return ERR_NO;
    return OK;
}

/*
Обработка ошибочных ситуаций
rc - код ошибки
a - исходный массив
b - новый массив
n1 - длина исходного массива
n2 - длина нового массива
*/
int main(void)
{
    int rc = OK;
    int a[N], b[N];
    int n1, n2;

    rc = read_array(a, &n1);
    if (rc == OK)
    {
        rc = new_array(a, n1, b, &n2);
        if (rc == OK)
        {
            printf("Array created!\n");
            print_array(b, n2);
        }
        else
        {
            printf("No first = last in array!\n");
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
