#include <stdio.h>

#define PI 3.14159

int main(){
    // 初始化数据
    float r;
    printf("请输入 r: ");
    // 需要输入 r =2.5
    scanf("%f", &r);
    int h;
    printf("请输入 h: ");
    // 需要输入 h =3
    scanf("%d", &h);
    float area, cir, vol;
    // 计算
    cir = PI * r * 2;
    area = PI * r * r;
    vol = area * h;

    printf("cir = %.2f, area = %.2f, vol = %.2f\n", cir, area, vol);
    return 0;
}