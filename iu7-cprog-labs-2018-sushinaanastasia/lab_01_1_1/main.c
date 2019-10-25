/* 
Даны основания равнобедренной трапеции и угол при большем основании. Найти
площадь трапеции.
*/

#include <stdio.h>
#include <math.h>

#define ODNA_VTORAIA (0.5f)
#define PI (3.1415926535)
#define GRADUSOV_V_PI (180)

int main(void)
{
    float a, b, alpha, c, h, s;

    setbuf(stdout, NULL);
    printf("a  b - base of trapeziod.\nalpha - corner.\n");
    printf("Enter a,b and alpha:\n");
    scanf("%f%f%f", &a, &b, &alpha);
    //Переведем градусы в радианы
    alpha *= PI/GRADUSOV_V_PI;
    // Найдем высоту трапеции
    c = fabs((b - a) * ODNA_VTORAIA);
    h = c * tan(alpha);
    // Найдем площадь
    s = ODNA_VTORAIA * h * (a + b);
    printf("Square = %.5f", s);

    return 0;
}
