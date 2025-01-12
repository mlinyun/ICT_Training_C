# Makefile —— 深入了解 Makefile

## Makefile 规则之自动推导

makefile 有一套隐含的自动推导规则，具体内容如下：

1. 对于 `xxx.o` 类型的目标会默认使用命令 `cc -c xxx.c -o xxx.o` 进行编译。
2. 对于`xxx`类型的目标会默认使用命令 `cc xxx.o -o xxx` 进行编译。

下面用两个小实验对 makefile 的自动推导规则进行验证。

编写 `main.c` 文件，`main.c` 文件的内容如下：

```C
#include <stdio.h>

int main(void)
{
    printf("Hello world!\n");
    return 0;
}
```

在确认当前目录中不包含 makefile 文件后，通过下面的命令验证自动推导规则的第一条

```bash
make main.o
```

从终端输出的结果说明 `make` 自动使用 `cc -c` 命令生成了 `main.o` 文件

类似的通过下来验证自动推导规则中的第二条

```bash
make main
```

从终端输出的结果说明 `make` 通过 `cc` 命令成功生成了 `main` 文件，不过我们通过终端的输出可以发现 `cc` 命令在生成 `main` 文件的过程中使用到了 `mian.o` 文件，而 `main.o` 文件在进行上一步实验的过程中已经产生了。现在我们尝试删除当前文件夹中的 `main` 和 `main.o` 文件后

```bash
rm main main.o
```

再在终端中输入命令 `make main`，从终端的输出结果，说明在当前文件夹中不存在 `main.o` 文件时，`make` 会将 `main.c` 文件直接编译成 `main` 文件

## Makefile 中的「include」关键字

### include 的概念

makefile 中可以使用 `include` 指令来包含另一个文件。 当 `make` 识别到 `include` 指令时，会暂停读入当前的 makefile 文件，并转而读入 `include` 指定的文件，之后再继续读取本文件的剩余内容。

### include 的使用

接下来的操作涉及到的文件都在 `./makefile_dir` 路径下包括：

- inc_a
- inc_b
- makefile

`inc_a` 的内容如下：

```makefile
# this is a include file for makefile

vari_c="vari_c from inc_a"
```

将 makefile 文件从 `makefile_dir` 文件夹拷贝至当前文件夹

```bash
cp ./makefile_dir/makefile ./
```

makefile 文件的内容如下：

```makefile
# this is a basic makefile

.PHONY:all clean

vari_a="original vari a"
vari_b="original vari b"

include ./makefile_dir/inc_a

all:
    @echo $(vari_a)
    @echo $(vari_b)
    @echo $(vari_c)

clean:
```

在终端中执行 `make` 命令并观察输出结果，从输出结果可以看出来 makefile 已经成功包含了 `inc_a` 文件，并且正确获取到了 `vari_c` 变量

值得一提的是 `include` 指示符所指示的文件名可以是任何 shell 能够识别的文件名，这表明 `include` 还可以支持包含通配符的文件名。我们将在下面的实验中进行验证

`./makefile_dir` 目录下有一份需要被包含的文件 `inc_b`，文件内容如下：

```makefile
# this is a include file for makefile

vari_d="vari_d from inc_b"
```

修改 makefile，使用通配符同时包含 `inc_a` 和 `inc_b` 文件。 修改后的 makefile 内容如下：

```makefile
# this is a basic makefile

.PHONY: all clean

vari_a="original vari a"
vari_b="original vari b"

include ./makefile_dir/inc_*

all:
    @echo $(vari_a)
    @echo $(vari_b)
    @echo $(vari_c)
    @echo $(vari_d)

clean:
```

> **注意**：makefile 中修改了两处，第一处是 `inc_a` 修改为了 `inc_*`，第二处是在 `all` 中新增了 `@echo $(vari_d)` 。因为在 `inc_b` 中我们定义了变量 `vari_d`，在 makefile 中我们需要对其值进行输出。

执行 `make` 命令，从终端的输出结果说明 `inc_a` 与 `inc_b` 都被包含进了 makefile 文件中

### include 的文件的查找路径

当 include 指示符包含的文件不包含绝对路径，且在当前路径下也无法寻找到时，make 会按以下优先级寻找文件：

1. `-I` 指定的目录
2. `/usr/gnu/include`
3. `/usr/local/include`
4. `/usr/include`
5. 指定 makefile 的 include 路径

修改 `makefile`，不再指定 `inc_a` 和 `inc_b` 的相对路径，此时 makefile 文件的内容是：

```makefile
# this is a basic makefile

.PHONY: all clean

vari_a="original vari a"
vari_b="original vari b"

include inc_*

all:
    @echo $(vari_a)
    @echo $(vari_b)
    @echo $(vari_c)
    @echo $(vari_d)
clean:
```

执行 `make` 命令，观察输出结果，发现有错误产生

```plaintext
makefile:8: inc_*: 没有那个文件或目录
make: *** No rule to make target 'inc_*'。 停止。
```

可以看到 makefile 无法找到 `inc_a` 和 `inc_b` 文件

接下来使用 `make -I` 命令来指定搜寻路径。

```bash
make -I ./makefile_dir/
```

同样的终端还是出现了和上面一样的错误，因为从输出结果可以看出 `make` 是在查找名为 `inc_*` 的文件。现在我们修改 makefile 文件中的 `include` 行。

```makefile
include inc_a inc_b
```

再次执行下面的命令：

```bash
make -I ./makefile_dir/
```

从终端的输出结果说明程序得到了正确的执行。所以我们可以知道 `make` 在通过 `-I` 来指定想要包含的文件的路径时，在 makefile 中不能使用通配符来表是具体的要引用的文件

### include 的处理细节

前面提到 `make` 读入 makefile 时遇见 `include` 指示符会暂停读入当前文件，转而读入 `include` 指定的文件，之后才继续读入当前文件。

拷贝文件 `makefile_dir/makefile_b` 到当前目录并命名为 makefile：

```bash
cp makefile_dir/makefile_b ./makefile
```

此时 makefile 文件的内容如下：

```makefile
# this makefile is test for include process

.PHONY: all clean

vari_a="vari_a @ 1st"

include ./makefile_dir/c_inc

vari_a += " @2nd ..."

all:
    @echo $(vari_a)

clean:
```

从 makefile 内容上可以看出 makefile 规则的执行过程是先定义变量 `vari_a`，然后再引入文件 `c_inc`，最后修改变量 `vari_a`。

`c_inc` 文件的内容如下：

```makefile
# this is a include file for include process

vari_a="vari_a from c_inc"
```

从中可以看出在 `c_inc` 文件中也对 `vari_a` 变量进行了定义。

执行 `make` 命令并观察输出结果，这说明 `vari_a` 在 `include` 过程中被修改了，并且在其后添加了字符串 `@2nd ...`，结果与预期中 `make` 处理 `include` 指示符的行为一致

## Makefile 中环境变量的使用

`MAKEFILES` 环境变量有定义时，它的作用类似于 `include`。 该变量在被展开时以空格作为文件名的分隔符。

删除当前目录下的 makefile 文件，然后创建一个新的 makefile 文件，内容如下：

```makefile
# this makefile is test for include process

.PHONY: all clean

vari_a += "2nd vari..."

all:
    @echo $(vari_a)

clean:
```

执行 `make` 命令，查看输出结果，可以看到终端只输出了 `2nd vari...`

现在增加环境变量 `MAKEFILES`：

```bash
export MAKEFILES=./makefile_dir/c_inc
```

再次执行 `make` 命令，此时终端输出了 `vari_a from c_inc 2nd vari...`，可以看出 `c_inc` 中的变量被引用到了 makefile 文件中

接下来开始探究 `MAKEFILES` 的使用限制

在当前文件夹下创建一个 `aim_b_file` 文件，内容如下：

```makefile
# this is aim_b file

.PHONY: aim_b

aim_b:
    @echo "now we exe aim_b"
```

将 `aim_b_file` 加入到 `MAKEFILES` 环境变量中。

```bash
export MAKEFILES=./aim_b_file
```

执行 `make` 命令，此时终端输出了 `2nd vari...`，可见 `make` 虽然先包含 `aim_b_file` 文件，但依然以 makefile 中的 `all` 作为最终目标。 我们再来验证 `aim_b` 规则是否已经被正常解析到，修改 makefile 文件，为 all 增加一条依赖。

```makefile
all: aim_b
```

执行 `make` 命令，此时终端输出的内容如下：

```plaintext
now we exe aim_b
2nd vari...
```

这说明 `aim_b` 已经被 `make` 成功的解析到了

接着执行 `make aim_b` 命令，此时终端输出了 `now we exe aim_b`，由此我们可以知道通过这两种方式 `make` 都能够使 `aim_b` 得到执行，但 `aim_b` 却不能作为最终目标而被执行，只有明确地指定此规则时才会执行其对应的命令

所有 `MAKEFILES` 指定的文件名、命令行指定的文件名、默认 makefile 文件以及 `include` 指定的文件名都会被记录下来。而当前路径下总共有 `./aim_b_file`，`./makefile`，`./makefile_dir/inc_a`，`./makefile_dir/inc_b`，`./makefile_dir/c_inc` 这 5 个文件。

现在我们使用不同的方式将它们包含进来。 我们将`./aim_b_file`和`./makefile_dir/c_inc`包含在`MAKEFILES`变量中：

```bash
export MAKEFILES="./makefile_dir/c_inc ./aim_b_file"
```

而`./makefile` 会在执行 `make` 时被自动调用，接着修改 makefile 用 `include` 指示符包含文件 `./makefile_dir/inc_a` 和 `./makefile_dir/inc_b`。 并在 `all` 目标中打印 `MAKEFILE_LIST` 变量，修改后的 makefile 内容如下：

```makefile
# this makefile is test for include process

.PHONY: all clean

include ./makefile_dir/inc_a ./makefile_dir/inc_b

vari_a += "2nd vari..."

all: aim_b
 @echo $(vari_a)
 @echo $(MAKEFILE_LIST)
clean:
```

执行 `make` 命令，此时终端的输出如下：

```plaintext
now we exe aim_b
vari_a from c_inc 2nd vari...
./makefile_dir/c_inc ./aim_b_file makefile makefile_dir/inc_a makefile_dir/inc_b
```

通过第三行的输出内容我们可以看出 `MAKEFILE_LIST` 中包含的文件有 `./makefile_dir/c_inc`，`./aim_b_file`，`./makefile`，`./makefile_dir/inc_a`和`./makefile_dir/inc_b`。

## 重载另一个 Makefile

通过 `cp` 命令拷贝并重命名当前目录下的 makefile 文件

```bash
cp makefile inc_test
```

再通过命令 `make -f` 指定要读取的 makefile 文件。

```bash
make -f inc_test
```

从终端的输出结果中可以看出原来的 makefile 文件变成了 `inc_test` 文件，说明 `inc_test` 文件已经被 `MAKEFILE_LIST` 记录下来了

makefile 重载另一个 makefile 的时，不允许有规则名重名。 若是有规则发生重名会发生什么状况呢？ 修改 `aim_b_file` 增加 `all` 规则：

```makefile
all:
    @echo "all in aim_b"
```

执行 `make` 命令，终端的输出结果如下:

```plaintext
makefile:10: warning: overriding recipe for target 'all'
T):9: warning: ignoring old recipe for target 'all'
now we exe aim_b
vari_a from c_inc 2nd vari...
./makefile_dir/c_inc ./aim_b_file makefile makefile_dir/inc_a makefile_dir/inc_b
```

从打印日志中可以看出 `makefile` 重写了 `aim_b_file` 文件中的 `all` 规则

从上面的实验中可以看出，对于两个文件中同名的规则，`make` 后读入的规则会重写先读入的规则。 现在假如有两个 makefile 文件，AMake 和 BMake，它们都定义了一条 `intro` 规则，但行为不同。 用户希望执行在生成目标 `AAim` 和 `BAim` 的时候分别调用 AMake 和 BMake 的 `intro` 规则，要怎样来做呢？

我们无法用 `include` 指示符来包含这两个 makefile，否则会产生重写规则的行为。 此时需要用到重载另一个 makefile 的技巧。 具体方法就是在对应的规则中重新调用 `make` 并传入需要重载的 makefile 文件名及目标名。

接下来我们将使用到在目录 `./make_example-master/chapter02/makefile_dir` 下的 `makefile_c`、`AMake` 和 `BMake` 文件，我们先将其拷贝至当前目录

```bash
cp makefile_dir/makefile_c makefile
cp makefile_dir/AMake ./
cp makefile_dir/BMake ./
```

查看 makefile 文件，内容如下：

```makefile
# this is a makefile reload example main part

.PHONY: AAim BAim

AAim:
 make -f AMake intro

BAim:
 make -f BMake intro
```

当目标为 `AAim` 时，会执行 `make -f AMake intro`。 也就是会重载 `AMake` 作为 makefile 文件并执行 `intro` 规则。 `BAim` 的处理方式也类似。 现在查看一下执行效果，执行命令：

```bash
make AAim
```

从终端的输出结果中可以看出 `AAim` 中的 `intro` 规则得到了正确的执行

现在输入下面的命令查看结果

```bash
make BAim
```

从终端的输出结果可以看出 `BAim` 中的 `intro` 规则也得到了正确的执行

通过上面的实验我们已经掌握了基本的重载方式，接下来我们再增加一个要求，希望在执行其它未定义的规则时默认执行另一条 `intro` 规则，而该规则是在 CMake 文件中被定义的。为了匹配到所有的未定义规则，我们需要用到通配符「%」。

修改 makefile，在文件最后加入「所有匹配模式」规则：

```makefile
%:
    make -f CMake intro
```

接下来将 `makefile_dir/CMake` 文件拷贝到当前目录下：

```bash
cp makefile_dir/CMake ./
```

随意的执行一条未定义的规则 `AAA` 并观察输出结果，说明这条未定义的规则最后会重载 CMake 并执行其 `intro` 规则
