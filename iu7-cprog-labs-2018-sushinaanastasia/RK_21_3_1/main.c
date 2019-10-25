/*
Дано натуральное число. Если в нем есть числа a и b, то определить какая
из них расположена в числе правее.
*/

#include <stdio.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_NET_CHISLA 3

#define TEN 10

/*
Ищет какая из цифр правее
n - исходное натуральное
a - число a
b - число b
p - указатель на искомое число
k - текущее значение цифры числа
flaga - минимальная позиция a
flagb - минимальная позиция b
i - счетчик позиции
*/

int what_number_is_in_right(int n, int a, int b, int *p)
{
    int k;
    int flaga = 0, flagb = 0, i = 1;

    while (n > 0)
    {
        k = n % TEN;
        if (k == a)
        {
            if (!flaga)
                flaga = i;
        }
        if (k == b)
        {
            if (!flagb)
                flagb = i;
        }
        i += 1;
        n /= TEN;
    }

    if (!flaga || !flagb)
    {
        return ERR_NET_CHISLA;
    }
    else if (flaga < flagb)
    {
        *p = a;
    }
    else
    {
        *p = b;
    }
    return OK;
}

/*
Обработка ошибочных ситуаций, вывод
rc - код ошибки
n - исходное натуральное число
a - число a
b - число b
p - значение числа, которое находится правее
*/

int main (void)
{
    int rc;
    int n, a, b;
    int p;

    printf("Input N(natural): ");
    if (scanf("%d", &n) == 1)
    {
        if (n > 0)
        {
            printf("Input a and b: ");
            if (scanf("%d%d", &a, &b) == 2)
            {
                if ((a >= 0 && a < 10) && (b >= 0 && b < 10))
                {
                    rc = what_number_is_in_right(n, a, b, &p);
                    if (rc == OK)
                    {
                        printf("Right number is %d!\n", p);
                    }
                    else
                    {
                        printf("No numbers in N!\n");
                    }
                }
                else
                {
                    rc = ERR_RANGE;
                    printf("a and b must be less then 10!\n");
                }
            }
            else
            {
                rc = ERR_IO;
                printf("Input error!\n");
            }
        }
        else
        {
            rc = ERR_RANGE;
            printf("N must be natural!\n");
        }
    }
    else
    {
        rc = ERR_IO;
        printf("Input error!\n");
    }
    return rc;
}
