## Makefile 使用说明

Make 主要用于处理 C 和 C++的编译工作，但不只能处理 C 和 C++，所有编译器/解释器能在命令行终端运行的编程语言都可以处理(例如 Java、Python、 Golang、 Rust…)。Make 也不只能用来处理编程语言，所有基于一些文件(依赖)的改变去更新另一些文件(目标)的工作都可以做

> 官方文档: https://www.gnu.org/software/make/manual/make.html

### 基本规则

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
make -C . #指定Makefile所在目录
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

### 目标

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

### 伪目标

如果一个标并不是一个文件，则这个目标就是伪目标。例如 clean 。如果说在当前目录下有一个文件名称和这个目标名称冲突了，则这个目标就没法执行。这时候需要用到一个特殊的目标 .PHONY，将上面的 clean 目标改写如下;这样即使当前目录下存在与目标同名的文件，该目标也能正常执行

```Makefile
.PHONY: clean
clean:
    rm block.o command.o input.o main.o scene.o test.o
    rm sudoku.exe
```

#### 伪目标的其他应用方式

如果一条规则的依赖文件没有改动，则不会执行对应的更新方法。如果需要每次不论有没有改动都执行某一目标的更新方法，可以把对应的目标添加到.PHONY 的依赖中 每次执行 make 都会更新 test.o，不管其依赖文件有没有改动

```Makefile
test.o: test.cpp test.h
        g++ -c test.cpp

.PHONY: clean test.o
```

### 依赖

- 普通依赖 -- 直接列在目标后面

  1.如果这一依赖是由其他规则生成的文件，那么执行到这一目标前会先执行生成依赖的那一规则

  2.如果任何一个依赖文件修改时间比目标晚，那么就重新生成目标文件

- order-only 依赖

  1.依赖文件不存在时，会执行对应的方法生成，但依赖文件更新并不会导致目标文件的更新

```Makefile
targets : normal-prerequisites | order-only-prerequisites
# normal-prerequisites普通依赖可以为空
```

#### 指定依赖搜索路径

make 默认在 Makefile 文件所在的目录下查找依赖文件，如果找不到，就会报错。这时候就需要手动指定搜索路径，用 VPATH 变量或 vpath 指令

```Makefile
# VPATH用法
# VPATH = <dir1>:<dir2>:<dir3>...
VPATH = include:src #多个目录:隔开

# vpath指令用法
# vpath <pattern> <directories>
vpath %.h include  # .h文件在include目录下查找
vpath %.h include:headers  # .h文件在include或headers文件下查找
vpath % src   # 所有文件都在src下查找
vpath hello.cpp src  # hello.cpp文件在src查找
```

### shell

#### 执行终端

```Makefile
# 过SHELL变量手动指定Shell
SHELL = cmd.exe
# 默认的执行方式为一条指令重新调用一个Shell进程来执行。有时为了提高性能或其他原因，想让这个目标的所有指令都# 在同一进程中执行，可以在Makefile中添加 .ONESHELL, 这样所有指令都会在同一次Shell调用中执行
.ONESHELL:
```

#### Shell 语句回显问题

通常 make 在执行一条 Shell 语句前都会先打印这条语句，如果不想打印可以在语句开头在@

```Makefile
@echo hello
@g++ -o hello hello.cpp
# 也可以使用.SILENT来指定哪些目标的更新方法指令不用打印
.SILENT: main
```

#### 错误处理

如果一条规则当中包含多条 Shell 指令，每条指令执行完之后 make 都会检查返回状态，如果返回状态是 0，则执行成功，继续执行下一条指令，直到最后一条指令执行完成之后，一条规则也就结束了。如果过程中发生了错误，即某一条指令的返回值不是 0，那么 make 就会终止执行当前规则中剩下的 Shell 指令。
这时如果第一条 rm main.o hello.o 出错，第二条 rm main.exe 就不会执行。类似情况下，希望 make 忽视错误继续下一条指令。在指令开头-可以达到这种效果。

```Makefile
clean:
    -rm main.o hello.o
    -rm main.exe main.out
```

### 变量

Makefile 中的变量有点类似 C 语言中的宏定义，即用一个名称表示一串文本。但与 C 语言宏定义不同的是，Makefile 的变量值是可以改变的。变量定义之后可以在目标、依赖、方法等 Makefile 文件的任意地方进行引用。

#### 变量定义与使用

```Makefile
# 定义方式
# 变量名区分大小写，可以是任意字符串，不能含有":", "#", "="
# <变量名> = <变量值>  <变量名> := <变量值>  <变量名> ::= <变量值>
files = main.cpp hello.cpp
objects := main.o hello.o
var3 ::= main.o

# 使用方式
# $(<变量名>) 或者 ${<变量名>}
main.o : $(files) # 或者 ${files}
```

#### 变量赋值

GNU make 分两个阶段来执行 Makefile

第一阶段(读取阶段)：

1.读取 Makefile 文件的所有内容

2.根据 Makefile 的内容在程序内建立起变量

3.在程序内构建起显式规则、隐式规则

4.建立目标和依赖之间的依赖图

第二阶段(目标更新阶段)：

1.用第一阶段构建起来的数据确定哪个目标需要更新然后执行对应的更新方法

变量和函数的展开如果发生在第一阶段，就称作**立即展开**，否则称为**延迟展开**。立即展开的变量或函数在第一个阶段，也就是 Makefile 被读取解析的时候就进行展开。延迟展开的变量或函数将会到用到的时候才会进行展开，有以下两种情况： 1)在一个立即展开的表达式中用到、2)在第二个阶段中用到

**显式规则中，目标和依赖部分都是立即展开，在更新方法中延迟展开**

##### 递归展开赋值（延迟展开）

第一种方式就是直接使用=，这种方式如果赋值的时候右边是其他变量引用或者函数调用之类的，将不会做处理，直接保留原样，在使用到该变量的时候再来进行处理得到变量值（Makefile 执行的第二个阶段再进行变量展开得到变量值）

```Makefile
bar2 = ThisIsBar2No.1
foo = $(bar)
foo2 = $(bar2)

all:
@echo $(foo)  # Huh?
@echo $(foo2)  # ThisIsBar2No.2
@echo $(ugh)   # Huh?

bar = $(ugh)
ugh = Huh?
bar2 = ThisIsBar2No.2
```

##### 简单赋值(立即展开)

简单赋值使用:=或::=，这种方式如果等号右边是其他变量或者引用的话，将会在赋值的时候就进行处理得到变量值。（Makefile 执行第一阶段进行变量展开）

```Makefile
bar2 := ThisIsBar2No.1
foo := $(bar)
foo2 := $(bar2)

all:
    @echo $(foo)    # 空串，没有内容
    @echo $(foo2)    # ThisIsBar2No.1
    @echo $(ugh)    #

bar := $(ugh)
ugh := Huh?
bar2 := ThisIsBar2No.2
```

##### 条件赋值

条件赋值使用?=，如果变量已经定义过了（即已经有值了），那么就保持原来的值，如果变量还没赋值过，就把右边的值赋给变量。

```Makefile
var1 = 100
var1 ?= 200

all:
    @echo $(var1) # 100
```

##### 追加

使用+=在变量已有的基础上追加内容

```Makefile
files = main.cpp
files += hello.cpp

all:
    @echo $(files)
```

##### Shell 运行赋值

使用!=，运行一个 Shell 指令后将返回值赋给一个变量

```Makefile
# 这种赋值方式只适用于与Linux相同的Shell指令，Windows独有的指令不能这样使用。
gcc_version != gcc --version
files != ls
```

##### 定义多行变量

```Makefile
# define <varable_name>  # 默认为 =
# # 变量内容
# endef

# define <varable_name> :=
# # 变量内容
# endef

# define <varable_name> +=
# # 变量内容
# endef
echosomething = @echo This is the first line

define echosomething +=

@echo hello
@echo world
@echo 3
endef

all:
    $(echosomething)
```

##### 环境变量的使用

系统中的环境变量可以直接在 Makefile 中直接使用，使用方法跟普通变量一样

```Makefile
all:
    @echo $(USERNAME)
    @echo $(JAVA_HOME)
```

##### 变量替换

语法：$(var:a=b)，意思是将变量 var 的值当中每一项结尾的 a 替换为 b，

```Makefile
files = main.cpp hello.cpp
objs := $(files:.cpp=.o) # main.o hello.o
# 另一种写法
objs := $(files:%.cpp=%.o)
```

##### 变量覆盖

所有在 Makefile 中的变量，都可以在执行 make 时通过指定参数的方式进行覆盖。

```Makefile
OverridDemo := ThisIsInMakefile
all:
    @echo $(OverridDemo)

# make OverridDemo=ThisIsFromOutShell # 等号两边不能有空格
# 用这样的命令参数会覆盖Makefile中对应变量的值，如果不想被覆盖，可以在变量前加上override指令，override具有较高优先级，不会被命令参数覆盖
override OverridDemo := ThisWillNotOverride
```

##### 自动变量

$@：① 本条规则的目标名；② 如果目标是归档文件的成员，则为归档文件名；③ 在多目标的模式规则中, 为导致本条规则方法执行的那个目标名；
$<：本条规则的第一个依赖名称
$?：依赖中修改时间晚于目标文件修改时间的所有文件名，以空格隔开
$^：所有依赖文件名，文件名不会重复，不包含 order-only 依赖
$+：类似上一个， 表示所有依赖文件名，包括重复的文件名，不包含 order-only 依赖
$|：所有 order-only 依赖文件名
$\*：(简单理解)目标文件名的主干部分(即不包括后缀名)
$%：如果目标不是归档文件，则为空；如果目标是归档文件成员，则为对应的成员文件名

以下变量对应上述变量，D 为对应变量所在的目录，结尾不带/，F 为对应变量除去目录部分的文件名
$(@D) $(@F)
$(*D) $(*F)
$(%D) $(%F)
$(<D) $(<F)
$(^D) $(^F)
$(+D) $(+F)
$(?D) $(?F)

##### 绑定目标的变量

Makefile 中的变量一般是全局变量。也就是说定义之后在 Makefile 的任意位置都可以使用。但也可以将变量指定在某个目标的范围内，这样这个变量就只能在这个目标对应的规则里面保用

```Makefile
var1 = Global Var

first: all t2

all: var2 = Target All Var
all:
    @echo $(var1)
    @echo $(var2)

t2:
    @echo $(var1)
    @echo $(var2)

# 这种定义变量的方式，目标也可以使用模式匹配，这样所有能匹配上的目标范围内都可以使用这些变量
%.v: var2 = Target %.v Var

t2.v:
    @echo $@ -- $(var1)
    @echo $@ -- $(var2)

t3:
    @echo $@ -- $(var1)
    @echo $@ -- $(var2)
```

##### 二次展开

前面说的依赖中的变量都是在 Makefile 读取阶段立即展开的。如果想让依赖的的变量延迟展开，可以使用.SECONDEXPANSION:，添加之后，在依赖中使用变量时用$$，可以让变量在第二阶段进行二次展开，从而达到延迟展开的效果

```Makefile
VAR1 = main.cpp
.SECONDEXPANSION:
all: $$(VAR1)
    @echo $^

VAR1 = hello.cpp
```

### 自动推导与隐式规则

Makefile 中有一些生成目标文件的规则使用频率非常高，比如由.c 或.cpp 文件编译成.o 文件，这样的规则在 make 中可以自动推导，所以可以不用明确写出来，这样的规则称为隐式规则。

#### 一些 make 预定义的规则

##### C 语言编译

```Makefile
$(CC) $(CPPFLAGS) $(CFLAGS) -c
```

##### C ++编译

```Makefile
$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c
```

##### 链接

由.o 文件链接到可执行文件

```Makefile
$(CC) $(LDFLAGS) *.o $(LOADLIBES) $(LDLIBS)
```

#### 隐式规则中常用一些变量

这些变量都有默认值，也可以自行修改

```txt
CC
编译 C 语言的程序，默认为 cc
CXX
编译 C++的程序，默认为 g++
AR
归档程序，默认为 ar
CPP
C 语言预处理程序，默认为 $(CC) -E
RM
删除文件的程序，默认为 rm -f
CFLAGS
传递给 C 编译器的一些选项，如-O2 -Iinclude
CXXFLAGS
传递给 C++编译器的一些选项，如-std=c++ 11 -fexec-charset=GBK
CPPFLAGS
C 语言预处理的一些选项
LDFLAGS
链接选项，如-L.
LDLIBS
链接需要用到的库，如-lkernel32 -luser32 -lgdi32
```

### 多目标与多规则

显式规则中一条规则可以有多个目标，多个目标可以是相互独立的目标，也可以是组合目标，用写法来区分

#### 独立多目标

相互独立的多个目标与依赖之间直接用:，常用这种方式的有以下两种情况

1.只需要写目标和依赖，不需要写方法的时候

```Makefile
block.o input.o scene.o : common.h
# 等价于
# block.o : common.h
# input.o : common.h
# scene.o : common.h
```

2.生成(更新)目标的方法写法一样的，只是依赖与目标不一样时。

```Makefile
# block.o: block.cpp common.h block.h color.h
#     g++ -c block.cpp
# command.o: command.cpp command.h scene.h
#     g++ -c command.cpp
# input.o: input.cpp common.h utility.inl
#     g++ -c input.cpp
# main.o: main.cpp scene.h input.h test.h
#     g++ -c main.cpp
# scene.o: scene.cpp common.h scene.h utility.inl
#     g++ -c scene.cpp
# test.o: test.cpp test.h
#     g++ -c test.cpp
# 进行简写如下
block.o command.o input.o main.o scene.o test.o : common.h block.h command.h ...
    g++ -c $(@:%.o=%.cpp)
# 或者多个分开使用subst
block.o : common.h block.h command.h ...
    g++ -c $(subst .o,.cpp,$@)
```

#### 组合多目标

多目标与依赖之前用&:，这样的多个目标称为组合目标。与独立多目标的区别在于，独立多目标每个目标的更新需要单独调用一次更新方法。而组合多目标调用一次方法将更新所有目标,所有目标的更新方法都写到其中，每次更新只会调用一次

```Makefile
block.o input.o scene.o &: block.cpp input.cpp scene.cpp common.h
    g++ -c block.cpp
    g++ -c input.cpp
    g++ -c scene.cpp
```

#### 同一目标多条规则

同一目标可以对应多条规则。同一目标的所有规则中的依赖会被合并。但如果同一目标对应的多条规则都写了更新方法，则会使用最新的一条更新方法，并且会输出警告信息。

同一目标多规则通常用来给多个目标添加依赖而不用改动已写好的部分。

```Makefile
input.o: input.cpp utility.inl
    g++ -c input.cpp
main.o: main.cpp scene.h input.h test.h
    g++ -c main.cpp
scene.o: scene.cpp scene.h utility.inl
    g++ -c scene.cpp

input.o main.o scene.o : common.h #添加依赖common.h
```

#### 静态模式

独立多目标可以简化 Makefile 的书写，但是不利于将各个目标的依赖分开，让目标文件根据各自的依赖进行更新。静态模式可以在一定程度上改进依赖分开问题。

静态模式就是用%进行文件匹配来推导出对应的依赖。

```txt
targets …: target-pattern(目标模式): prereq-patterns(依赖模式) …
        recipe
        …
```

```Makefile
block.o : %.o : %.cpp %.h
    g++ -c $<
# block.o为目标，%.o为目标模式，%.cpp，%.h为依赖模式，对于这一条规则，%.o代表的是目标文件block.o，所以这里的%匹配的是block，因此，%.cpp表示block.cpp，%.h代表block.h，所以block.o : %.o : %.cpp %.h表示的意思同下面这种写法
# block.o : block.cpp block.h
# $<表示目标的第一个依赖，在这条规则中，$<表示block.cpp

# 利用模式匹配可以直接将所有.cpp到.o文件的编译简写为如下
%.o : %.cpp %.h
    g++ -c $<
```

### 条件判断

使用条件指令可以让 make 执行或略过 Makefile 文件中的一些部分。

```Makefile
# ifdef 判断一个变量是已否定义
OS = Linux
ifdef Win
    OS = Windows
else ifdef Mac
    OS= MacOS
endif

# ifndef 判断一个变量是否没被定义
ifndef FLAGS
    FLAGS = -finput-charset=utf-8
endif

# ifeq 判断两个值是否相等
version = 3.0

ifeq ($(version),1.0)            # ifeq后一定要一个空格
    msg := 版本太旧了，请更新版本
else ifeq ($(version), 3.0)
    msg := 版本太新了，也不行
else
    msg := 版本可以用
endif
# ifeq另一种写法
msg = Other
ifeq "$(OS)" "Windows_NT"
    msg = This is a Windows Platform
endif

ifeq '$(OS)' 'Windows_NT'
    msg = This is a Windows Platform
endif

ifeq '$(OS)' "Windows_NT"
    msg = This is a Windows Platform
endif

# ifneq 判断两个值是否不等
# 用法及参数同ifeq，只是判断结果相反
```

### 文本处理函数

Makefile 中调用函数的写法 $(function arguments) 或 ${function arguments}
$(function arg1,$(arg2),arg3 ...) # 参数之间不要有空格

#### 字符替换与分析

##### subst

```Makefile
# $(subst target,replacement,text) 文本替换函数，返回替换后的文本
#         --- 用relacement替换text中的target
#         --- target 需要替换的内容
#         --- replacement 替换为的内容
#         --- text 需要处理的内容，可以是任意字符串

objs = main.o hello.o
srcs = $(subst .o,.cpp,$(objs))
headers = $(subst .cpp,.h,$(srcs))

all:
    @echo $(srcs)
    @echo $(headers)
```

##### patsubst

```Makefile
# $(patsubst pattern,replacement,text) 模式替换，返回替换后的文本
#         --- pattern 需要替换的模式
#         --- replacement 需要替换为
#         --- text 待处理内容，各项内容需要用空格隔开

objs = main.o hello.o
srcs = $(patsubst %.o,%.cpp,$(objs))
headers = $(patsubst %.cpp,%.h,$(srcs))
```

##### strip

```Makefile
# $(strip string) 去除字符串头部和尾部的空格，中间如果连续有多个空格，则用一个空格替换，返回去除空格后的文本
#         --- string 需要去除空格的字符串

files = aa hello.cpp      main.cpp     test.cpp
files := $(subst aa,        ,$(files))
files2 = $(strip $(files))
```

##### findstring

```Makefile
# $(findstring find,string) 查找字符串，如果找到了，则返回对应的字符串，如果没找到，则反回空串
#         --- find 需要查找的字符串
#         --- string 用来查找的内容
files = hello.cpp main.cpp test.cpp
find = $(findstring hel,$(files))
find = $(findstring HEL,$(files))
```

##### filter

```Makefile
# $(filter pattern…,text) 从文本中筛选出符合模式的内容并返回
#         --- pattern 模式，可以有多个，用空格隔开
#         --- text 用来筛选的文本，多项内容需要用空格隔开，否则只会当一项来处理

files = hello.cpp main.cpp test.cpp main.o hello.o hello.h
files2 = $(filter %.o %.h,$(files))
```

##### filter-out

```Makefile
# $(filter-out pattern…,text) 与filter相反，过滤掉符合模式的，返回剩下的内容
#         --- pattern 模式，可以有多个，用空格隔开
#         --- text 用来筛选的文本，多项内容需要用空格隔开，否则只会当一项来处理

files = hello.cpp main.cpp test.cpp main.o hello.o hello.h
files2 = $(filter-out %.o %.cpp,$(files))
```

##### sort

```Makefile
# $(sort list) 将文本内的各项按字典顺序排列，并且移除重复项
#         --- list 需要排序内容

files = hello.cpp main.cpp test.cpp main.o hello.o hello.h main.cpp hello.cpp
files2 = $(sort $(files))
```

##### word

```Makefile
# $(word n,text) 用于返回文本中第n个单词
#         --- n 第n个单词，从1开始，如果n大于总单词数，则返回空串
#         --- text 待处理文本

files = hello.cpp main.cpp test.cpp main.o hello.o hello.h main.cpp hello.cpp
files2 = $(word 3,$(files))
```

##### wordlist

```Makefile
# $(wordlist start,end,text) 用于返回文本指定范围内的单词列表
#         --- start 起始位置，如果大于单词总数，则返回空串
#         --- end 结束位置，如果大于单词总数，则返回起始位置之后全部，如果start > end，什么都不返回

files = hello.cpp main.cpp test.cpp main.o hello.o hello.h main.cpp hello.cpp
files2 = $(wordlist 3,6,$(files))
```

##### words

```Makefile
# $(words text) 返回文本中单词数
#         --- text 需要处理的文本

files = hello.cpp main.cpp test.cpp main.o hello.o hello.h main.cpp hello.cpp
nums = $(words $(files))
```

##### firstword

```Makefile
$(firstword text) #返回第一个单词
```

##### lastword

```Makefile
$(lastword text) #返回最后一个单词
```

#### 文件名处理函数

##### dir

```Makefile
# $(dir file1 file2) 返回文件目录
#         --- file1 file2 需要返回目录的文件名，可以有多个，用空格隔开

files = src/hello.cpp main.cpp

files2 = $(dir $(files))
```

##### notdir

```Makefile
# $(notdir files) 返回除目录部分的文件名
#         --- files 需要返回文件列表，可以有多个，用空格隔开

files = src/hello.cpp main.cpp
files2 = $(notdir $(files))
```

##### suffix

```Makefile
# $(suffix files) 返回文件后缀名，如果没有后缀返回空
#         --- files 需要返回后缀的文件名，可以有多个，用空格隔开


files = src/hello.cpp main.cpp hello.o hello.hpp hello
files2 = $(suffix $(files))
```

##### basename

```Makefile
# $(basename files) 返回文件名除后缀的部分
#         --- files 需要返回的文件名，可以有多个，用空格隔开


files = src/hello.cpp main.cpp hello.o hello.hpp hello
files2 = $(basename $(files))
```

##### addsuffix

```Makefile
# $(addsuffix suffix,files) 给文件名添加后缀
#         --- suffix 需要添加的后缀
#         --- files 需要添加后缀的文件名，可以有多个，用空格隔开

files = src/hello.cpp main.cpp hello.o hello.hpp hello
files2 = $(addsuffix .exe,$(files))
```

##### addprefix

```Makefile
$(addprefix prefix,files)
        --- prefix 需要添加的前缀
        --- files 需要添加前缀的文件名，可以有多个，用空格隔开

files = src/hello.cpp main.cpp hello.o hello.hpp hello
files2 = $(addprefix make/,$(files))
```

##### join

```Makefile
# $(join list1,list2) 将两个列表中的内容一对一连接，如果两个列表内容数量不相等，则多出来的部分原样返回
#         --- list1 第一个列表
#         --- list2 需要连接的第二个列表

f1 = hello main test
f2 = .cpp .hpp
files2 = $(join $(f1),$(f2))  #hello.cpp main.hpp test
```

##### wildcard

```Makefile
# $(wildcard pattern) 返回符合通配符的文件列表
#         --- pattern 通配符

files2 = $(wildcard *.cpp)
files2 = $(wildcard *)
files2 = $(wildcard src/*.cpp)
```

##### realpath

```Makefile
# $(realpath files) 返回文件的绝对路径
#         --- files 需要返回绝对路径的文件，可以有多个，用空格隔开

f3 = $(wildcard src/*)
files2 = $(realpath $(f3))
```

##### abspath

```Makefile
# 返回绝对路径，用法同realpath，如果一个文件名不存在，realpath不会返回内容，abspath则会返回一个当前文件夹一下的绝对路径
$(abspath files)
```

#### 条件函数

##### if

```Makefile
# $(if condition,then-part[,else-part])  如果条件展开不是空串，则反回真的部分，否则返回假的部分
#         --- condition 条件部分
#         --- then-part 条件为真时执行的部分
#         --- else-part 条件为假时执行的部分，如果省略则为假时返回空串

files = src/hello.cpp main.cpp hello.o hello.hpp hello
files2 = $(if $(files),有文件,没有文件)
```

##### or

```Makefile
# $(or condition1[,condition2[,condition3…]]) 返回条件中第一个不为空的部分

f1 =
f2 =
f3 = hello.cpp
f4 = main.cpp
files2 = $(or $(f1),$(f2),$(f3),$(f4))
```

##### and

```Makefile
# $(and condition1[,condition2[,condition3…]]) 如果条件中有一个为空串，则返回空，如果全都不为空，则返回最后一个条件

f1 = 12
f2 = 34
f3 = hello.cpp
f4 = main.cpp
files2 = $(and $(f1),$(f2),$(f3),$(f4))
```

##### intcmp

```Makefile
# $(intcmp lhs,rhs[,lt-part[,eq-part[,gt-part]]])  比较两个整数大小，并返回对应操作结果（GNU make 4.4以上版本）
#         --- lhs 第一个数
#         --- rhs 第二个数
#         --- lt-part  lhs < rhs时执行
#         --- eq-part  lhs = rhs时执行
#         --- gt-part  lhs > rhs时执行
#         --- 如果只提供前两个参数，则lhs == rhs时返回数值，否则返回空串
#             参数为lhs,rhs,lt-part时，当lhs < rhs时返回lt-part结果，否则返回空
#             参数为lhs,rhs,lt-part,eq-part，lhs < rhs返回lt-part结果，否则都返回eq-part结果
#             参数全时，lhs < rhs返回lt-part，lhs == rhs返回eq-part, lhs > rhs返回gt-part

@echo $(intcmp 2,2,-1,0,1)
```

#### file

读写文件

```Makefile
# $(file op filename[,text]) 读写文件
#         --- op 操作
#                 > 覆盖
#                 >> 追加
#                 < 读
#         --- filename 需要操作的文件名
#         --- text 写入的文本内容，读取是不需要这个参数

files = src/hello.cpp main.cpp hello.o hello.hpp hello
write = $(file > makewrite.txt,$(files))
read = $(file < makewrite.txt)
```

#### foreach

```Makefile
# $(foreach each,list,process) 对一列用空格隔开的字符序列中每一项进行处理，并返回处理后的列表
#         --- each list中的每一项
#         --- list 需要处理的字符串序列，用空格隔开
#         --- process 需要对每一项进行的处理

list = 1 2 3 4 5
result = $(foreach each,$(list),$(addprefix cpp,$(addsuffix .cpp,$(each))))
```

#### call

将一些复杂的表达式写成一个变量，用 call 可以像调用函数一样进行调用。类似于编程语言中的自定义函数。在函数中可以用$(n)来访问第 n 个参数

```Makefile
# $(call funcname,param1,param2,…)
#         --- funcname 自定义函数（变量名）
#         --- 参数至少一个，可以有多个，用逗号隔开

dirof =  $(dir $(realpath $(1))) $(dir $(realpath $(2)))
result = $(call dirof,main.cpp,src/hello.cpp)
```

#### value

对于不是立即展开的变量，可以查看变量的原始定义；对于立即展开的变量，直接返回变量值

```Makefile
$(value variable)

var = value function test
var2 = $(var)
var3 := $(var)
all:
    @echo $(value var2)
    @echo $(value var3)
```

查看一个变量定义来源

```Makefile
$(origin variable)

var2 = origin function
all:
    @echo $(origin var1)    # undefined 未定义
    @echo $(origin CC)        # default 默认变量
    @echo $(origin JAVA_HOME) # environment 环境变量
    @echo $(origin var2)    # file 在Makefile文件中定义的变量
    @echo $(origin @)        # automatic 自动变量
```

#### flavor

```Makefile
# $(flavor variable)  查看一个变量的赋值方式

var2 = flavor function
var3 := flavor funciton
all:
    @echo $(flavor var1)    # undefined 未定义
    @echo $(flavor var2)    # recursive 递归展开赋值
    @echo $(flavor var3)    # simple 简单赋值
```

#### eval

```Makefile
# $(eval text) 可以将一段文本生成Makefile的内容

define eval_target =
eval:
    @echo Target Eval Test
endef

$(eval $(eval_target))
```

#### shell

用于执行 Shell 命令

```Makefile
files = $(shell ls *.cpp)
$(shell echo This is from shell function)
```

#### let

```Makefile
$(let var1 [var2 ...],[list],proc) 将一个字符串序列中的项拆开放入多个变量中，并对各个变量进行操作（GNU make 4.4以上版本）
        --- var 变量，可以有多个，用空格隔开
        --- list 待处理字符串，各项之间空格隔开
        --- proc 对变量进行的操作，结果为let的返回值
            将list中的值依次一项一项放到var中，如果var的个数多于list项数，那多出来的var是空串。如果
            var的个数小于list项数，则先依次把前面的项放入var中，剩下的list所有项都放入最后一个var中


list = a b c d
letfirst = $(let first second rest,$(list),$(first))
letrest = $(let first second rest,$(list),$(rest))


# 结合call可以对所有项进行递归处理
reverse = $(let first rest,$(1),$(if $(rest),$(call reverse,$(rest)) )$(first))
all: ; @echo $(call reverse,d c b a)
```

#### 信息提示函数

##### error

```Makefile
# $(error text)
#         --- text 提示信息

EXIT_STATUS = -1
ifneq (0, $(EXIT_STATUS))
    $(error An error occured! make stopped!)
endif
```

##### warning

```Makefile

```

##### info

```Makefile

```

### 同一项目中有多个 Makefile 文件

#### 包含其他 makefile 文件

使用 include 指令可以读入其他 makefile 文件的内容，效果就如同在 include 的位置用对应的文件内容替换一样。

```Makefile
include mkf1 mkf2 # 可以引入多个文件，用空格隔开
include *.mk    # 可以用通配符，表示引入所有以.mk结尾的文件
-include mkf1 mkf2 #如果要忽略错误，可以在include前加-
```

#### 嵌套 make

库文件 Makefile

```Makefile
vpath %.h ../include

CXXFLAGS += -I../include -fexec-charset=GBK -finput-charset=UTF-8

cpps := $(wildcard *.cpp)
objs := $(cpps:%.cpp=%.o)

libsudoku.a: $(objs)
    ar rcs $@ $^

$(objs): %.o : %.cpp %.h
```

main.cpp test.cpp 的 Makefile

```Makefile
CXXFLAGS += -I../include -fexec-charset=GBK -finput-charset=UTF-8
vpath %.h ../include
vpath %.a ../lib

../sudoku: main.o test.o -lsudoku
    $(CXX) -o $@ $^
```

总的 Makefile

```Makefile
.PHONY: all clean

all: subsrc

subsrc: sublib
    $(MAKE) -C src   #这一指令会自动进入src文件夹然后执行make

sublib:
    $(MAKE) -C lib  #这一指令会自动进入lib文件夹然后执行make。

clean:
    -rm *.exe src/*.o lib/*.o lib/*.a
```

可以通过 export 指令向子项目的 make 传递变量

```Makefile
export var  # 传递var
export      # 传递所有变量
unexport    # 取消传递
```

### 一些开源项目的 Makefile

```txt
redis:https://github.com/redis/redis

ffmpeg:https://github.com/FFmpeg/FFmpeg

aubio:https://github.com/aubio/aubio

libav:https://github.com/libav/libav

OpenH264:https://github.com/cisco/openh264

TinyVM:https://github.com/jakogut/tinyvm
```
