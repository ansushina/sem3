/*
Вычислить значение x[0] + x[0]*x[1] +x[0]*x[1]*x[2]+...+x[0]*x[1]*x[2]...x[m],
где x[i] - элементы массива x из n элементов, m - индекс первого
отрицательного элемента этого массива либо число n-1,
если такого элемента в массиве нет.
*/

#include <stdio.h>

#define N 100

#define OK 0
#define ERR_IO 1
#define ERR_PARAM 2
#define ERR_RANGE 3

int read_array_new(FILE *f, int *pbeg, int **pend);

void get_sum(const int *pbeg, const int *pend, int *sum);


/*
Обработка ошибочных ситуаций
argc - количество параметров
argv - параметры
f - файл
x - массив
sum - значение
rc - код ошибки
rend - указатель на запоследний элемент
*/
int main(int argc, char **argv)
{
    FILE *f;
    int x[N];
    int sum;
    int rc;
    int *pend;

    if (argc != 2)
    {
        printf("main.exe <file-name>!\n");
        return ERR_PARAM;
    }

    f = fopen(argv[1], "r");
    if (f)
    {
        rc = read_array_new(f, x, &pend);
        fclose(f);
        if (rc == ERR_RANGE)
            printf("More then hundred elements in file!\n");
		if (x != pend)
		{
            get_sum(x, pend, &sum);
            printf("sum = %d", sum);
		}
		else
		{
			rc = ERR_IO;
			printf("No elements in file!\n");
		}
    }
    else
    {
        rc = ERR_IO;
        printf("File can't be open!");
    }
    return rc;
}

