#include <stdio.h>

int main(void) {
    int i, j, temp, LearnTime[10];
    printf("Please enter 10 number:\n");
    for (i = 0; i < 10; i++) {
        scanf("%d", &LearnTime[i]);
    }

    // 使用冒泡排序对数组进行排序
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9 - i; j++) {
            if (LearnTime[j] > LearnTime[j + 1]) {
                temp = LearnTime[j];
                LearnTime[j] = LearnTime[j + 1];
                LearnTime[j + 1] = temp;
            }
        }
    }

    // 排序之后的数组
    printf("the sorted number:\n");
    for (i = 0; i < 10; i++) {
        printf("%d\t", LearnTime[i]);
    }
    printf("\n");
    return 0;
}