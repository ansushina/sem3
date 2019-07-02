/*
Рассчитать дисперцию чисел. Дисперсия и математическое ожидание считаются отдельно.
*/

#include <stdio.h>
#include <math.h>

#define OK 0
#define ERR_IO 1
#define ERR_PARAM 2

/*
Получить математическое ожидание
f - файл
p - указатель на значение математического ожидания
n - кол-фо элементов
a - текущий элемент
s - сумма элементов 
*/
int get_math_oz(FILE *f, float *p)
{
    int n = 0;
    float a;
    float s = 0;

    while (fscanf(f, "%f", &a) == 1)
    {
        s += a;
        n += 1;
    }
    if (n > 0)
    {
        *p = s / n;
        return OK;
    }
    return ERR_IO;
}

/*
Получить дисперсию

f - файл
p - указатель на значени дисперсии
m - математическое ожидание
n - кол-во элементов
s - сумма квадратов разности среднего и текущего значений
a - текущее значение 
*/
int get_dispersia(FILE *f, float *p, float m)
{
    int n = 0;
    float s = 0;
    float a;

    while (fscanf(f, "%f", &a) == 1)
    {
        s += (a - m) * (a - m);
        n += 1;
    }
    if (n > 0)
    {
        *p = sqrt(s / n);
        return OK;
    }
    return ERR_IO;
}

/*
обработка ошибок 

argc - кол-во параметров
argv - массив параметров
f - файл 
rc -код ошибки 
m - математическое ожидание 
d - дисперсия
*/
int main(int argc, char **argv)
{
    FILE* f;
    int rc;
    float m;
    float d;

    if (argc != 2)
    {
        printf("main.exe file_name\n");
        return ERR_PARAM;
    }

    f = fopen(argv[1], "r");

    if (f == NULL)
    {
        printf("Cannot open a file!\n");
        rc = ERR_IO;
    }
    else
    {
        rc = get_math_oz(f, &m);
        if (rc == OK)
        {
            rewind(f);
            rc = get_dispersia(f, &d, m);
            if (rc == OK)
                printf("Dispersia is %f\n", d);
            else
                printf("No numbers in file!\n");
        }
        else
        {
            printf("No numbers in file!\n");
        }
        fclose(f);
    }
    return rc;
}
