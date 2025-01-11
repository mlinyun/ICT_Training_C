#include <stdio.h>

int main(void) {
    char str1[] = "I am a programmer.";
    char str2[20];
    char *p1, *p2;

    p1 = str1;
    p2 = str2;

    for (; *p1 != '\0'; p1++, p2++) {
        *p2 = *p1;
    }
    *p2 = '\0';

    printf("%s\n", str1);
    printf("%s\n", str2);
    return 0;
}