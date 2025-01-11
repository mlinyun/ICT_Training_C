#include <stdio.h>

int main(void) {
    
    void printstar(); // 声明 printstar 函数
    void printmessage(); // 声明 printmessage 函数

    printstar(); // 调用 printstar 函数
    printmessage(); // 调用 printmessage 函数
    printstar(); // 调用 printstar 函数

    return 0;
}

// 定义 printstar 函数
void printstar() {
    printf("*************\n");
}

// 定义 print_message 函数
void printmessage() {
    char message[] = "how do you do!";
    printf("%s\n", message);
}