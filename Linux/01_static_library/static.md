# Static Library


## 介绍
简单来说，静态库就是一组目标文件的集合，也就是很多目标文件经过压缩打包后形成的一个文件。
之所以称为静态库，是因为在链接阶段，会将汇编生成的目标文件与引用到的库一起链接打包到可执行文件中。因此这种链接方式称为静态链接。


## 创建静态库
```bash
gcc -O -c add.c sub.c
ar -rcs libxmath.a add.o sub.o
```


## 使用静态库
```bash
# 直接使用静态库的全名
gcc -o ztest ztest.c libzmath.a
# 使用-l选项，指定-static
gcc -o ztest ztest.c -static -lzmath -L.
```

使用gcc链接程序的时候需要注意参数的顺序；-l选项是链接选项，因此需要放在需要编译的文件名之后。如下所示，将无法链接：
```bash
gcc -o ztest -static -lzmath -L. ztest.c
```
