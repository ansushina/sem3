/*
Определить принадлежит ли точка отрезку.
*/

#include <stdio.h>
#include <math.h>

#define OK 0
#define ERR_IO 1
#define ERR_NE_OTREZOK 2
#define EPS 0.000001
#define YES 1
#define NO 0
/*
Функция проверки принадлежит ли точка отрезку
xa,ya - точка A
ya,yb - точка B
x, y - точка X
p - Векторное произвеление векторов AX и AB
*/
int tochka(float xa, float ya, float xb, float yb, float x, float y)
{
    float p;
    //Проверим находится ли точка между A и B
    if ((xa <= x && x <= xb) || (xb <= x && x <= xa))
    {
        // Найдем векторное произведение AX и AB
        // Если оно рано нулю, значит веторы коллинеары
        p = (x - xa) * (yb - ya) - (y - ya) * (xb - xa);
        if (fabs(p) <= EPS)
        {
            return YES;
        }
        else
        {
            return NO;
        }
    }
    else
    {
        return NO;
    }
}
/*
Проверяет верно ли введены значения
xa,ya - точка A
ya,yb - точка B
x, y - точка X
rc - код ошибки
*/
int main(void)
{
    float xa, ya;
    float xb, yb;
    float x, y;
    int p;
    int rc = OK;

    printf("Input xa, ya:");
    if (scanf("%f%f", &xa, &ya) == 2)
    {
        printf("Input xb, yb:");
        if (scanf("%f%f", &xb, &yb) == 2)
        {
            printf("Input x, y:");
            if (scanf("%f%f", &x, &y) == 2)
            {
                if (fabs(xa - xb) >= EPS || fabs(ya - yb) >= EPS)
                {
                    p = tochka(xa, ya, xb, yb, x, y);
                    if (p == YES)
                    {
                        printf("Yes! %d \n", p);
                    }
                    else if (p == NO)
                    {
                        printf("No! %d \n", p);
                    }
                }
                else
                {
                    rc = ERR_NE_OTREZOK;
                    printf("A and B must be different!\n");
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
            rc = ERR_IO;
            printf("Input error!\n");
        }
    }
    else
    {
        rc = ERR_IO;
        printf("Input error!\n");
    }
    return rc;
}
