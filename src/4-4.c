#include <stdio.h>

int main(void) {
    // 产品的单价
    double unit_price = 3.5;
    // 3 个级别的折扣
    double discount1 = 0.05;
    double discount2 = 0.1;
    double discount3 = 0.15;
    // 最终价格
    double total_price = 0.0;
    // 购买产品数量
    int quantity = 0;
    printf("Enter the number that you want to buy: ");
    scanf("%d", &quantity);

    total_price = quantity * unit_price * (1.0 - (quantity > 50 ? discount3 :(quantity > 20 ? discount2 : (quantity > 10 ? discount1 : 0.0))));

    printf("The price for %d is %7.2f\n", quantity, total_price);
    return 0;
}