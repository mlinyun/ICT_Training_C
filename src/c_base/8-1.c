#include <stdio.h>

int main(void) {
    int a = 100, b = 10;
    // 定义指向整型数据的指针变量 point_1, point_2
    int *point_1, *point_2;

    // 把变量 a 的地址赋值给指针变量 point_1
    point_1 = &a;
    // 把变量 b 的地址赋值给指针变量 point_2
    point_2 = &b;
    
    // 打印 a 和 b 的值
    printf("a = %d, b = %d\n", a, b);
    // 输出 a 和 b 在内存中的地址
    printf("a = %p, b = %p\n", point_1, point_2);
    // 通过指针输出 a 和 b 的值
    printf("a = *point_1 = %d, b = *point_2 = %d\n", *point_1, *point_2);
    return 0;
}