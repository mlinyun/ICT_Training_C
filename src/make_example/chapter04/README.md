# Makefile —— 目标、依赖与通配符

## Make 对最终目标的认定

一般情况下 makefile 的最终目标是第一条规则的目标。 提供的代码文件中包含了测试需要用到的 makefile 文件，内容如下：

```makefile
# this is a makefile to verify the default aim

aim_1:
    @echo "this is " $@

aim_2:
    @echo "this is " $@

aim_3:
    @echo "this is " $@
```

从内容上看 makefile 中指定了三个目标，执行的动作都是打印当前执行目标的名称。变量 `$@` 会被 `make` 自动展开为目标名称。

现在执行下面的命令，并观察输出结果。

```bash
make aim_1; make aim_2; make aim_3
```

终端的输出结果如下所示：

```plaintext
this is  aim_1
this is  aim_2
this is  aim_3
```

> shell 中可以使用分号隔开一系列指令并顺序执行

执行 `make` 命令而不指定具体的目标

```bash
make
```

终端的输出结果如下所示：

```plaintext
this is  aim_1
```

从结果中可以看出 `make` 将第一个目标 `aim_1` 做为最终目标。 感兴趣的同学可以自己调换一下 `aim_1`、 `aim_2` 与 `aim_3` 的顺序，看看最终目标是否会随之改变

### 判断最终目标时的特殊情况

第一种特殊情况是当目标名以符号「.」开头且其后跟的不是斜线符号「/」（即不被解析为目录符号）时，此目标无法作为最终目标。如前面所述的 `.PHONY:`，这个目标的依赖都被视为伪目标，该规则可以被执行，但无法作为最终目标。 提供的源文件已有 `phony_make` 文件，内容如下：

```makefile
# this is a makefile to verify the default aim

.PHONY: aim_2
    @echo "this is " $@

aim_1:
    @echo "this is " $@

aim_2:
    @echo "this is " $@

aim_3:
    @echo "this is " $@
```

从内容上看，目标 `.PHONY` 的名字是以符号「.」开头且后面没有跟符号「/」我们可以知道 `.PHONY` 虽然是第一个目标但是不会被作为最终目标，而 `aim_1` 则会是真正的最终目标。

执行下面的命令：

```bash
make -f phony_make .PHONY
```

从终端的输出结果我们可以看出 `.PHONY` 所在的规则正确的执行了

现在直接执行 `make` 命令而不指定具体的规则，观察输出结果。

```bash
make -f phony_make
```

从终端的输出结果可以看出 `aim_1` 才是最终目标

第二种特殊情况是模式规则中的目标不会被作为最终目标。通过提供的 `pattern_make` 文件来进行测试，其内容如下：

```makefile
# this is a makefile to verify the default aim

%:
    @echo "this is " $@

aim_1:
    @echo "this is " $@

aim_2:
    @echo "this is " $@

aim_3:
    @echo "this is " $@
```

对比 makefile 文件，其第一条规则变成了模式规则，「%」符号可以匹配任何未显示定义的目标

输入下面的命令执行模式规则，观察执行后的输出结果

```bash
make -f pattern_make 123
```

从终端的输出结果说明模式规则得到了正确的执行，「%」匹配到了未定义的字符串 `123`

现在执行下面的命令但不指定具体的规则名称

```bash
make -f pattern_make
```

从终端的输出结果说明了模式规则中的目标不会被作为最终目目标

第三种特殊情况是使用 `MAKEFILES` 指定的文件会被 `make` 首先读入，但其中的目标无法作为最终目标。通过提供的 `envir_make` 文件来进行测试，具体内容如下：

```makefile
# this is a makefile to verify the default aim

envir_1:
    @echo "this is " $@
```

文件中包含了一个 `envir_1` 目标。 现在修改 makefile，在 `aim_2` 后面增加依赖项 `envir_1`，用以确认 `envir_make` 是否被正常读入。修改后 makefile 中的目标 `aim_2` 内容如下：

```makefile
aim_2: envir_1
    @echo "this is " $@
```

接下来将 `envir_make` 加入到环境变量 `MAKEFILES` 中。

```bash
export MAKEFILES=envir_make
```

现在执行 `make` 命令：

```bash
make aim_2
```

从终端的输出结果说明被 `MAKEFILES` 指定的 `envir_make` 文件被成功的解析

现在直接输入 `make` 命令并查看输出结果，说明 `aim_1` 才是最终目标

最后一种特殊情况是关键字 `include` 所引用进 makefile 中的规则，它的目标会被作为最终目标。

清空 `MAKEFILES` 防止对实验结果产生干扰。

```bash
export MAKEFILES=
```

再次修改 makefile 在 `aim_1` 目标之前加入对 `envir_make` 文件的包含，增加的 makefile 内容如下：

```makefile
include envir_make
```

执行 `make` 命令，此时终端输出的内容如下：

```plaintext
this is  envir_1
```

可见 `envir_make` 中的 `envir_1` 目标被作为最终目标进行了重建

## makefile 最终目标的重建

makefile 中的规则传递给 `make` 两条信息：

1. 目标何时重建
2. 目标如何重建

而目标何时重建的依据如下：

1. 目标是否为伪目标，若是则需要执行重建，否则参考第 2 条
2. 目标是否存在，若存在，则参考第 3 条，若不存在则需要执行重建
3. 目标文件是否比其全部依赖项都新，若比其任一依赖项文件要旧则需要执行重建

先来验证伪目标的重建，提供进行验证的 `rebuild_make` 文件的内容如下：

```makefile
# this is a makefile to verify the rebuild rule

aim_1: test_1
    touch aim_1

aim_2:
    @echo "this is " $@
```

从内容上看最终目标为 `aim_1`，其依赖项为 `test_1`

新建一个 `test_1` 文件并执行 `make` 命令

```bash
touch test_1; make -f rebuild_make; ls -l aim_1
```

从终端的输出结果说明当前路径下有一个 `aim_1` 文件被生成。判断流程：`aim_1` 不是伪目标 -> `aim_1` 不存在 -> 执行重建

现在执行 `make` 命令：

```bash
make -f rebuild_make
```

终端的输出结果如下：

```plaintext
make: 'aim_1' is up to date.
```

其判断流程如下：`aim_1` 不是伪目标 -> `aim_1` 存在 -> `aim_1` 比 `test_1` 时间戳要新 -> 不执行重建。

现在重新生成 `test_1`，再执行 `make` 命令：

```bash
touch test_1; make -f rebuild_make; ls -l aim_1
```

终端的输出结果如下：

```plaintext
touch aim_1
-rw-r--r-- 1 shiyanlou shiyanlou 0 1月  12 11:33 aim_1
```

这次的判断流程：`aim_1` 不是伪目标 -> `aim_1` 存在 -> `aim_1` 比 `test_1` 时间戳旧 -> 重建最终目标

最后再看伪目标的情况，我们不再更新 `test_1` 文件，此时执行 `make` 依然会出现 「'aim_1' is up to date」的提示，并且 `aim_1` 不会被重建

现在修改 `rebuild_make` 文件，添加伪目标 `aim_1`，此时 `rebuild_make` 的内容如下：

```makefile
# this is a makefile to verify the rebuild rule

.PHONY: aim_1

aim_1: test_1
    touch aim_1

aim_2:
    @echo "this is " $@
```

执行 `make` 命令：

```bash
make -f rebuild_make; make -f rebuild_make; make -f rebuild_make
```

终端的输出结果如下：

```plaintext
touch aim_1
```

可以看出无论执行多少次 `make -f rebuild_make` 命令，最终目标都会重建

## Makefile 的依赖类型

GNU make 的规则中可以使用两种不同类型的依赖。

| 类型            | 描述                                                         |
| --------------- | ------------------------------------------------------------ |
| 常规依赖        | 告诉 `make` 目标重建所需的依赖文件以及何时需要更新目标。     |
| order-only 依赖 | 告诉 `make` 目标重建所需的依赖文件，这些依赖文件的更新不会导致目标被重建。order-only 依赖以管道符号「\|」开始，管道符号左边为常规依赖项，管道符号右边为 order-only 依赖项。 |

通过提供的 `order_make` 文件对常规依赖进行测试，其主要内容如下。

```makefile
# this is a makefile to verify the order-only rule

.PHONY: clean

aim_1: test_1 | test_2 test_3
    touch aim_1

clean:
    rm -f test_1 test_2 test_3 aim_1
```

从内容上可以看出 `aim_1` 规则的常规依赖项为 `test_1`，order-only 依赖项为 `test_2` 和 `test_3`。

执行 `make -f order_make clean`，清除各项文件，并手动生成 `test_1`、`test_2` 与 `test_3` 文件。

```bash
make -f order_make clean; touch test_1 test_2 test_3; ls -l test*
```

执行 `make -f order_make` 命令并查看生成的 `aim_1` 目标文件

```bash
make -f order_make; ls -l aim_1
```

创建新的 `test_2`，`test_3` 文件并重新执行 `make` 命令

```bash
touch test_2 test_3; make -f order_make
```

从终端的输出结果说明 `test_2`、`test_3` 文件的更新都不会影响到目标的重建。现在删除 `test_2` 并执行 `make` 命令测试目标是否会检查依赖项文件：

```bash
rm test_2; make -f order_make
```

终端的输出结果如下：

```plaintext
make: *** No rule to make target 'test_2', needed by 'aim_1'。 停止。
```

说明 order-only 依赖项对应的文件依然会被 `make` 检查。

## 文件名通配符的使用

makefile 文件中通配符的用法和含义与 linux 的 Bourne shell 相同。下面的表格列举了一些常用的通配符。

| 通配符 | 功能                                                         |
| ------ | ------------------------------------------------------------ |
| *      | 匹配任意长度的任意字符。（注意：匹配文件名，无法匹配 makefile 文件中的规则等字段）。 |
| ?      | 匹配单个任意字符。                                           |
| [...]  | 匹配括号中指定的任意一个字符。                               |
| ~      | 代表当前用户目录                                             |

通配符出现在下面场合：

- 可以出现在规则的目标或依赖项中。
- 可以出现在规则的命令中。

通配符的使用变化很多，此处使用简单的实验来进行展示。在我们提供的 `wildcard_make` 文件中就对通配符进行了简单的使用，其内容如下：

```makefile
# this is a makefile test for wildcard

.PHONY: all clean prepare test_1

all: aim_1

aim_%: test_*
    @echo "aim : " $@ "depen : " $^
    @cd ~ ; echo "print user home path:";pwd
    @ls *

test_%:
    touch $@

test_1:test_4
    @echo "exe " $@

clean:
    rm -f test_*

prepare:
    touch test_1 test_2 test_3
```

从内容上我们可以知道 `wildcard_make` 使用 `all` 作为最终目标，依赖项为 `aim_1`。 `aim_1` 规则与 `aim_%` 相匹配，依赖项为所有的以 `test_` 开头的文件。命令执行后将为打印一些信息。 `test_` 开头的文件名若为 `test_1`，则会依赖于 `test_4`，并打印执行 `test_1` 目标的信息。 `test_4` 匹配 `test_%` 规则，会新建一个 `test_4` 文件

现在先清除一些干扰测项，并生成所需的文件

```bash
make -f wildcard_make clean; make -f wildcard_make prepare
```

执行 `make` 命令，观察输出结果。

```bash
make -f wildcard_make
```

终端输出的内容如下：

```plaintext
touch test_4
exe  test_1
aim :  aim_1 depen :  test_1 test_2 test_3
print user home path:
/home/shiyanlou
aim_1       makefile    pattern_make  README.md     test_1  test_3  wildcard_make
envir_make  order_make  phony_make    rebuild_make  test_2  test_4
```

可见由于依赖项层层传递，最先执行的是 `test_4` 目标，生成 `test_4` 文件， 接下来打印 `test_1` 的执行信息， 最后执行 `aim_1` 目标打印相关的信息。 此测试演示了在依赖项和命令行中使用文件名通配符匹配，并成功匹配到了 `test_1`、`test_2` 和 `test_3` 文件和用户宿主目录
