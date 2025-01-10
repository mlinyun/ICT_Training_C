#include <stdio.h>

int main(void) {
    // 目标：不交换整形变量的值，而是交换两个指针变量的值
    int a, b;
    int *p1, *p2, *p;
    printf("Please enter two integer number: ");
    scanf("%d%d", &a, &b);

    p1 = &a;
    p2 = &b;

    // 注意：这里是交换指针的值，即指针的指向发生变化，
    // 但是两个变量 a 和 b 的值是没有改变的

    if (a < b) {
        p = p1;
        p1 = p2;
        p2 = p;
    } // p1 和 p2 的值互换（即地址互换）
    // 如果 a < b，通过结果可以观测到 p1 指向 b，p2 指向 a
    printf("a = %d, b = %d\n", a, b);
    printf("max = %d, min = %d\n", *p1, *p2);
    return 0;
}