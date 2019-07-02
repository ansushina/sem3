/*
Определите номер подъезда и этажа по номеру квартиры девятиэтажного дома, считая,
что на каждом этаже ровно 4 квартиры, а нумерация квартир начинается с первого
подъезда.
*/

#include <stdio.h>

#define FLOORS (9)
#define FLATS (4)

int main(void)
{
    int n, floor, podezd;

    printf("Input number of flat:");
    scanf("%d", &n);

    n -= 1;
    // Найдем номер подъезда
    podezd = n / FLATS / FLOORS + 1;
    printf("Podezd is %d\n", podezd);
    // Найдем этаж
    floor = n % (FLATS * FLOORS) / FLATS + 1;
    printf("Floor is %d", floor);
    return 0;
}
