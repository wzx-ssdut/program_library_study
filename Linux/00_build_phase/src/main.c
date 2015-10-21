#include <stdio.h>

#include "add.h"
#include "sub.h"

// 注释，以上为文件包含

// 宏定义
#define XXX 1.234
#define YYY 9.763

int main(void) {
    printf("%f + %f = %f\n", XXX, YYY, add(XXX, YYY));
    printf("%f - %f = %f\n", XXX, YYY, sub(XXX, YYY));

    // 条件编译
#if 1
    puts("111111111111111111111111111111");
#else
    puts("000000000000000000000000000000");
#endif

    return 0;
}
