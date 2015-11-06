#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

int main(void) {
    void* handle = NULL;
    double (*add)(double, double);
    char* error;

    // 全路径，使用任意名称都可以
    //handle = dlopen("/usr/local/lib/libzmath.so", RTLD_LAZY);  // linker name
    //handle = dlopen("/usr/local/lib/libzmath.so.1", RTLD_LAZY);  // soname
    //handle = dlopen("/usr/local/lib/libzmath.so.1.0.0", RTLD_LAZY); // real name

    //handle = dlopen("libzmath.so", RTLD_LAZY); // linker name
    //handle = dlopen("libzmath.so.1", RTLD_LAZY); // soname
    //handle = dlopen("libzmath.so.1.0.0", RTLD_LAZY); // real name : cannot find
	// 使用命令strings /etc/ld.so.cache | grep libzmath可以查看能使用的名称
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

