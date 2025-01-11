#include <stdio.h>

int fun(int a, int b) {
    int c;
    c = a % 10 * 1000 + a / 10 * 10 + b / 10 * 100 + b % 10;
    printf("%d\n", c);
}

int main(void) {
    int a, b;
    scanf("%d%d", &a, &b);

    // a, b 必须是两位数
    if(a < 10 || a > 99 || b < 10 || b > 99) {
        printf("Enter error!");
        return 0;
    }

    //调用函数
    fun(a,b);

    return 0;
}