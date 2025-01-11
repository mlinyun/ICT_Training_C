#include <stdio.h>
#include <string.h>

int main(void) {
    // 目标：任意输入 3 个字符，找出最小的一个
    char string[30];
    // 定义一个二维数组
    // ch[1]、ch[2]、ch[3] 都是一个字符数组，相当于三个字符串
    char ch[3][30];
    int i;
    // 循环读取三行，并且将每行存到 ch[i] 中
    for (i = 0; i < 3; i++) {
        gets(ch[i]); // 有的编译器会报 warning，提示 gets() 函数不安全
    }
    // 将字符串数组的第一个元素复制到 string 中
    strcpy(string, ch[0]);
    for (i = 1; i < 3; i++) {
        if (strcmp(ch[i], string) < 0) {
            strcpy(string, ch[i]);
        }
    }
    printf("The result is : %s\n", string);
    return 0;
}