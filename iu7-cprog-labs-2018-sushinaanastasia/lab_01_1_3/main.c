/*
Смешано v1 литров воды температуры t1 с v2 литрами воды температуры t2. Найти
объем и температуры образовавшейся смеси.
*/

#include <stdio.h>

int main(void)
{
    float v1, v2, t1, t2, v, t;

    printf("Input v1 and t1:");
    scanf("%f%f", &v1, &t1);
    printf("Input v2 and t2:");
    scanf("%f%f", &v2, &t2);

    // Посчет объема
    v = v1 + v2;
    printf("V = %.2f\n", v);
    // Подсчет температуры
    t = (v1 * t1 + v2 * t2) / v;
    printf("t = %.2f", t);
    return 0;
}
