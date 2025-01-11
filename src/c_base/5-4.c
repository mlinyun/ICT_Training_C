#include <stdio.h>

int main(void) {
    int i, sum = 0;
    printf("please enter i: ");
    scanf("%d", &i);
    do {
        sum += i;
        i++;
    } while (i <= 100);
    printf("sum = %d\n", sum);
    return 0;
}