#include <stdio.h>

int main(void) {
    // 目标：要求通过字符指针变量输出一个字符串和该字符串的第 10 个字符
    char *string = "I love Shiyanlou!";
    printf("%s\n", string);
    printf("%c\n", *(string + 9));
    return 0;
}