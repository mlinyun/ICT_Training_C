#include <stdio.h>

int main(void) {
    // 函数声明
    int max(int x, int y);
    int a[10];
    int m, n, i;

    printf("Please enter 10 integer number: ");
    for (i = 0; i < 10; i++) {
        scanf("%d", &a[i]);
    }
    m = a[0];
    for (i = 1; i < 10; i++) {
        if (max(m, a[i]) > m) { // 若 max 函数返回值大于 m
            m = max(m, a[i]); // max 函数的返回值取代 m
            n = i; // 把数组元素的序号记下来，放到 n 中
        }
    }
    printf("The largest number is %d\nit is the %dth number \n", m, n + 1);

    return 0;
}

// 比较两个整数的大小
int max(int x, int y) {
    return (x > y ? x : y);
}