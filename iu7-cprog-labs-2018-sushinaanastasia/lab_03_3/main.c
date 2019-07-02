/*
Написать программу, которая обрабатывает двоичный файл, содержащий целые числа.
Программа должна уметь:
− создавать файл и заполнять его случайными числами;
− выводить числа из файла на экран;
− упорядочивать числа в файле.

Выбранные параметры для этой задачи:
Целочисленный тип: int
Пузырьковая сортировка
Элементы располагаются по возрастанию
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define OK 0
#define ERR_PARAM 1
#define ERR_IO 2
#define ERR_FUN 3

// Справка
void usage(void)
{
    printf("main.exe <action> <file_name>\n");
    printf("Action:\n");
    printf("\t c - create file\n");
    printf("\t p - print file\n");
    printf("\t s - sort file\n");
}

/*
 заполнение файла массивом случайных чисел
 f - файл
 a - текущее число
 n - кол-во элементов
*/
int create_array(FILE *f)
{
    int a;
    int n = 10;

    for (int i = 0; i < n; i++)
    {
        a = rand();
        if (fwrite(&a, sizeof(int), 1, f) != 1)
             return ERR_FUN;
    }
    return OK;
}

/*
Печать массива чисел из файла
f - файл
k - текущий элемент
i - счетчик
*/
void print_array(FILE *f)
{
    int k;
    int i = 0;

    while (fread(&k, sizeof(int), 1, f) == 1)
    {
        printf("arr[%d] = %d\n", i++, k);
    }
}

/*
Получить значение по номеру
f - файл
p - указатель на значение
pos - позиция
*/
int get_number_by_pos(FILE *f, int *p, int pos)
{
    if (fseek(f, pos * sizeof(int), SEEK_SET) != 0)
        return ERR_FUN;
    if (fread(p, sizeof(int), 1, f) == 1)
        return OK;
    return ERR_FUN;
}

/*
По номеру загрузить значение
f - файл
n - значение
pos - позиция
*/
int put_number_by_pos(FILE *f, int n, int pos)
{
    if (fseek(f, pos * sizeof(int), SEEK_SET) != 0)
        return ERR_FUN;
    if (fwrite(&n, sizeof(int), 1, f) == 1)
        return OK;
    return ERR_FUN;
}

/*
сортировка пузырьком
f - файл
a - первое значение
b - второе значение
n - кол-во элементов
*/
int sort(FILE *f)
{
    int a;
    int b;
    int n = 0;
    int size;
    int rc;

    fseek(f, 0L, SEEK_END);
    size = ftell(f);
    n = size / sizeof(int);

    for (int j = 0; j <= n - 1; j++)
    {
        for (int i = 0; i <= n - 2; i++)
        {
            rc = get_number_by_pos(f, &a, i);
            if (rc == ERR_FUN)
                return rc;
            rc = get_number_by_pos(f, &b, i + 1);
            if (rc == ERR_FUN)
                return rc;

            if (a > b)
            {
                rc = put_number_by_pos(f, a, i + 1);
                if (rc == ERR_FUN)
                    return rc;
                rc = put_number_by_pos(f, b, i);
                if (rc == ERR_FUN)
                    return rc;
            }
        }
    }
    return OK;
}

/*
Обработка ошибок

argc - кол-во парамеров
argv - массив параметров
rc - код ошибки
f - файл
*/
int main(int argc, char **argv)
{
    int rc = OK;
    FILE *f;

    srand(time(NULL));

    if (argc != 3)
    {
        usage();
        return ERR_PARAM;
    }

    if (strcmp(argv[1], "c") == 0)
    {
        f = fopen(argv[2], "wb");
        if (f)
        {
            rc = create_array(f);
            if (rc == OK)
                printf("File was created!\n");
            else
                printf("Create error!\n");
            fclose(f);
        }
        else
        {
            rc = ERR_IO;
            printf("Cannot open a file!\n");
        }
    }
    else if (strcmp(argv[1], "p") == 0)
    {
        f = fopen(argv[2], "rb");
        if (f)
        {
            print_array(f);
            fclose(f);
        }
        else
        {
            rc = ERR_IO;
            printf("Cannot open a file!\n");
        }
    }
    else if (strcmp(argv[1], "s") == 0)
    {
        f = fopen(argv[2], "r+b");
        if (f)
        {
            rc = sort(f);
            fclose(f);
            if (rc == OK)
                printf("File was sorted!");
            else
                printf("Error in sort!!");
        }
        else
        {
            rc = ERR_IO;
            printf("Cannot open  file!\n");
        }
    }
	else
	{
		rc = ERR_PARAM;
		usage();
	}

    return rc;
}
