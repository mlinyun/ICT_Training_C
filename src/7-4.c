#include <stdio.h>

int main(void) {
    int fac(int n);
    int n, y;

    printf("please input an integer number : ");
    scanf("%d", &n);

    if (n < 0) {
        printf("data error"); // n 不小于 0
    } else {
        y = fac(n);
        printf("%d != %d\n", n, y);
    }
    return 0;
}

// 阶乘函数
int fac(int n) {
    int f;
    if (n == 0 || n == 1) {
        f = 1;
    } else {
        f = fac(n - 1) * n;
    }
    return f;
}