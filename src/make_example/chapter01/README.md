# Makefile 基础 —— 初识 Makefile

## Makefile 的基础规则与命名方式

### makefile 的基础规则

编写 `main.c` 文件，在本次实验中将用简单的 `hello world!` 程序来验证 makefile 的基本规则，由于提供的源代码中已包含编写好的 `main.c` 文件，因此我们可以直接拿来使用。`main.c` 文件的主要内容如下：

```C
#include <stdio.h>

int main(void)
{
    printf("hello world!\n");
    return 0;
}
```

因为 makefile 是为了自动管理编译、链接流程而存在的，因此 makefile 的书写需要遵照一定的书写规则。

```makefile
TARGET... : PREREQUISITES...
COMMAND
```

> `TARGET`：规则目标，可以是一个 object file (目标文件)，也可以是一个执行文件，还可以是一个标签（label）
> `PREREQUISITES`：要生成那个 target 所需要的文件或是目标，即规则依赖
> `COMMAND`：也就是 make 需要执行的命令，**必须以 [TAB] 开始**，由 shell 执行

编写一个简单的 makefile 文件用来管理 `main.c` 文件的编译，makefile 文件的内容如下：

```makefile
main: main.o
    gcc -o main main.o

main.o: main.c
    gcc -c main.c
```

`make` 工具的基本使用方法为：`make TARGET`。

现在在终端输入命令：

```bash
make main.o
```

从终端的输出结果说明 shell 执行了命令 `gcc -c main.c`

接下来输入以下命令：

```bash
make main
```

从终端输出结果说明 shell 执行了命令 `gcc -o main main.o`

最后在终端中输入以下命令：

```bash
./main
```

从终端的输出结果说明程序得到了正确的执行

在进行自动化编译之前，我们将生成的多余文件进行删除

```bash
rm main.o main
```

由于我们的最终的目标是 `main` 文件，实际上我们并不关心中间目标文件 `main.o`。现在尝试只运行一次 `make` 编译出我们需要的最终目标

```bash
make main
```

从终端的输出内容可以看出 `make` 还是先生成 makefile 中 `main` 的依赖文件 `main.o`，再链接生成 `main` 文件

让 `make` 自动寻找目标，即在 `make` 命令后不添加任何参数直接运行

首先删除之前产生的 `main` 和 `main.o` 文件

```bash
rm main main.o
```

然后在终端中输入命令：

```bash
make
```

终端的输出内容跟之前的输出内容相同，这是因为默认情况下，`make` 会以第一条规则作为其终极目标

现在我们尝试修改 makefile，在目标 `main` 之前再增加一条规则：

```makefile
dft_test: middle_file
    mv middle_file dft_test

middle_file:
    touch middle_file
```

**注意**：在将这段代码复制到 makefile 中时需要观察一下此时 tab 的默认格式是 space:4 表示使用 4 个空格代替 制表符

这样的话在执行 make 命令会出现以下错误：

```plaintext
makefile:4: *** missing separator。 停止。
```

解决办法是依次点击 **Space:4**->**Indent Using Tabs**->**4 Configured Tab Size** 然后删除 `Command` 那一行的缩进，重新使用 tab 缩进，保存之后重新执行 `make` 命令，问题将得以解决

执行命令：

```bash
make
```

若没有报错说明规则得到了正确的执行，同时在当前文件夹下会产生一个新的文件 `dft_test`。

### makefile 的命名规则

目前为止，我们写的自动编译规则都放在 makefile 中，通过实验也可证明了 `make` 工具会自动调用 makefile 文件。 是否文件名必须命名为「makefile」呢？ 然而并不是，GNU make 会按默认的优先级查找当前文件夹的文件，查找的优先级为： 「GNUmakefile」> 「makefile」> 「Makefile」。

接下来对 makefile 名称的优先级进行测试。

新建 GNUmakefile 文件，添加以下内容：

```makefile
# this is a GNUmakefile

.PHONY: all

all:
    @echo "this is GNUmakefile"
```

新建 Makefile 文件，添加以下内容：

```makefile
# this is a Makefile

.PHONY: all

all:
    @echo "this is Makefile"
```

查看一下当前目录文件，现在应该有三个 `make` 能够识别到的文件。

```bash
ls *file* -hl
```

执行 `make` 命令，查看 Makefile 的执行情况。

```bash
make
```

从终端的输出结果说明 `make` 调用的是 GNUmakefile，删除 GNUmakefile 再执行一次 `make` 命令，其调用的是 makefile，删除 makefile 再执行 `make` 命令，其调用的是 Makefile

说明 Makefile 是三者中优先级最低。然而在创建 makefile 文件时推荐以 makefile 或者 Makefile 进行命名，而不使用 GNUmakefile ，因为 GNUmakefile 只能被 GNU 的 make 工具识别到

## Makefile 之时间戳

`make` 命令在执行时会自动检测依赖文件的时间戳，具体规则如下：

1. 若依赖文件不存在或者依赖文件的时间戳比目标文件新，则执行依赖文件对应的命令
2. 若依赖文件的时间戳比目标文件老，则忽略依赖文件对应的命令

接下来对 makefile 时间戳规则进行验证

将 makefile 文件内容还原，还原后的内容应该与下面给出的代码一致：

```makefile
main: main.o
    gcc -o main main.o

main.o: main.c
    gcc -c main.c
```

为 makefile 打上 `v1.0.patch` 补丁，增加一些新的内容。

```bash
patch -p2 < v1.0.patch
```

此时 makefile 的内容如下：

```makefile
#this is a makefile example

main: main.o testa testb
 gcc -o main main.o

main.o: main.c
 gcc -c main.c

testa:
 touch testa

testb:
 touch testb

```

清除可能存在的中间文件

```bash
rm main.o testa testb
```

执行 `make` 命令。

```bash
make
```

`make` 命令执行后分别生成 `main.o`、`testa`、`testb` 这三个中间文件。这验证了时间戳规则中的第一条

现在删除 `testb` 文件，再观察 `make` 会如何执行。

```bash
make
```

从终端的输出结果如图：可见 `make` 分别执行了 `testb` 和 `main` 两条规则，`main.o` 和 `testa` 规则对应的命令没有被执行。这验证了 makefile 时间戳规则中的第二条

## Makefile 依赖执行顺序

从上面的内容可以看出 `make` 目标文件的依赖文件是按照从左到右的顺序生成的。 它对应规则 `main`。

```makefile
main:main.o testa testb
    gcc -o main main.o
```

`make` 按照顺序分别执行 `main.o`、`testa`、`testb` 所对应的规则。 现在我们调换 `main.o`、`testa`、`testb` 的顺序。 修改 makefile 文件的 `main` 规则的依赖顺序：

```makefile
main: testa testb main.o
```

清除上次编译过程中产生的中间文件：

```bash
rm main.o testa testb
```

执行 `make` 命令。

```bash
make
```

从终端的输出结果可见 `make` 的确是按照从左到右的规则分别执行依赖文件对应的命令

## Makefile 中的变量、「.PHONY」与「-」

makefile 也可以使用变量，它类似于 C 语言中的宏定义。 变量可以直接使用「vari=string」的写法来定义，并以「$(vari)」格式来使用。 我们用变量来定义目标的依赖项，使 makefile 保持良好的扩展性

### 在 makefile 中定义并使用变量

将 makefile 还原至以下内容：

```makefile
main: main.o
    gcc -o main main.o

main.o: main.c
    gcc -c main.c
```

为 makefile 打上`v1.0.patch`补丁，并移除旧的中间文件。

```bash
patch -p2 < v1.0.patch
rm main.o testa testb
```

在目标 `main` 之前定义一个变 `depen`：

```makefile
#this is a makefile example

depen=main.o testa testb

main: main.o testa testb
 gcc -o main main.o

main.o: main.c
 gcc -c main.c

testa:
 touch testa

testb:
 touch testb

```

修改 `main` 的依赖声明。

```makefile
main: $(depen)
```

执行 `make` 命令，并观察输出结果。

从终端的输出结果可以看出 makefile 依然能够正常执行。 就算之后 `main` 目标的依赖项有变化时，也只需修改 `depen` 变量的值即可

为 makefile 添加 `clean` 规则，因为每次测试 makefile 的时候我们都要清除中间文件，为了使得编译工程更加自动化，我们在 makefile 中添加规则让其自动清除

在 makefile 中修改 `depen` 变量，增加 `clean` 依赖：

```makefile
depen=clean main.o testa testb
```

增加 `clean` 规则及其命令。

```makefile
clean:
    rm main.o testa testb
```

此时 makefile 的内容如下：

```makefile
# this is a makefile example

depen=clean main.o testa testb

main: $(depen)
 gcc -o main main.o

main.o: main.c
 gcc -c main.c

testa:
 touch testa

testb:
 touch testb

clean:
 rm main.o testa testb

```

执行 `make` 命令并观察，执行结果，说明现在 `make` 会先清除掉上次编译的中间文件并重建新的对应的文件

在 `clean` 规则中也使用 `depen` 变量。

```makefile
clean:
    rm $(depen)
```

然而当我们执行了 `make` 命令之后，发现问题产生了，出现了如下的错误

```plaintext
rm clean main.o testa testb
rm: 无法删除'clean': 没有那个文件或目录
makefile:18: recipe for target 'clean' failed
make: *** [clean] Error 1
```

原来是因为 `depen` 变量指明 `clean` 为依赖项，因此执行 `rm` 命令时也会试图删除 `clean` 文件，这时就会出现错误。 而 `make` 在执行命令行过程中出现错误后会退出执行

### 「-」的使用

因为在大部分情况下我们不会将删除一个不存在文件时所产生的错误作为真正的错误来看待，为了让 `rm` 命令在执行过程中即使出现了错误，`makefile` 也能够继续执行不退出，我们需要用到「-」符号。 而「-」的作用是让 `make` 忽略该指令的错误。

现在修改 makefile 中的 clean 规则：

```makefile
clean:
    -rm $(depen)
```

执行 `make` 命令并观察输出结果，从输出结果来看，虽然 `rm` 指令报出错误，`make` 却依然可以生成 `main` 文件

### 伪目标的使用

前面提到 makefile 依赖文件的时间戳若比目标文件旧，则对应规则的命令不会执行。 我们现在定义了一个 `clean` 规则，但如果文件夹下正好有一个 `clean` 文件会发生什么样的冲突呢？ 我们先在当前目录下先新建一个 clean 文件：

```bash
touch clean
```

执行 `make` 命令，并观察输出结果，发现 `clean` 规则没有的到执行，因为 `clean` 文件已经存在。然而 `clean` 实际上是一个伪目标，我们并不期望它会与真正 `clean` 文件有任何关联。 因此需要使用 `.PHONY` 来声明伪目标

接下来修改 makefile 在变量 `depen` 之前加入一条伪目标声明

```makefile
.PHONY: clean
```

执行 `make` 命令并观察输出结果，可以看到 makefile 又能得到正常执行了，并且所有流程都符合我们的预期

现在删除掉 `main` 依赖项 `testa` 和 `testb` 因为在生成 `main` 文件过程中并不需要用到这两个文件。 修改 makefile 的 `depen` 变量：

```makefile
depen=clean main.o
```

执行 `make` 命令并观察输出结果

学到这里，我们就已经可以随心所欲的定制 `main` 的依赖规则了
