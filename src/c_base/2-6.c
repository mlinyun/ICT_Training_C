#include <stdio.h>

int main(void){
    // float  a , b;
    double  a , b ; //把 float 改为 double 类型
    a = 123456.789e5;
    /* 相当于 123456.789 * 10^5 */
    b = a + 20;
    /* 20加上无意义 */
    printf("%f\n", b);
    // 在使用浮点数时，要小心数值溢出的问题
    return 0;
}