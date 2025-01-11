#include <stdio.h>

int main(void) {
    int max(int a, int b); // 声明 max 函数
    int a = 10, b = 20;
    int c;
    c = max(a, b); // a, b 为实际参数；调用 max 函数，传递的是 a，b 的值给 max 函数
    printf("%d\n", c);
    return 0;
}

// int 代表的是返回值是 int 型
int max(int a, int b) {
    int max = a > b ? a : b;
    return max; // 返回 max
}