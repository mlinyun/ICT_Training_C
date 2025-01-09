#include <stdio.h>

int main(void) {
    int i, j, n = 0;

    for (i = 1; i <= 4; i++) {
        for (j = 1; j <= 5; j++) {
            printf("%d\t", ++n);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}