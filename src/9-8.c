#include <stdio.h>

int main(void) {
    int num;
    scanf("%d", &num);
    // 初始化月份
    const char *month[] = {
        "January", "February", "March",
        "April", "May", "June", "July",
        "August", "September", "October",
        "November","December"
    };

    // 打印指定月份
    printf("%s\n", *(month + num - 1));

    return 0;
}