#include <stdio.h>

int main(void) {
    char c;
    printf("Input an uppercase letter: ");
    c = getchar();
    putchar(c + 32);
    putchar('\n');
    return 0;
}