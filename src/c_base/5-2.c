#include <stdio.h>

int main(void) {
    int i = 1, sum = 0;
    do {
        sum += i;
        i++;
    } while (i <= 100);
    printf("sum = %d\n", sum);
    return 0;
}