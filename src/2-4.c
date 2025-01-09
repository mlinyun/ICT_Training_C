#include <stdio.h>
#include <float.h>

int main(void) {
    // float 的取值范围
    printf("The size of the smallest positive non-zero value of type float is %.3e\n", FLT_MIN);
    printf("The size of the largest value of type float is %.3e\n", FLT_MAX);
    return 0;
}