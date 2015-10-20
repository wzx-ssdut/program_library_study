#include <stdio.h>
#include "zmath.h"

int main(void) {
    double x = 3.496;
    double y = 1.214;

    printf("x+y=%f\n", add(x, y));
    printf("x-y=%f\n", sub(x, y));

    return 0;
}
