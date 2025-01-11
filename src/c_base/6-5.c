#include <stdio.h>

int main(void) {
    char str[] = "China\nChengdu";

    puts(str);
    printf("Enter a new string: ");
    gets(str); // 有的编译器会报 warning，提示 gets() 函数不安全
    puts(str);
    return 0;
}