#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

int main(void) {
    void* handle = NULL;
    double (*add)(double, double);
    char* error;

    //handle = dlopen("libzmath.so", RTLD_LAZY); // 通过链接名无法找到共享库
    //handle = dlopen("libzmath.so.1.0.0", RTLD_LAZY); // 真名也不行...
    handle = dlopen("libzmath.so.1", RTLD_LAZY);
    if (!handle) {
        fputs(dlerror(), stderr);
        exit(1);
    }

    dlerror(); // clear error
    add = dlsym(handle, "add");
    if ((error = dlerror()) != NULL) {
        fputs(error, stderr);
        exit(1);
    }

    printf("%f\n", add(2.2, 5.4));

    dlclose(handle);

    return 0;
}

