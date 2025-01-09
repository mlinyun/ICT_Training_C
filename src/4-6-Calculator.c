#include <stdio.h>

int main(void) {
    double number1 = 0.0;     // 定义第一个操作数
    double number2 = 0.0;     // 定义第二个操作数
    char operation = 0;       // operation 必须是 '+' '-' '*' '/' 或 '%'

    printf("Enter the calculation: ");
    scanf("%lf %c %lf", &number1, &operation, &number2);

    switch(operation) {
        case '+':
            printf(" = %lf\n", number1 + number2);
            break;
        case '-':
                printf(" = %lf\n", number1 - number2);
                break;
        case '*':
                printf(" = %lf\n", number1 * number2);
                break;
        case '/':
                if(number2 == 0) {
                    printf("\n\n\aDivision by zero error!\n");
                } else {
                    printf(" = %lf\n", number1 / number2);
                }
                break;
        case '%':
                if((long)number2 == 0) {
                    printf("\n\n\aDivision by zero error!\n");
                } else {
                    printf(" = %ld\n", (long)number1 % (long)number2);
                }
                break;
        default:
            printf("\n\n\aDivision by zero error!\n");
            break;
    }

    return 0;
}