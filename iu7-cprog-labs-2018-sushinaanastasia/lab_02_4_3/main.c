/*
Вычислить с точностью eps значение приближенное значение функции s(x),
точное значение функции f(x) и абсолютную и отночительную погрешности.
*/

#include <stdio.h>
#include <math.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

/*
Функция вычисление приближенного значения s(x).
x - аргумент
eps - погрешность
sum - сумма
k - элемент
n - номер элемента
*/

float s(float x, float eps)
{
    float sum = 1.0;
    float k = 1;
    float n = 1;

    while (fabs(k) > eps)
    {
        n += 1;
        k *= (-1) * (n + 1) * x / (n - 1);
        sum += k;
    }
    sum -= k;
	
    return sum;
}

/*
Функция f(x) вычисляет точное значение
x - аргумент
*/
float f(float x)
{
    return pow(1 + x, -3);
}

/*
Проверка значений и основные действия
x - аргумент
eps - точность
sum - значение s(x)
fun - значение f(x)
a - абсолютная погрешность
o - относительная погрешность
*/
int main(void)
{
    float x, eps;
    float sum, fun, a, o;
    int rc = OK;

    printf("Input x(abs(x) less then one):");
    if (scanf("%f", &x) == 1)
    {
        if (fabs(x) < 1)
        {
            printf("Input eps (eps from zero to one):");
            if (scanf("%f", &eps) == 1)
            {
                if (eps > 0 && eps <= 1)
                {
                    sum = s(x, eps);
                    //printf("s(x) = %f\n", sum);
                    fun = f(x);
                    //printf("f(x) = %f\n", fun);
                    a = fabs(fun - sum);
                    o = a / fabs(fun);
                    //printf("Absolute error is %f\n", a);
                    //printf("Relative error is %f\n", o);
					printf("%f %f %f %f", sum, fun, a, o);
                }
                else
                {
                    rc = ERR_RANGE;
                    printf("eps from zero to one!\n");
                }
            }
            else
            {
                rc = ERR_IO;
                printf("Inrut error!\n");
            }
        }
        else
        {
            rc = ERR_RANGE;
            printf("abs(x) less then one!\n");
        }
    }
    else
    {
        rc = ERR_IO;
        printf("Input error!\n");
    }
    return rc;
}
