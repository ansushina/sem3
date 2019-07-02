/*
Составить программу, печатающее разложение на простые множители заданного
натурального числа n > 0. Если n равно 1, печатать ничего не надо.
*/

#include <stdio.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

/*
Функция разложения на простые множетели.
a - исходное число
n - значение множителя
*/
void prost(int a)
{
    int n = 2;
    printf("All simple factors:\n");
	//цикл ищет все простые множетели
    while (a != 1)
    {
        if (a % n == 0)
        {
            a /= n;
            printf("%d\n", n);
        }
        else
            n += 1;
    }
}

/*
Проверка ввоода значений.
num - вводиме число
rc - код ошибки
*/
int main(void)
{
    int num;
    int rc = OK;
    printf("Enter natural number: ");

    if (scanf("%d", &num) == 1)
    {
        if (num >= 1)
        {
            prost(num);
        }
        else
        {
            rc = ERR_RANGE;
            printf("N mast be natural!\n");
        }
    }
    else
    {
        rc = ERR_IO;
        printf("Input error!\n");
    }
    return rc;
}
