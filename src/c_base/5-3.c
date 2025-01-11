#include <stdio.h>

int main(void) {
    int i, sum = 0;
    printf("Please enter i: ");
    scanf("%d", &i);
    while (i <= 100) {
        sum += i;
        i++;
    }
    printf("sum = %d\n", sum);
    return 0;
}