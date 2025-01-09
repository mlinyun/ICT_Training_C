#include <stdio.h>

int main(void) {
    int a, b, c;

    printf("Please enter a value: ");
    scanf("%d", &a);
    printf("Please enter b value: ");
    scanf("%d", &b);
    c = a + b;
    printf("c = a + b = %d + %d = %d\n",a, b, c);
    return 0;
}