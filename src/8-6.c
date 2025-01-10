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

    for (i = 0; i < 10; i++) {
        printf("%d\t", *(a + i)); // 通过数组名和元素序号计算元素地址，再找该元素
    }
    printf("\n");
    return 0;
}