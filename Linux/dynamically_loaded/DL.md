# Dynamically Loaded (DL) Libraries

Dynamically loaded (DL) libraries are libraries that are loaded at times other than
during the startup of a program.
动态链接库是不在程序启动时加载的库。

实现插件和模块时，它们特别有用，因为它们允许在需要的时候再加载插件。

They're also useful for implementing interpreters that wish to occasionally compile
their code into machine code and use the compiled version for efficiency purposes,
all without stopping. For example, this approach can be useful in implementing a
just-in-time compiler or multi-user dungeno (MUD).

如果想实现一个解释器，将代码编译为机器码，然后使用这些机器码来提高性能，而不需要停止。

In Linux, DL libraries aren't actually special from the point-of-view of their format;
they are built as standard object files or standard shared libraries as discussed above.
在Linux中，DL库在格式上看并不特殊；它们被构建成标准目标文件或者标准共享文件。

The main difference is that the libraries aren't automatically loaded at program link
time or start-up, there is an API for opening a library, looking up symbols, handling
errors, and closing the library. C users will need to include the header file `<dlfcn.h>`
to use this API.
主要的区别在于DL库不是在程序链接或启动时自动加载的。
有一组API用于打开一个库，查找符号，处理错误和关闭库。
C用户需要包含`<dlfcn.h>`来使用这个API。

## dlopen()
```c
void* dlopen(const char* filename, int flag);
```
The `dlopen` function opens a library and prepares it for use.
如果文件名以`/`开始，`dlopen`会直接尝试使用它。否则，`dlopen`会按照如下顺序查找库：
1. `LD_LIBRARY_PATH`环境变量指定的目录；
2. `/etc/ld.so.cache`中指定的库列表（通过`/etc/ld.so.conf`生成）；
3. `/lib`，紧接着`/usr/lib`。

在`dlopen`函数中，`flag`必须是`RTLD_LAZY`或`RTLD_NOW`。
`RTLD_LAZY` : resolve undefined symbols as code from the dynamic library is executed
`RTLD_NOW`  : resolve all undefined symbols before `dlopen` returns and fail if this cannot be done
`RTLD_GLOBAL`可以和`flag`进行或(OR)操作。Meaning that the external symbols defined in the library will be mad available to subsequently loaded libraries.

`dlopen`函数的返回值是一个句柄，这个值被其他DL库函数使用，这个句柄应该被视为不透明值。
`dlopen`会返回`NULL`，如果它尝试加载库但是没有成功。使用的时候需要检查这个值。
如果一个库被多次打开，`dlopen`会返回相同的句柄。


## dlerror()
    char* dlerror(void);

通过调用`dlerror`函数可以得到错误，一个字符串，用于表示上一次`dlopen`，`dlsym`和`dlclose`执行后
的错误信息。当`dlerror`调用之后，错误信息将被清除，再次调用`dlerror`会得到NULL。
Errors can be reported by calling dlerror(), which returns a string describing the error from the
last call to dlopen(), dlsym(), or dlclose(). One oddity is that after calling dlerror(), future
calls to dlerror() return NULL until another error has been encountered.


## dlsym()
    void* dlsym(void* handle, const char* symbol);
加载一个DL库但是却不使用它是毫无意义的。使用DL库的主要函数是`dlsym`，它在打开的库中查找符号的值。
如果找不到符号，`dlsym`会返回NULL。如果你知道这个symbol不可能为`NULL`或`zero`，这样不会有歧义，
但是如果这个值可以为`NULL`，那么无法确定有没有这个symbol，还是这个symbol的值为`NULL`。标准解决
方案是先调用`dlerror`清除错误信息，然后调用`dlsym`查找符号，然后再次调用`dlerror`来确定是否有错误
发生。
```c
dlerror(); // clear error code
s = (actual_type)dlsym(handle, symbol_being_searched_for);
if ((err = dlerror()) != NULL) {
    // handle error, the symbol wasn't found.
}
else {
    // symbol found, its value is in s
}
```


## dlclose()
    int dlclose(void* handle);
`dlclose`关闭DL库。The `dl` library maintains link counts for dynamic file handles, so a dynamic
library is not actually deallocated until `dlclose` has been called on it as many times as `dlopen` has succeeded on it. Thus, it's not a problem for the same program to load the same library
multiple times.


