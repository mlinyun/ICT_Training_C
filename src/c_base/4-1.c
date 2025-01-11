#include <stdio.h>
#include <math.h>

int main(void) {
    double a, b, c, disc, p, q, x1, x2;
    scanf("%lf%lf%lf", &a, &b, &c);
    disc = b * b - 4 * a * c;
    if (disc < 0) {
        printf("This equation hasn't real root!\n");
    } else {
        p = -b / (2.0 * a);
        q = sqrt(disc) / (2.0 * a);
        x1 = p + q;
        x2 = p - q;
        printf("x1 = %7.2lf\nx2 = %7.2lf\n", x1, x2);
    }
    // gcc -o 4-1 4-1.c -lm
    return 0;
}