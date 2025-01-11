#include <stdio.h>

int main(void) {
    // 定义 copy_string  函数
    void copy_string(char from[], char to[]);
    char a[] = "I am a teacher";
    char b[] = "You are a programmer";
    printf("string a = %s\nstring b = %s\n", a, b);
    printf("copy string a to string b:\n");
    copy_string(a, b);
    printf("string a = %s\nstring b = %s\n", a, b);
    return 0;
}

// copy_string  函数：用来实现字符串赋复制
void copy_string(char from[], char to[]) {
    int i = 0;
    while (from[i] != '\0') {
        to[i] = from[i];
        i++;
    }
    to[i] = '\0';
}