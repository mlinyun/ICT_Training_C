#include <stdio.h>

int main(void) {
    char a, b;  // 定义字符变量 a 和 b
    // 把字符常量 'c' 赋值给 a
    a = 'c';
    b = 121;
    printf("%c, %c\n", a, b);
    printf("%d,%d\n",a,b); // %d 表示以有符号十进制形式输出整数型
    return 0;
}