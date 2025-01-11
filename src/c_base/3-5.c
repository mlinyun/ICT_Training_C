#include <stdio.h>
#include <math.h> // 程序中要求调用平方根函数 sqrt

int main(void) {
    double a, b, c, disc, x1, x2, p, q;
    scanf("%lf%lf%lf", &a, &b, &c);
    disc = b * b - 4 * a * c;
    p = -b / (2.0 * a);
    q = sqrt(disc) / (2.0 * a);
    x1 = p + q;
    x2 = p- q;
    printf("x1 = %7.2lf\nx2 = %7.2lf\n", x1, x2);
    // 编译时需要注意，在 Linux 系统下，C 源文件若调用了 math 库里的函数，
    // 则编译时要加上 -lm （是字母 l ，不是数字 1），表示链接到 math 库
    // gcc -o 3-5 3-5.c -lm
    return 0;
}