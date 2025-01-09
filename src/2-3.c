#include <stdio.h>

int main(void) {
    // sizeof() 的值的类型不是 int 型，而是 long unsigned int
    printf("%ld\n", sizeof(int));
    printf("%ld\n", sizeof(short));
    printf("%ld\n", sizeof(long));
    return 0;
}