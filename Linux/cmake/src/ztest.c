#include <stdio.h>
#include "zmath.h"


int main(void) {
    double x = 9.99;
    double y = 7.25;

    printf("add: %f\n", add(x, y));
    printf("subtract: %f\n", subtract(x, y));
    printf("multiply: %f\n", multiply(x, y));
    printf("divide: %f\n", divide(x, y));

    return 0;
}

