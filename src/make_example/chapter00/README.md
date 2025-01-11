# Makefile 基础 —— 编译连接与执行

## 主程序的编译、链接与执行

打开 chapter00 文件夹查看 main.c 文件，内容如下：

```c
#include <stdio.h>

int main(void)
{
    printf("Hello Cacu!\n");
    return 0;
}
```

在 chapter0 目录下打开终端执行下面的命令，对 `main.c` 文件只编译而不链接

```bash
gcc -c main.c
```

可以发现在当前目录中生成了一个新的文件 `main.o`

通过 file 命令查看 main.o 的文件格式：

```bash
file main.o
```

通过终端输出的结果说明 `main.o` 实际上是一个 relocatable object 文件

通过以下命令为 `main.o` 文件赋予可执行的权限：

```bash
chmod 777 main.o
```

输入以下命令尝试执行 main.o 文件：

```bash
./main.o
```

终端输出可执行文件格式错误，说明 relocatable object 文件是不可执行的

接下来通过 GCC 对 `main.o` 文件进行链接操作，从而生成一个可执行的程序 `main`

在终端中输入以下命令将 `main.o` 链接为 `main` 文件：

```bash
gcc -o main main.o
```

可以发现当前目录新增了一个名为 main 的文件

通过 file 命令查看 main 的文件格式：

```bash
file main
```

从终端中输出的结果说明 `main` 文件是一个可执行的文件，于是通过以下命令来执行 `main` 文件：

```bash
./main
```

可以看到程序得到了正确的执行

## 静态链接

执行以下命令给 main.c 打上 v1.0.patch 补丁：

```bash
patch -p2 < v1.0.patch
```

此时 `main.c` 文件内容如下：

```c
#include <stdio.h>
#include "add_minus.h"

int main(void)
{
    int rst;

    printf("Hello Cacu!\n");

    rst = add(3,2);
    printf("3 + 2 = %d\n",rst);

    rst = minus(3,2);
    printf("3 - 2 = %d\n",rst);

    return 0;
}
```

通过以下命令对 main.c 文件进行编译和链接：

```bash
# 编译
gcc -c main.c
gcc -c add_minus.c
# 链接
gcc -o main main.o add_minus.o
```

注意：在链接的时候，需要将 `main.o` 和 `add_minus.o` 链接成可执行文件

执行新生成的可执行文件 `main`

```bash
./main
```

这样程序就能够正常执行了

重新编译 `add_minus.c` 生成 `add_minus.o` 文件

```bash
gcc -c add_minus.c
```

通过 `ar` 命令将 `add_minus.o` 打包到静态库中

```bash
ar rc libadd_minus.a add_minus.o
```

执行上面的命令后，可以发现在当前目录下，生成了一个名为 `libadd_minus.a` 的静态库文件

用 `file` 命令查看 `libadd_minus.a` 的文件格式

```bash
file libadd_minus.a
```

实际上 `libxxx.a` 格式的文件可以简单的看成指定的以 `.o` 结尾的文件集合

链接 `main.o` 和静态库文件

```bash
gcc -o main2 main.o -L./ -ladd_minus 
```

> `-L./`: 表明库文件位置在当前文件夹
> `-ladd_minus`: 表示链接 `libadd_minus.a` 文件，使用 `-l` 参数时,前缀 `lib` 和后缀 `.a` 是需要省略的

执行 `main2`:

```bash
./main2
```

这样操作程序也能够正确的执行

## 动态链接

通过以下命令将 `multi_div.c` 文件编译成动态链接库

```bash
gcc multi_div.c -fPIC -shared -o libmulti_div.so
```

> `-fPIC`: 选项作用于编译阶段，在生成目标文件时就得使用该选项，以生成位置无关的代码

命令执行结束后，在当前目录下会生成一个名为 `libmulti_div.so` 的文件

通过 `file` 命令来查看 `libmulti_div.so` 的文件格式

```bash
file libmulti_div.so
```

从终端中输出的结果可知 `libmulti_div.so` 是一个 shared object 文件

删除之前的 main.c 文件，并编写新的 main.c 文件，内容如下：

```c
#include <stdio.h>

int main(void)
{
    printf("Hello Cacu!\n");
    return 0;
}
```

通过以下命令为 `main.c` 打上 `v2.0.patch` 补丁：

```bash
patch -p2 < v2.0.patch
```

编译 `main.c` 生成 `main.o`：

```bash
gcc -c main.c
```

链接 `main.o` 与动态链接库文件

```bash
gcc -o main3 main.o -L./ -lmulti_div
```

执行生成的 `main3` 文件。

```bash
./main3
```

你会发现输出结果出现错误，出现错误的原因是我们生成的动态库 `libmulti_div.so` 并不在库文件搜索路径中

**解决办法**：

1. 将 `libmulti_div.so` 拷贝到 `/lib/` 或 `/usr/lib/` 文件夹下。

    ```bash
    sudo cp libmulti_div.so /usr/lib
    ```

2. 在 `LD_LIBRARY_PATH` 变量中指定库文件路径，而动态链接库文件存放在 `/home/project/make_example-master/chapter0/` 路径下。所以需要在 Terminal 中执行下面的命令：

     ```bash
     export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/project/make_example-master/chapter0/
     ```

现在在 Terminal 中执行下面的命令：

```bash
./main3
```

通过上面的操作，程序就可以正确的执行了

## 混合使用静态链接与动态链接

删除旧的 `main.c` 文件，并编写新的 `main.c` 文件，内容如下：

```C
#include <stdio.h>

int main(void)
{
    printf("Hello Cacu!\n");
    return 0;
}
```

为新的 `main.c` 文件打上 `v3.0.patch` 补丁

```bash
patch -p2 < v3.0.patch
```

编译 `main.c` 生成 `main.o`。

```bash
gcc -c main.c
```

测试执行混用静态链接和动态链接的方式

```bash
gcc -o main4 main.o -L./ -ladd_minus -lmulti_div
```

由于我们之前已经修改过 `LD_LIBRARY_PATH` 变量，所以此次无需再次修改

执行下面的命令：

```bash
./main4
```

可以看到程序得到正确的执行

> 尽管我们知道无论是静态链接还是动态链接都能达到链接对象文件生成可执行文件的目的，但是我们还是得注意静态链接库与动态链接库之间的区别，详细内容参考 [Static, Shared Dynamic and Loadable Linux Libraries](http://www.yolinux.com/TUTORIALS/LibraryArchives-StaticAndDynamic.html)
