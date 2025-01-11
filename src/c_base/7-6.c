#include <stdio.h>

int main(void) {
    float average(float array[10]);
    float score[10], aver;
    int i;

    printf("Please enter 10 scores: ");
    for (i = 0; i < 10; i++) {
        scanf("%f", &score[i]);
    }
    aver = average(score); // 注意这里调用函数时，向形参传递的是数组首元素的地址
    printf("Average score is %5.2f\n ", aver);
    return 0;
}

float average(float array[10]) {
    float aver, sum = 0;
    for (int i = 0; i < 10; i++) {
        sum += array[i];
    }
    aver = sum / 10;
    return aver;
}