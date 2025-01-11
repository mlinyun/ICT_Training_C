#include <stdio.h>

int main(void) {
    // 目标：将字符串 str1 复制为 str2 并输出字符串 str2
    char str1[] = "I am a programmer.";
    char str2[20];
    int i;
    // 使用 i++ 来遍历数组
    for (i = 0; *(str1 + i) != '\0'; i++) {
        *(str2 + i) = *(str1 + i);
    }
    *(str2 + i) = '\0';
    printf("string str1 is: %s\n", str1);
    printf("string str2 is: ");
    for (i = 0; *(str2 + i) != '\0'; i++) {
        printf("%c", *(str2 + i));
    }
    printf("\n");

    return 0;
}