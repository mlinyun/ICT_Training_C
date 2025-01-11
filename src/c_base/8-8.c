#include <stdio.h>

int main(void) {
    int a[10];
    int *p;
    int i;

    p = a;

    printf("Please enter 10 integer numbers: ");
    // 为数组赋值
    for (i = 0; i < 10; i++) {
        scanf("%d", p++);
    }

    p = a; // 这一步很关键
    for (i = 0; i < 10; i++, p++) {
        printf("%d\t", *p);
    }
    printf("\n");
    return 0;
}