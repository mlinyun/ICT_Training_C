#include <stdio.h>

int main(void) {
    int i, num[10]; // 定义数组 num
    // 给数组 num 赋值
    for (i = 0; i < 10; i++) {
        num[i] = i + 1;
    }
    // 逆序输出数组 num 的元素
    for (i = 9; i >= 0; i--) {
        printf("%d\t", num[i]);
    }
    printf("\n");
    return 0;
}