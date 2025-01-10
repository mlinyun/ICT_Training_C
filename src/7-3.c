#include <stdio.h>

int main(void) {
    int max4(int a, int b, int c, int d);
    int a, b, c, d, max;
    printf("Please enter 4 integer number: ");
    scanf("%d%d%d%d", &a, &b, &c, &d);
    max = max4(a, b, c, d);
    printf("max = %d\n", max);
    return 0;
}

// 定义 max4 函数
int max4(int a, int b, int c, int d) {
    int max2(int a, int b); // 声明 max2 函数
    int m;
    m = max2(a, b);
    m = max2(m, c);
    m = max2(m, d);
}

// 定义 max2 函数
int max2(int a, int b) {
    return a > b ? a : b;
}
