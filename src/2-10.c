#include <stdio.h>

int main(void) {
    int speed = 40;
    double time = 1.5;
    double len;
    len = speed * time;
    printf("小明家与公司的距离是 %.2f 公里\n", len);
    return 0;
}