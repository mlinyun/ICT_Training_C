#include <stdio.h>

int main(void) {
    int a[10];
    int *p;
    int i;

    printf("Please enter 10 integer numbers: ");
    // 为数组赋值
    for (i = 0; i < 10; i++) {
        scanf("%d", &a[i]);
    }

    for (p = a; p < a + 10; p++) {
        printf("%d\t", *p); // 用指针指向当前的数组元素
    }
    printf("\n");
    return 0;
}