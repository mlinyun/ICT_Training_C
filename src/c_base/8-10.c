#include <stdio.h>

int main(void) {
    void change(int *x, int n);
    int i , a[10] = {3, 7, 9, 11, 0, 6, 7, 5, 4, 2};
    printf("The original array:\n");
    for (i = 0; i < 10; i++) {
        printf("%d\t", a[i]);
    }
    printf("\n");

    change(a, 10);

    printf("The array has been inverted:\n");
    for (i = 0; i < 10; i++) {
        printf("%d\t", a[i]);
    }
    printf("\n");
    return 0;
}

void change(int *x, int n) {
    int *p, temp, *i, *j, m = (n - 1) / 2;
    i = x;
    j = x + n - 1;
    p = x + m;

    for (; i <= p; i++, j--) {
        temp = *i;
        *i = *j;
        *j = temp;
    }
}