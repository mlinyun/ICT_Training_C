#include <stdio.h>

int main(void) {
    int i, j;
    // 正金字
    for (i = 1; i <= 4; i++) { // 控制金字塔的层数，输出4层，可以改变输出任意层
        for (j = 1; j <= 4-i; j++) // 控制金字塔每层前面输出的空格数
            printf(" ");
        for (j = 1; j <= 2 * i - 1; j++) // 控制金字塔每层需要打印'*'的个数
            printf("*");
        printf("\n"); // 一层金字塔输出完毕，换行继续输出下一层
    }
    // 倒金字
    for (i = 3; i  >0; i--) {            // 控制金字塔的层数，输出3层，可以改变输出任意层
        for(j = 1; j <= 4 - i; j++)
            printf(" ");
        for (j = 1; j <= 2 * i - 1; j++)
            printf("*");
        printf("\n");
    }
    return 0;
}