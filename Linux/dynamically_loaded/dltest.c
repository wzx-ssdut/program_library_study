#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

int main(void) {
    void* handle = NULL;
    double (*cosine)(double);
    char* error;

    handle = dlopen("libm.so.6", RTLD_LAZY);
    if (!handle) {
        fputs(dlerror(), stderr);
        exit(1);
    }

    dlerror(); // clear error
    cosine = dlsym(handle, "cos");
    if ((error = dlerror()) != NULL) {
        fputs(error, stderr);
        exit(1);
    }

    printf("%f\n", cosine(2.0));

    dlclose(handle);

    return 0;
}
