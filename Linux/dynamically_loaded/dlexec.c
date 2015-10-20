#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

int main(void) {
    void* handle = NULL;
    void (*hello)();
    char* error;

    handle = dlopen("/tmp/hello", RTLD_LAZY);
    if (!handle) {
        fputs(dlerror(), stderr);
        exit(1);
    }

    dlerror(); // clear error
    hello = dlsym(handle, "add");
    if ((error = dlerror()) != NULL) {
        fputs(error, stderr);
        exit(1);
    }

    hello();

    dlclose(handle);

    return 0;
}

