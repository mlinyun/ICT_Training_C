#include <stdio.h>

int main(void) {
    char grade; // 等级
    scanf("%c", &grade);
    printf("You score: ");
    switch (grade) {
        case 'a':
            printf("85 ~ 100\n");
            break;
        case 'b':
            printf("70 ~ 84\n");
            break;
        case 'c':
            printf("60 ~ 69\n");
            break;
        case 'd':
            printf("< 60\n");
            break;
        default:
            printf("error!\n");
    }
    return 0;
}