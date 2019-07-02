/*
Пользователь вводит целые числа, по окончании ввода чисел нажимает Ctrl-Z и Enter или
вводит букву. Программа находит количество чисел, которые больше своих «соседей», т.е. предшествующего и
последующего.
*/

#include <stdio.h>

#define OK 0
#define ERR_NUMBER 1

/*
 Функция подсчета чисел, которые больше своих соседей.
 f - файл
 n - количество
 num1,num2,num3 - три подряд идущих элемента
*/
int poisk(FILE *f, int *p)
{
    int num1, num2, num3;

    *p = 0;
    if (fscanf(f, "%d%d", &num1, &num2) == 2)
    {
        //цикл, проверяет является ли текущая тройка чисел подходящей
        while (fscanf(f, "%d", &num3) == 1)
        {
            if (num2 > num1 && num2 > num3)
            {
                *p += 1;
            }
            num1 = num2;
            num2 = num3;
        }
    }
    else
    {
        return ERR_NUMBER;
    }
    return OK;
}

/*
Проверка ввода и вывод значения.
f - файл
n - количество
rc - код ошибки
*/
int main(int argc, char **argv)
{
    int n;
    int rc = OK;

    printf("Input numbers: ");

    if (poisk(stdin, &n) == OK)
    {
        printf("n = %d\n", n);
    }
    else
    {
        rc = ERR_NUMBER;
        printf("Need more numbers in file!\n");
    }

    return rc;
}
