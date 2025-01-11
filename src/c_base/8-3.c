#include <stdio.h>

int main(void) {
    // 目标：要求实现的功能和 8-2.c 相同，只不过这次我们采用
    // 函数来处理，而且用指针类型的数据做函数的参数
    void swap(int *point_1, int *point_2);

    int a, b;
    int *p1, *p2;

    printf("Please enter two integer number: ");
    scanf("%d%d", &a, &b);
    printf("a = %d, b = %d\n", a, b);

    p1 = &a;
    p2 = &b;

    if (a < b) {
        swap(p1, p2);
    }
    // 如果 a < b，那么 a 和 b 的值进行了交换
    printf("max = %d, min = %d\n", a, b);
    // 如果打印了 *p1 和 *p2 我们会发现，p1 仍指向 a，p2 仍指向 b
    printf("a = %d = %p = %p, b = %d = %p = %p\n", a, &a, p1, b, &b, p2);

    return 0;
}

void swap(int *point_1, int *point_2) {
    int temp;
    // 注意：这里是交互指针所指变量的值
    // 即指针的指向没有发生改变
    // 但是变量 a 和变量 b 的值改变了
    temp = *point_1;
    *point_1 = *point_2;
    *point_2 = temp;
}