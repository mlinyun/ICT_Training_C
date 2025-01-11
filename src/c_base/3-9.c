#include <stdio.h>

int main(void) {
    // 初始化字符
    char str[9] = {'S', 'h', 'i', 'Y', 'a', 'n', 'l', 'o', 'u'};

    // 每个字符 +1
    for (int i = 0; i < 9; i++) {
        str[i] += 1;
    }

    // 使用 printf 打印
    for (int i = 0; i < 9; i++) {
        printf("%c", str[i]);
    }

    printf("\n");

    // 使用 putchar 打印
    for (int i = 0; i < 9; i++) {
        putchar(str[i]);
    }

    printf("\n");
    
    return 0;
}