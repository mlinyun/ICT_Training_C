#include <stdio.h>

int main(void) {
    // 定义油箱的容积为浮点类型变量 tank_volume
    float tank_volume;
    // 定义油的密度为浮点类型变量 oil_density
    float oil_density;
    float oil_kg;
    float area;

    // 给变量 tank_volume 赋值
    tank_volume = 0.1;
    // 给变量 oil_density 赋值
    oil_density = 850;
    // 求 tank_volume 和 oil_density 的积并赋值给 oil_kg
    oil_kg = tank_volume * oil_density;
    // 求 oil_kg/0.85 的商并赋值给 area
    area = oil_kg / 0.85;
    printf("Most farming is %.2f mu\n", area);
    return 0;
}