# Shared Library

## 创建共享库
First, create the object files that will go into the shared library using the gcc `-fPIC` or `-fpic` flag.
1. 生成目标文件
    gcc -fPIC -c add.c -o add.o
    gcc -fPIC -c sub.c -o sub.o

选项`-fPIC`和`-fpic`将生成`Position Independent Code`，即位置无关代码，共享库必须指定这个选项。
使用`-fPIC`还是`-fpic`来生成代码取决于目标。`-fPIC`总是可行的，但是可能会生成更大的代码。
使用`-fpic`选项通常生成更小和更快的代码，但是会有一些平台相关的限制，比如全局可见符号或代码的大小。
在你创建共享库的时候，连接器会告诉你它是否合适。
拿不准的时候，就使用`-fPIC`，肯定可以工作。

2. 生成共享库。
    gcc -shared -Wl,-soname,libzmath.so.1 -o libzmath.so.1.0.0 add.o sub.o

`-shared`选项表示生成的库为共享库，`-Wl,<options>`用于传递逗号分割的选项给连接器。
此处指定生成的`libzmath.so.1.0.0`的soname为`libzmath.so.1`。

gcc有一组这样的选项，分别用于给汇编器，预处理器和连接器传递选项和参数。
```
-Wa,<options>            Pass comma-separated <options> on to the assembler
-Wp,<options>            Pass comma-separated <options> on to the preprocessor
-Wl,<options>            Pass comma-separated <options> on to the linker
-Xassembler <arg>        Pass <arg> on to the assembler
-Xpreprocessor <arg>     Pass <arg> on to the preprocessor
-Xlinker <arg>           Pass <arg> on to the linker
```

## 使用共享库
最简单的方式，就是把库复制到其中一个标准目录（如：`/usr/lib`）中，然后运行`ldconfig`。
首先，你需要创建共享库。然后，你需要设定好必须的符号链接，特别是*soname*到*real name*的链接。
