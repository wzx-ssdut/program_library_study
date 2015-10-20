# Static Library


## 创建静态库
```
gcc -O -c add.c sub.c
ar -rcs libxmath.a add.o sub.o
```


## 使用静态库
```
# 直接使用静态库的全名
gcc -o ztest ztest.c libzmath.a
# 使用-l选项，指定-static
gcc -o ztest ztest.c -static -lzmath -L.
```

使用gcc链接程序的时候需要注意参数的顺序；-l选项是链接选项，因此需要放在需要编译的文件名之后。如下所示，将无法链接：
```
gcc -o ztest -static -lzmath -L. ztest.c
```

