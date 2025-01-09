#include <stdio.h>

int main(void) {
    int i = 3;
    float f = 4.3;
    double d = 7.5;
    double sum;
    sum = 10 + 'a' + i * f - d / 3;
    printf("%lf\n", sum);
    return 0;
}