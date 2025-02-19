#include <stdio.h>

int main(void) {
    // 目标：采用 8-3.c 的方法在函数中改变 3 个变量的值。
    // 用 swap 函数交换两个变量的值，用 exchange 函数
    // 改变着 3 个变量的值
    void exchange(int *q1, int *q2, int *q3);
    int a, b, c;
    int *p1, *p2, *p3;
    printf("Please enter 3 integer number: ");
    scanf("%d%d%d", &a, &b, &c);

    p1 = &a;
    p2 = &b;
    p3 = &c;

    exchange(p1, p2, p3);

    printf("The order is : %d, %d, %d\n", a, b, c);
    return 0;
}

void exchange(int *q1, int *q2, int *q3) {
    void swap(int *p1, int *p2);
    if (*q1 < *q2) swap(q1, q2);
    if (*q1 < *q3) swap(q1, q3);
    if (*q2 < *q3) swap(q2, q3);
}

void swap(int *p1, int *p2) {
    int temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}