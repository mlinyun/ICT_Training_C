#include <stdio.h>

int main(void) {
    float radius, diameter;
    float circumference, area;
    float pi = 3.1415926;

    printf("Input the diameter of the table: ");
    scanf("%f", &diameter);

    radius = diameter / 2;
    circumference = 2.0 * pi * radius;
    area = pi * radius * radius;
    printf("\nThe circumference is %.2f\n", circumference);
    printf("\nThe area is %.2f\n", area);
    return 0;
}