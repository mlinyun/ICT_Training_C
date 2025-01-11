#include <stdio.h>

int main(void) {
    // 目标：定义一个字符数组，在其中存放字符串 “I love Shiyanlou!”，
    // 输出该字符串和第 10 个字符
    char string[] = "I love Shiyanlou!";
    
    printf("%s\n", string);
    printf("%c\n", string[9]);

    return 0;
}