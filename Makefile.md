## Makefile 使用说明

Make 主要用于处理 C 和 C++的编译工作，但不只能处理 C 和 C++，所有编译器/解释器能在命令行终端运行的编程语言都可以处理(例如 Java、Python、 Golang、 Rust…)。Make 也不只能用来处理编程语言，所有基于一些文件(依赖)的改变去更新另一些文件(目标)的工作都可以做

### 规则

```txt
第一种
target … (目标): prerequisites …(依赖)
第二种
target … (目标): prerequisites …(依赖); recipe(方法) ;…
```

### Makefile 文件的命名与指定

Make 会自动查找 makefile 文件，查找顺序为 GNUmakefile -> makefile -> Makefile（最常用，建议使用）

```shell
# 手动指定名字
make -f mkfile  # make -f <filename>
make --file=mkfile # make --file=<filename>
```

### Makefile 文件内容组成

- 显式规则 -- 显式指明何时以及如何生成或更新目标文件，显式规则包括目标、依赖和更新方法三个部分
- 隐式规则 -- 根据文件自动推导如何从依赖生成或更新目标文件
- 变量定义 -- 定义变量并指定值，值都是字符串，类似 C 语言中的宏定义(#define)，使用时将值展开到引用位置
- 指令 -- 在 make 读取 Makefile 的过程中做一些特别的操作
  1、读取(包含)另一个 makefile 文件(类似 C 语言中的#include)
  2、确定是否使用或略过 makefile 文件中的一部分内容(类似 C 语言中的#if)
  3、定义多行变量
- 注释 -- 一行当中 # 后面的内容都是注释，不会被 make 执行 \\#表示使用#符号

#### 目标

1.Makefile 中会有很多目标，但最终目标只有一个，其他所有内容都是为这个最终目标服务的，写 Makefile 的时候先写出最终目标，再依次解决总目标的依赖

2.一般情况第一条规则中的目标会被确立为最终目标，第一条规则默认会被 make 执行

3.通常来说目标是一个文件，一条规则的目的就是生成或更新目标文件

4.make 会根据目标文件和依赖文件最后修改时间判断是否需要执行更新目标文件的方法。如果目标文件不存在或者目标文件最后修改时间早于其中一个依赖文件最后修改时间，则重新执行更新目标文件的方法。否则不会执行

5.除了最终目标对应的更新方法默认会执行外，如果 Makefile 中一个目标不是其他目标的依赖，那么这个目标对应的规则不会自动执行。需要手动指定，方法为 make target

6.可以使用.DEFAULT_GOAL 来修改默认最终目标

```Makefile
.DEFAULT_GOAL = main #修改默认最终目标为第二条的main
all:
    @echo all
clean:
    rm -rf *.out *.o *.exe
    @echo clean
main:
    @echo main
```

#### 伪目标

如果一个标并不是一个文件，则这个目标就是伪目标。例如 clean 。如果说在当前目录下有一个文件名称和这个目标名称冲突了，则这个目标就没法执行。这时候需要用到一个特殊的目标 .PHONY，将上面的 clean 目标改写如下;这样即使当前目录下存在与目标同名的文件，该目标也能正常执行

```Makefile
.PHONY: clean
clean:
    rm block.o command.o input.o main.o scene.o test.o
    rm sudoku.exe
```

##### 伪目标的其他应用方式

如果一条规则的依赖文件没有改动，则不会执行对应的更新方法。如果需要每次不论有没有改动都执行某一目标的更新方法，可以把对应的目标添加到.PHONY 的依赖中 每次执行 make 都会更新 test.o，不管其依赖文件有没有改动

```Makefile
test.o: test.cpp test.h
        g++ -c test.cpp

.PHONY: clean test.o
```

#### 依赖

- 普通依赖 -- 直接列在目标后面

- order-only 依赖
