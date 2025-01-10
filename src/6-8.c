#include <stdio.h>

int main(void) {
    int num[20];
    int sum; // 总和
    double ave; // 平均数
    int count = 0; // 标记大于平均数的个数
    // 输入数据
    for (int i= 0; i < 20; i++) {
        scanf("%d", &num[i]);
    }
    // 求和
    for (int i = 0; i < 20; i++) {
        sum += num[i];
    }
    // 平均数
    ave = sum * 1.0 / 20;
    // 找出大于平均数的个数
    for (int i = 0; i < 20; i++) {
        if (num[i] > ave) {
            count++;
        }
    }
    printf("ave = %.2lf, num bigger than ave is %d\n", ave, count);
    return 0;
}