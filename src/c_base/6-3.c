#include <stdio.h>

int main(void) {
    int i , j, row = 0, colum = 0, max;
    int arr2D[3][4] = {
        {3, 4, 16, 2},
        {7, 5, 1, 9},
        {11, 23, 3, 8}
    };
    max = arr2D[0][0];
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            if (arr2D[i][j] > max) {
                max = arr2D[i][j];
                row = i;
                colum = j;
            }
        }
    }
    printf("max = %d\nrow = %d\ncolum = %d\n", max, row, colum);
    return 0;
}