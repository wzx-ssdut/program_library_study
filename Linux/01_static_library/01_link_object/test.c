#include <stdio.h>

#include "add.h"
#include "sub.h"


int main(void) {
    double x = 9.246;
    double y = 2.487;

    printf("add: %f\n", add(x, y));
    printf("sub: %f\n", sub(x, y));

    return 0;
}
