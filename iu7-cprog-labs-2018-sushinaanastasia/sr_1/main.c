/*
Вычисляет площадь прямоугольника. Вычисляет площадь круга.
*/
#include <stdio.h>
#define PI 3.14
float sqr(float a, float b)
{
     float sr = a * b;
     return sr;
}

float sqc(float r)
{
    float sc = 2 * PI * r;
    return sc;
}
int main(void)
{
    float a, b, r;
    float sr, sc, s;
    printf("Input a and b: ");
    scanf("%f%f", &a, &b);
    sr = sqr(a, b);
    printf("Square of rectangle is %8.3f\n", sr);
    printf("Input r: ");
    scanf("%f", &r);
    sc = sqc(r);
    printf("Square of circle is %8.3f\n", sc);
    s = sr + sc;
    printf("All square is %8.3f\n", s);
    return 0;
}
