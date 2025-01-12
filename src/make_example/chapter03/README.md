# Makefile —— make 的执行过程与条件判断

## make 的两个执行阶段

编写 makefile 文件内容如下：

```makefile
# this is a makefile example

vari_a = "vari a from makefile"
vari_b = "vari b from makefile"

.PHONY: all

all:
    @echo $(vari_a)
    @echo $(vari_b)
```

在 makefile 文件中我们定义了两个变量 `vari_a` 与 `vari_b`，同时我们在执行规则 `all` 时将他们的值打印输出，现在执行 `make` 命令，输出结果如下：

```plaintext
vari a from makefile
vari b from makefile
```

新增一个文件 `inc_a`，在文件中声明一个变量 `vari_b` 值为 「vari b from inc_a」，内容如下：

```makefile
# this is a include file for make

vari_b = "vari b from inc_a"
```

修改 makefile 文件，在文件的**最后一行**通过 `include` 将 `inc_a` 包含到 makefile 中

```makefile
include inc_a
```

执行 `make` 命令，输出结果如下：

```plaintext
vari a from makefile
vari b from inc_a
```

可以发 `vari_b` 的值被修改了

我们知道 `make` 是按照顺序一行行读入 makefile。 前面介绍 `make` 的第一阶段是读入所有 makefile 文件，`include`导入的文件以及环境变量指定的文件。所以解析新修改的 makefile 时，`inc_a` 应该在第一阶段被解析完毕，所以 `vari_b` 变量就被 `inc_a` 修改掉了。**由此说明文件的处理顺序与 `include` 指示符在 makefile 中的位置无关**

## make 目标指令的执行细节

到目前为止，我们已经知道 makefile 中的指令都是 shell 指令，那么 `make` 是怎样执行目标对应指令呢？ 答案还是 shell。`make` 会调用 shell 去执行每一条指令。需要注意的是，即便在同一个目标下，每一条指令都是相互独立的。 也就是说 `make` 会分别调用 shell 去执行每一条指令，而非使用一个 shell 进程按顺序执行所有的命令。

使用 `cd` 命令和 `pwd` 命令查看两条相邻的命令能否相互产生影响，由此来验证说法的正确性。 创建 `cd_test.mk` 文件，写入如下的内容：

```makefile
# this is a makefile to test cd and pwd cmd

.PHONY: all

all:
    @pwd
    cd ..
    @pwd
```

从内容中我们可以知道 `all` 规则是由三条命令构成的，其中 `@pwd` 表示打印当前绝对路径，但不要显示 `pwd` 命令，`cd ..` 表示回到上一层目录。 因此，若三条指令是在一个 shell 进程中顺序执行，那么命令的执行顺序是先打印当前目录的绝对路径，再返回上一层目录并打印上一层目录的绝对路径。若是三条指令是在三个不同的 shell 中执行的，则两次 `@pwd` 命令的执行结果将会是相同的

现在执行下面的命令并观察输出结果

```bash
make -f cd_test.mk
```

从终端的输出结果知道两次 `@pwd` 命令的执行结果将会是相同的，这说明三条命令是在三个不同的 shell 中执行的

现在我们用另外一种方法来进行证明，打印执行当前命令的进程 id，通过观察进程 id 是否相同来判断不同行的命令是否是在同一个 shell 中执行的。创建 `cmd_test.mk`， 写入如下的内容：

```makefile
# this is a command test makefile

.PHONY: all

all:
    @echo "cmd1 process id is :" $$$$
    @echo "cmd2 process id is :" $$$$
```

可以看出 `all` 规则下的两条命令的作用都是对当前的进程号进行输出，其中 `$$$$` 表示当前的进程 id

执行下面的命令，观察输出结果。

```bash
make -f cmd_test.mk
```

从终端的输出结果可以看出两条命令输出的进程 id 是不同的，由此我们可以知道，目标下的每一条命令都是通过不同的 shell 执行的

有些状况下，用户希望能够使用 `cd` 命令来控制命令执行时所在的路径，比如 `cd` 到某个目录下，编译其中的源代码，要实现该操作就必须在一行中写入多条指令。

首先修改 `cd_test.mk` 文件，将三条指令都放在一行，并用「;」隔开。 请注意第三条 `@pwd` 的指令中，「@」符号要删掉，因为该符号只用于每一行的开头。修改后的 `cd_test.mk` 内容如下：

```makefile
# this is a makefile to test cd and pwd cmd

.PHONY: all

all:
    @pwd; cd .. ; pwd
```

执行以下命令:

```bash
make -f cd_test.mk
```

从终端的输出结果说明这三条命令是在同一个进程中被执行的

在同一行中书写多条指令是一件比较麻烦的事情，尤其是指令较长时，非常不方便阅读和修改。 makefile 中可以使用反斜线**「\」**来将一行的内容分割成多行

提供的源文件中有一个 `multi_test.mk` 文件，用于测试反斜线的作用，内容如下：

```makefile
# this is a command test makefile

.PHONY: all

all:
    @echo "cmd1 process \
    id is :" $$$$; \
    echo "cmd2 process id is :" $$$$
```

此文件将一条指令分割成 3 行，其中第 1 行和第 2 行组成一条完整的指令，内容与第 3 行指令相似。两条指令的作用也是打印当前执行进程的 id 号。 使用 `make -f multi_test.mk` 命令执行此文件。

从终端的输出结果可以看出执行效果与修改后的 `cmd_test.mk` 文件执行效果一致，说明反斜杠的确能起到连接多行指令的作用

## makefile 中的条件判断语句

### 条件判断语句的基本格式

makefile 中没有 `else` 分支的条件判断语句的格式如下：

```makefile
CONDITIONAL-DIRECTIVE
TEXT-IF-TRUE
endif
```

其中 `TEXT-IF-TRUE` 可以为若干任何文本行，当条件为真时它被 `make` 作为需要执行的一部分。

makefile 中有 `else` 分支的条件判断语句格式如下：

```makefile
CONDITIONAL-DIRECTIVE
TEXT-IF-TRUE
else
TEXT-IF-FALSE
endif
```

其中 `make` 在条件为真时执行 `TEXT-IF-TRUE`，否则执行`TEXT-IF-FALSE`。

### 条件判断语句中的关键字

| 关键字 | 描述               |
| ------ | ------------------ |
| ifeq   | 判断参数是否相等   |
| ifneq  | 判断参数是否不相等 |
| ifdef  | 判断变量是否有值   |
| ifndef | 判断变量是否无值   |

`ifeq` 可以支持以下几种格式：

```makefile
ifeq (ARG1, ARG2)
ifeq 'ARG1' 'ARG2'
ifeq "ARG1" "ARG2"
ifeq "ARG1" 'ARG2'
ifeq 'ARG1' "ARG2"
```

**注意**：`ifeq/ifneq` 等关键字后面一定要接一个**空格**，否则 `make` 会因为无法识别关键字而报错！

提供的代码文件中已有 `eq.mk` 文件，内容如下：

```makefile
# this is a makefile to test ifeq

.PHONY: all

b="ifeq default"

ifeq ($(a),1)
b="ifeq a 1"
endif

ifeq '$(a)' '2'
b="ifeq a 2"
endif

ifeq "$(a)" "3"
b="ifeq a 3"
endif

ifeq "$(a)" '4'
b="ifeq a 4"
endif

ifeq '$(a)' "5"
b="ifeq a 5"
endif

all:
        @echo $(b)
```

依次执行下面的命令：

```bash
make -f eq.mk
make -f eq.mk a=1
make -f eq.mk a="1"
make -f eq.mk a=2
make -f eq.mk a=3
make -f eq.mk a=4
make -f eq.mk a=5
make -f eq.mk a=6
```

观察终端的输出结果，`ifneq` 支持的格式与 `ifeq` 相同

同样提供的代码文件中已有 `neq.mk` 文件，内容如下：

```makefile
# this is a mekfile to test ifneq

.PHONY: all

ifneq ($(a),)
b=$(a)
else
b="null"
endif

all:
    @echo "value b is:" $(b)
```

`neq.mk` 中的条件判断语句使用了 `ifneq ... else ... endif` 结构。 当 `a` 不为空时，`b` 的值与 `a` 相同，否则 `b` 为默认值 `null`。

依次执行下面的 `make` 命令，打印输出 `b` 在各种情况下的值：

```bash
make -f neq.mk
make -f neq.mk a=1
make -f neq.mk a=2
make -f neq.mk a="hello"
```

`ifdef` 语句的语法格式如下：

```makefile
ifdef VARIABLE-NAME
```

它只会判断变量是否有值，而不关心其值是否为空。

现在我们测试 `ifdef` 的用法，以及要怎样理解变量值为空和变量未定义的差别。 提供的源代码文件中已有测试需要的代码文件`def.mk`，内容如下：

```makefile
# this is a makefile to test ifdef

.PHONY: all

a=
b=$(a)

ifdef a
c="a is defined"
else
c="a is not defined"
endif

ifdef b
d="b is defined"
else
d="b is not defined"
endif

all:
    @echo "vari a is:" $(a)
    @echo "vari b is:" $(b)
    @echo "vari c is:" $(c)
    @echo "vari d is:" $(d)
```

`def.mk` 文件中先声明了一个变量 `a`，但并未给其赋值，即变量 `a` 未定义。 变量 `a` 又被赋给了变量 `b`，由于 `a` 是未定义变量，因此 `b` 为空值。 `make` 执行此文件时分别打印变量 `a`、`b`、`c`、`d` 的值。

现在执行下面的 `make` 命令，观察输出结果。

```bash
make -f def.mk
```

从终端的输出结果可见对 `make` 来说，它认为 `a` 属于未定义变量，`b` 则属于已定义变量

`ifneq` 格式与 `ifeq` 相同，逻辑上与 `ifneq` 相反。 提供的源代码中包含了测试需要用到的代码文件 `ndef.mk` 文件，它的内容与 `def.mk` 相似：

```makefile
# this is a makefile to test ifndef

.PHONY: all

a=
b=$(a)

ifndef a
c="a is not defined"
else
c="a is defined"
endif

ifndef b
d="b is not defined"
else
d="b is defined"
endif

all:
    @echo "vari a is:" $(a)
    @echo "vari b is:" $(b)
    @echo "vari c is:" $(c)
    @echo "vari d is:" $(d)
```

现在执行下面的 `make` 命令并查看输出结果。

```bash
make -f ndef.mk
```
