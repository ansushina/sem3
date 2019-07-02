/*
Текстовый файл содержит целые числа. Найти значение минимального четного числа.
Задачу решить за один просмотр файла. Имя файла передается в программу через
параметры комнадной строки.
*/

#include <stdio.h>

#define OK 0
#define ERR_IO 1
#define ERR_PARAM 2
#define ERR_NET_CHISLA 3

#define TWO 2

#define YES 1
#define NO 0

/*
Получить минимальное четное
f - файл
p - адрес переменной минимума
a - знаечние текущего числа
flag - переменная, определяющая встречено ли четное
*/

int get_min_chet(FILE *f, int *p)
{
    int a;
    int flag = NO;

    while (fscanf(f,"%d", &a) == 1)
    {
        if (a % TWO == 0)
        {
            if (!flag)
            {
                flag = YES;
                *p = a;
            }
            if (a < *p)
                *p = a;
        }
    }
    if (flag)
    {
        return OK;
    }
    else
    {
        return ERR_NET_CHISLA;
    }
}

/*
Обработка ошибочных ситуаций, вывод
argc - кол-во параметров
argv - массив параметров
rc -код ошибки
f - файл
min - искомый минимум
*/
int main(int argc, char **argv)
{
    int rc;
    FILE *f;
    int min;

    if (argc != 2)
    {
        printf("main.exe <file_name>!\n");
        return ERR_PARAM;
    }

    f = fopen(argv[1], "r");
    if (f)
    {
        rc = get_min_chet(f, &min);
        if (rc == OK)
        {
            printf("Chet minimum = %d", min);
        }
        else
        {
            printf("No chet numbers!\n");
        }
        fclose(f);
    }
    else
    {
        printf("Input error!");
        rc = ERR_IO;
    }
    return rc;
}
