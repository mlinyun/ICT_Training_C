# Makefile 基础 —— 扩展通配符与文件路径

## 函数 wildcard 的使用

前面章节介绍了文件通配符的使用，在规则中通配符会被自动展开，但在变量定义和函数引用时，通配符则会失效，那么在这种情况下就需要使用 `wildcard` 函数代替通配符。

`wildcard` 函数的使用格式为：

```makefile
$(wildcard PATTERN...)
```

在 makefile 中，它将被展开为已经存在的使用空格分开的匹配此模式的所有文件列表。

接下来对 `wildcard` 函数进行验证，通过 `cd` 命令在 Terminal 中打开到对应的文件夹。

```bash
cd ./make_example-master/chapter05/wild_code
```

我们可以看到在 `foo1.c` 与 `foo2.c` 文件中分别定义了 `foo1()` 和 `foo2()` 函数，而在文件 `main.c` 文件中通过引入头文件 `foo1.h` 与 `foo2.h` 对这两个函数进行了调用

`main.c` 文件的内容如下：

```C
#include <stdio.h>
#include "foo1.h"
#include "foo2.h"

int main(void)
{
    foo1();
    foo2();
    return 0;
}
```

现在我们查看当前目录下 makefile 文件的主要内容。

```makefile
# this is a makefile for wildcard code test

.PHONY: all clean

code=$(wildcard *.c)
aim=wildtest

all: $(code)
    @echo "objs inlude : " $(code)
    $(CC) -o $(aim) $(code)

clean:
    $(RM) $(aim)
```

从内容上我们可以看到它的最终目标 `all` 依赖于当前目录下所有的 `.c` 文件。重建目标 `all` 时会打印依赖文件并使用 `cc` 将其链接为 `wildtest` 文件。

执行 `make` 命令并观察输出结果。

```bash
make
```

终端的输出结果如下：

```plaintext
objs inlude :  foo1.c main.c foo2.c
cc -o wildtest foo1.c main.c foo2.c
```

执行刚才生成的可执行文件 `wildtest`

```bash
./wildtest
```

终端的输出结果如下：

```plaintext
Hello foo1!
Hello foo2!
```

从输出上可以看到 `wildtest` 的输出符合预期效果

在实际的项目管理中，我们通常用 `.o` 文件作为依赖，而非 `.c` 文件，此时需要用到函数的嵌套调用。我们可以使用 `$(patsubst SRC_PATTERN,DEST_PATTERN,FULL_STR)` 来进行字符串替换，将 `.c` 文件替换为 `.o`文件，代码内容如下：

```makefile
objs=$(patsubst %.c,%.o,$(wildcard *.c))
```

> `$(patsubst pattern,replacement,text)`: 查找 `text` 中以空格分隔的单词，并用 `replacement` 去替代 `pattern` 部分。详细参考 [Functions for String Substitution and Analysis](https://www.gnu.org/software/make/manual/html_node/Text-Functions.html)

通过上面的代码就可以将当前目录下的 `.c` 文件列表转换为 `.o` 文件列表，再利用 `make` 的隐含规则自动编译。提供的 代码文件 `pat_make.mk` 对上述理论进行了验证，`pat_make.mk` 的内容如下：

```makefile
# this is a makefile for wildcard code test

.PHONY: all clean

objs=$(patsubst %.c,%.o,$(wildcard *.c))
aim=wildtest2

all: $(objs)
    @echo "objs inlude : " $(objs)
    $(CC) -o $(aim) $(objs)

clean:
    $(RM) $(objs)
    $(RM) $(aim)
```

执行 `make` 命令并观察输出结果。

```bash
make -f pat_make.mk
```

终端的输出结果如下：

```plaintext
cc    -c -o foo1.o foo1.c
cc    -c -o main.o main.c
cc    -c -o foo2.o foo2.c
objs inlude :  foo1.o main.o foo2.o
cc -o wildtest2 foo1.o main.o foo2.o
```

可见 `foo1.c`，`main.c`，`foo2.c` 都已经被替换为对应的 `.o` 文件

### VPATH 变量和 vpath 关键字的使用

#### VPATH 的使用

`VPATH` 变量可以指定文件的搜索路径，若规则的依赖文件或目标文件在当前目录不存在时，`make` 会在此变量指定的目录下去寻找依赖文件。`VPATH` 可以定义多个目录，目录间用「:」隔开，目录搜索顺序与 `VPATH` 中定义的顺序一致。

输入下面的命令通过 `cd` 命令进入到 `vpath_code` 目录中。

```bash
cd ./make_example-master/chapter05/vpath_code
```

查看当前目录下的 `main.c` 文件，内容如下：

```C
#include <stdio.h>

extern void foo1(void);
extern void foo2(void);

int main(void)
{
        foo1();
        foo2();
        return 0;
}
```

与上一节实验中的 `main.c` 文件内容不同的地方是，上一节实验中 `main.c` 文件内容中是通过导入头文件 `foo1.h` 与 `foo2.h` 来对 `foo1()` 和 `foo2()` 函数的调用。而本小节则是通过 `extern` 关键字对函数进行声明并调用。这使得 `main.c` 本身不需要关注这两个函数的头文件放在什么位置，只要链接时的 `.o` 文件能够包含它们的实现即可

`foo1()` 和 `foo2()` 的函数实现位于 `chapter05/wild_code/` 目录下，我们可以通过 `VPATH` 变量告知 makefile 它们的路径。 makefile 文件内容如下：

```makefile
# this is a makefile for VPATH test

.PHONY: all clean

depen=main.o foo1.o foo2.o
aim=main

all: $(depen)
    @echo "objs inlude : " $(depen)
    $(CC) -o $(aim) $(depen)

clean:
    $(RM) $(depen)
    $(RM) $(aim)
```

在 `makefile` 中它只是单纯指定了三个依赖项分别为 `main.o`，`foo1.o` 和 `foo2.o`，并在重建 `all` 目标时将三者链接为 `main` 文件。

现在执行 `make` 命令, Terminal 的输出结果如下：

```plaintext
cc    -c -o main.o main.c
make: *** No rule to make target 'foo1.o', needed by 'all'。 停止。
```

发现 `make` 没有找到目标文件 `foo1.o`，并且当前路径下也没有 `foo1.c` 文件，无法依靠隐含规则自动重建 `foo1.o`，因此 `make` 报错并退出执行

现在我们执行下面的命令，设定 `VPATH` 为 `../wild_code/` 并传给 `make`：

```bash
make VPATH=../wild_code/
```

终端的输出结果如下：

```plaintext
objs inlude :  main.o foo1.o foo2.o
cc -o main main.o foo1.o foo2.o
cc: error: foo1.o: 没有那个文件或目录
cc: error: foo2.o: 没有那个文件或目录
makefile:9: recipe for target 'all' failed
make: *** [all] Error 1
```

发现输出错误，原因是我们在进行完了上一小节实验后，没有对产生的 `.o` 文件进行清理

执行下面的命令，重新观察输出结果。

```bash
rm ../wild_code/*.o
make VPATH=../wild_code
```

终端的输出结果如下：

```plaintext
cc    -c -o foo1.o ../wild_code/foo1.c
cc    -c -o foo2.o ../wild_code/foo2.c
objs inlude :  main.o foo1.o foo2.o
cc -o main main.o foo1.o foo2.o
```

说明 makefile 得到了正确的执行

### vpath 关键字的使用

`vpath` 关键字的作用与 `VPATH` 变量相似，可以指定依赖文件或目标文件的目录。 但 `vpath` 的用法更加灵活，下面是`vpath`的三种指令形式：

1. `vpath PATTERN DIR`：为匹配 `PATTERN` 模式的文件指定搜索目录。
2. `vpath PATTERN`：清除匹配 `PATTERN` 模式的文件设置的搜索目录。
3. `vpath`：清除全部搜索目录。

查看当前目录下的 `vpath.mk` 文件，与 `makefile` 文件的不同之处在与，在 `vpath.mk` 的开头多了一行下面的内容。

```makefile
vpath %.c ../wild_code/
```

现在执行下面的命令，并观察输出结果。

```bash
make clean
make -f vpath.mk
```

终端的输出结果如下：

```plaintext
cc    -c -o main.o main.c
cc    -c -o foo1.o ../wild_code/foo1.c
cc    -c -o foo2.o ../wild_code/foo2.c
objs inlude :  main.o foo1.o foo2.o
cc -o main main.o foo1.o foo2.o
```

可知 `vpath.mk` 的执行效果与使用 `VPATH` 一致

### 文件路径的保存及 GPATH 的使用

如前面实验所展示，有时候某些依赖文件或目标文件需要搜索 `VPATH` 或 `vpath` 指定目录才能得到。因此后续的流程中需要决定目录搜索得到的完整路径是要保留还是废弃。

`make` 在解析 makefile 文件时对文件路径的保存/废弃算法如下：

1. 在当前目录查找文件，若不存在则搜索指定路径。
2. 若目录搜索成功则将完整路径作为临时文件名保存。
3. 依赖文件直接使用完整路径名。
4. 目标文件若不需要重建则使用完整路径名，否则完整路径名被废弃。

其中比较难理解的是第四点，简单来说意思就是目标文件会在当前路径被进行重建。

下面进行规则验证，先清除掉上次实验的结果并切换目录：

```bash
make -f vpath.mk clean; cd ../gpath_code/
```

在当前目录下只有一份 makefile 文件，文件的主要内容如下：

```makefile
# this is a makefile for gpath test

.PHONY: all clean

vpath %.c ../wild_code/

depen=main.o foo1.o foo2.o
aim=main

all: $(depen)
    @echo "objs inlude : " $(depen)
    $(CC) -o $(aim) $^

clean:
    $(RM) $(depen)
    $(RM) $(aim)
```

相比之前的 makefile 此处同时指定了 `.c` 和 `.o` 文件的搜索路径。 此外，还在重建 `all` 目标时使用自动化变量 `$^` 代替 `$(depen)`，因为 `$^` 变量会将指定的目标文件展开为完整路径名

但此次所有的 `.c` 文件都在 `../wild_code/` 目录下，根据文件路径的保存规则，其对应的 `.o` 文件要在当前路径下生成。 执行 `make` 并观察当前文件夹中内容的变化

```bash
make
ls
```

终端的输出结果如下：

```plaintext
shiyanlou:gpath_code/ $ make                                            [12:23:25]
cc    -c -o main.o ../wild_code/main.c
cc    -c -o foo1.o ../wild_code/foo1.c
cc    -c -o foo2.o ../wild_code/foo2.c
objs inlude :  main.o foo1.o foo2.o
cc -o main main.o foo1.o foo2.o
shiyanlou:gpath_code/ $ ls                                              [12:24:16]
foo1.o  foo2.o  main  main.o  makefile
```

发现 `.o` 文件已经在当前文件夹中生成

如果不希望在当前目录下生成目标文件，可以使用 `GPATH` 变量。 若目标文件与 `GPATH` 变量指定目录相匹配，其完整路径名不会被废弃，此时目标文件会在搜寻到的目录中被重建

为了测试 `GPATH` 变量的效果，我们先清除掉上一次测试产生的文件，并切换到 `../wild_code/` 目录编译得到对应的 `.o` 文件：

```bash
make clean; ls; cd ../wild_code;
cc -c foo1.c; touch foo1.c
cc -c foo2.c; touch foo2.c
cc -c main.c; touch main.c
```

**注意**：`touch` 在这里用来修改 `foo1.c`、`foo2.c` 与 `main.c` 文件的时间戳。

现在 `wild_code` 目录下已经存在 `foo1.o`、`foo2.o`、`main.o` 文件了。 现在切回 `gpath_code` 目录并在执行 `make` 时使用 `GPATH` 变量

```bash
cd ../gpath_code; make GPATH=../wild_code; ls
```

终端的输出结果如下：

```plaintext
cc    -c -o main.o ../wild_code/main.c
cc    -c -o foo1.o ../wild_code/foo1.c
cc    -c -o foo2.o ../wild_code/foo2.c
objs inlude :  main.o foo1.o foo2.o
cc -o main main.o foo1.o foo2.o
```

从输出结果中可以看到 `.o` 文件还是在当前目录下生成，说明结果并不符合预期。但是观察 makefile 文件，发现下面这一行代码，并没有指定 `.o` 文件所在的路径

```makefile
vpath %.c ../wild_code/
```

将该行代码修改成下面的内容：

```makefile
vpath %.o ../wild_code/
```

清除掉上次的执行结果，再执行一次:

```bash
touch ../wild_code/main.c
touch ../wild_code/foo1.c
touch ../wild_code/foo2.c
make clean; ls; make GPATH=../wild_code/; ls
```

终端的输出结果如下：

```plaintext
shiyanlou:gpath_code/ $ touch ../wild_code/main.c                       [12:26:44]
touch ../wild_code/foo1.c
touch ../wild_code/foo2.c
make clean; ls; make GPATH=../wild_code/; ls
rm -f main.o foo1.o foo2.o
rm -f main
makefile
cc    -c -o ../wild_code/main.o ../wild_code/main.c
cc    -c -o ../wild_code/foo1.o ../wild_code/foo1.c
cc    -c -o ../wild_code/foo2.o ../wild_code/foo2.c
objs inlude :  main.o foo1.o foo2.o
cc -o main ../wild_code/main.o ../wild_code/foo1.o ../wild_code/foo2.o
main  makefile
```

可见这一次只有 `main` 文件在当前路径下生成，其余 `.o` 文件都在 `../wild_code/` 中被重建。

### -lNAME 文件的使用

makefile 中可以使用 `-lNAME` 来链接共享库和静态库。文件列表中的 `-lNMAE` 将被解析为名为 `libNAME.so` 或 `libNAME.a` 文件

`make` 搜索 `-lNAME` 的过程如下：

1. 在当前目录搜索名为 `libNAME.so` 的文件
2. 若不存在则搜索 `VPATH` 或 `vpath` 定义的路径
3. 若仍然不存在，`make` 将搜索系统默认目录，顺序为 `/lib`, `/usr/lib, /usr/local/lib`
4. 若依然无法找到文件，`make` 将按照以上顺序查找名为 `libNAME.a`的文件

**注意**：`-lNAME` 中的 `NAME` 是指动态库或者静态库去掉文件格式 `.o` 或 `.so` 和 名字开头的 `lib` 剩下的那部分，例如 `libfoo.so` 则 `NAME` 就是 `foo`，`-lNAME` 此时就应该是 `-lfoo`

接下来对 `-LNAME` 的搜索过程进行验证，验证的步骤如下：

1. 编写同名的动态库文件和静态库文件，使用相同的 api 内部打印不同信息
2. 编写 `main` 文件调用库文件 `api`
3. 编译库文件生成静态库和动态库
4. makefile 中使用 `-lNAME` 依赖项进行链接，验证使用的哪个库文件
5. 删除之前链接到的库文件再次执行 `make` 确认另一个库文件能否被成功链接

在 `chapter05/lib_code/` 文件夹中已经提供了用来进行验证的编写好的代码

`lib/` 下有两个 `.c` 文件 `foo_dynamic.c` 和 `foo_static.c`，定义了同一个函数 `foo()`，分别返回 1 和 2，这两份代码会被分别用于生成动态库和静态库文件。 主目录下的 `main.c` 调用 `foo()` 函数并打印得到的结果

makefile 中提供了生成库文件和链接 `main.o` 的方法，内容如下：

```makefile
# this is a makefile for -lNAME test

.PHONY: all clean static_lib dynamic_lib

VPATH=lib/

all: main.o -lfoo
    $(CC) -o main $^

static_lib: foo_static.o
    $(AR) rc libfoo.a $^;\
    mv libfoo.a lib/

dynamic_lib: foo_dynamic.o
    $(CC) $^ -fPIC -shared -o libfoo.so;\
    mv libfoo.so lib/

clean:
    $(RM) *.o *.a *.so main
    $(RM) lib/*.a lib/*.soso
```

动态库和静态库的链接，我们在 `chapter00` 已经测试过了，现在输入下面的命令先分别生成动态库和静态库文件。

```bash
cd ../lib_code
make static_lib; make dynamic_lib; ls lib/
```

终端的输出结果如下：

```plaintext
cc    -c -o foo_static.o lib/foo_static.c
ar rc libfoo.a foo_static.o;\
mv libfoo.a lib/
cc    -c -o foo_dynamic.o lib/foo_dynamic.c
cc foo_dynamic.o -fPIC -shared -o libfoo.so;\
mv libfoo.so lib/
foo_dynamic.c  foo_static.c  libfoo.a  libfoo.so
```

再执行 `make` 观察最终目标链接的是哪个库文件。

```bash
make; ./main
```

终端的输出结果如下：

```plaintext
shiyanlou:lib_code/ $ make                                                                                                                           [12:34:37]
cc    -c -o main.o main.c
cc -o main main.o lib/libfoo.so
shiyanlou:lib_code/ $ ./main                                                                                                                         [12:36:35]
get i=1
```

可见 `-lNAME` 优先被解析为动态库

现删除动态库再次编译执行

```bash
rm lib/libfoo.so; make; ./main
```

终端的输出结果如下：

```plaintext
cc -o main main.o lib/libfoo.a
get i=2
```

可见动态库文件不存在时，`make` 会尝试查找和链接静态库文件

`-lNAME` 的展开是由变量 `.LIBPATTERNS` 来指定的，其值默认为`lib%.so lib%.a`。 感兴趣的同学可以自己尝试打印和修改此变量
