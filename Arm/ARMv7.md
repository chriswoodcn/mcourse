### Cortex-A 系列处理器介绍

#### ARM

ARM 一般有两个含义
ARM 公司，不生产，只进行 CPU 的框架设计
ARM 架构 Cortex-M、Cortex-A、Cortex-R

#### 裸机编程

没有操作系统运行之前的一段代码，可以是汇编也可以是 c 语言实现
bootloader 是一个裸机程序

#### ARM 内核发展

ARM 在 Cortex-A 系列处理器大体上按性能可以排序为：Cortex-A77 处理器、Cortex-A75 处理器、
Cortex-A73 处理器、 Cortex-A57 处理器、 Cortex-A53 处理器、 Cortex-A15 处理器、 Cortex-A9 处理器、 Cortex-A7 处理器、Cortex-A5 处理器等

ARM 产品指令集架构有 ARMv4、ARMv7、ARMv8，ARMv7 之后对 CPU 核心名称进行了调整，改用 Cortex-A,
Cortext-M 和 Cortex-R。
A 系列主要用于操作系统性能较好，M 系列通常用于单片机开发，R 系列主要用于实时控制方面
ARMv8 架构支持了 64bit 的指令集

#### 指令集 CPU 核心、CPU、SoC 区别

指令集通常是指 ARMv7 指令、ARMv8 指令集架构，这部分定义了整体的架构，例如定义了工作模式，中断的处理方法。

CPU 核心是指指令集的具体实现 Cortex-A7 就是根据 ARMv7 指令集来实现的 CPU 核心。

STM32MP157 是意法半导体根据 Cortex-A7 的 CPU 核心设计出来的一款 SoC，SoC 除了 CPU 之外还集成了很多控制器单元，例如 LCD 控制器单元和 UART 控制器单元等。

#### STM32MP157

##### 1.芯片资料

https://www.st.com/zh/microcontrollers-microprocessors/stm32mp157a.html#documentation

2 个 Cortex-A7 核心 MHZ 1 个 Cortex-M4 核心主频 209MHZ

通常需要下载数据手册、参考手册、编程手册、勘误手册

数据手册--介绍硬件特性，软件工程师一般查管脚

参考手册--数据手册的细化，介绍每个寄存器的使用，和软件开发关系密切

编程手册--讲述和芯片相关的体系结构的一些指令

勘误手册--介绍目前该芯片已知的问题，避坑

##### 2.ARM 资料

### Cortex-A7 开发环境

### Cortex-A7 结构

### Cortex-A7 内核存储系统和流水线

### ARM 基础指令

### ARM 处理器指令集

### ARM 汇编程序组成

### ARM 汇编程序设计

### Cortex-A7 GPIO

### Cortex-A7 UART
