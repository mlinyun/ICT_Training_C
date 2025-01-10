#include <stdio.h>

int main(void) {
    // 目标：有一个整型数组 a，有 10 个元素，要求输出数组中的全部元素
    int a[10];
    int i;

    printf("Please enter 10 integer numbers: ");
    // 为数组赋值
    for (i = 0; i < 10; i++) {
        scanf("%d", &a[i]);
    }
    // 打印数组的元素
    for (i = 0; i < 10; i++) {
        printf("%d\t", a[i]); // 数组元素用数组名和下标表示
    }
    printf("\n");
    return 0;
}