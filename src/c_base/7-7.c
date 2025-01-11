#include <stdio.h>

int main(void) {
    void fun(int m);
    int m;
    printf("Please enter m: ");
    scanf("%d", &m);
    fun(m);
    return 0;
}

void fun(int m) {
    for (int i = 1; i <= m; i++) {
        if (i % 7 == 0 || i % 11 == 0) {
            printf("%d\t", i);
        }
    }
    printf("\n");
}