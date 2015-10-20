# 链接程序

-o <file>
Place output in file <file>. This applies to whatever sort of output is being
produced, whether it be an executable file, an object file, an assembler file
or preprocessed C code.
If -o is not specified, the default is to put an executable file in `a.out`,
the object file for `source.suffix` in `source.o`, its assembler file in
`sources.s`, a precompiled header file in `source.suffix.gch`, and all 
preprocessed C source on standard output.

C源码编译成可执行程序包含如下四个阶段：

C语言编译的时候以.c文件为基本单元，每一个.c文件最后都生成一个.o文件，最后
所有的.o文件链接在一起，形成可执行文件。

1. 预处理 preprocess
2. 编译 compile
3. 汇编 assemble
4. 链接 link

其中使用了4个应用程序:
1. cpp  - The C Preprocessor
2. gcc
3. as  - the portable GNU assembler.
4. ld  - The GNU linker

hello.c -> hello.i -> hello.s -> hello.o -> hello

一般情况下，中间过程都可以省去，使用gcc命令可以直接从hello.c得到hello可执行文件。

# 预处理：完成宏定义的替换，去掉所有注释信息。
# -E: Preprocess only; do not compile, assemble or link
    gcc -o hello.i -E hello.c

# 编译：经过此法分析、语法分析和语义分析，将C代码转换成汇编指令。
# -S: Compile only; do not assemble or link
gcc -o hello.s -S hello.i

# 汇编：将汇编代码转化为机器可以执行的机器指令。
# -c: Compile and assemble, but do not link
gcc -o hello.o -c hello.s

# 链接：.o文件还不能够被计算机所执行，必须转换为可执行的二进制文件
# 才能被装载到内存中执行。而.o文件转换成二进制文件的过程就叫做链接。
# 使用readelf -h命令查看文件，可以得到文件类型
# readelf -h hello.o   =>    Type:  REL (Relocatable file)
# readelf -h hello     =>    Type:  EXEC (Executable file)
gcc -o hello hello.o

# 使用下面的命令可以查看文件信息
#objdump -h hello.o
#readelf -h hello.o
