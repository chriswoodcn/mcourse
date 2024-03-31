## 系统移植

### 介绍

系统移植（System Porting）是将一个操作系统（通常是嵌入式操作系统）从一个硬件平台或架构移植到另一个硬件平台或架构的过程。这个过程可能涉及到许多不同的方面，包括硬件适配、驱动程序开发、引导加载程序（Bootloader）配置、文件系统适配、内核参数设置等等

系统移植的主要目的是使一个操作系统能够在不同的硬件平台上正常运行，并充分发挥其功能。在嵌入式领域，不同的硬件平台可能有不同的处理器架构、外设、内存布局等，因此需要进行适当的调整和配置，以确保操作系统能够正确地与硬件交互

通常情况下，系统移植需要进行以下工作：

1. 选择操作系统版本： 首先需要选择适合目标硬件平台的操作系统版本，确保其支持目标架构和硬件特性。
2. 硬件适配：修改操作系统的源代码，以适配新的硬件平台。这可能涉及修改底层驱动程序、中断处理、外设配置等。
3. 驱动程序开发： 编写或适配适合目标硬件的驱动程序，使操作系统能够与硬件进行通信。
4. 引导加载程序配置： 配置引导加载程序，使其能够正确加载和启动操作系统内核。
5. 文件系统适配： 调整文件系统以适应新的硬件存储和文件结构
6. 内核参数设置： 配置操作系统内核参数，以适应硬件资源和性能需求。
7. 调试和测试： 进行测试，确保操作系统在新硬件平台上稳定运行。调试可能涉及硬件问题、驱动程序问题、性能问题等

### 前置知识

- 启动加载器 (Bootloader)

系统启动的第一阶段是启动加载器的运行。在你的配置中，有两个级别的启动加载器：第一级 (FSBL) 和第二级 (SSBL)。这些启动加载器负责加载和运行更高级别的启动加载器，以及最终加载内核和文件系统

- 内核 (Kernel)

内核是操作系统的核心，它负责管理硬件资源、进程管理、文件系统等。在配置中，内核文件通常被放置在 bootfs 或者 rootfs 中。内核必须能够正确地加载和解释设备树 (Device Tree)。

- 设备树 (Device Tree)

设备树是一种描述硬件的机制，使内核能够根据硬件的不同配置进行正确的初始化。在你的配置中，设备树文件可能会附加在启动加载器 (ssbl 或 fsbl) 后面，作为启动加载器的一部分

### 标准 Linux 启动过程

1. 上电和自检 (Power On and Power-On Self-Test, POST)：

计算机上电，开始进行硬件初始化和自检。自检程序会检查硬件是否正常工作，并进行初始化。

2. 引导加载器 (Bootloader)：

引导加载器负责加载操作系统内核和根文件系统。常见的引导加载器包括 GRUB、U-Boot 等。引导加载器从引导设备（如硬盘、闪存）读取配置和内核映像。

3. 内核启动 (Kernel Boot)：

内核加载后，会被解压和初始化。内核首先会设置基本硬件参数，如内存管理、处理器模式等。初始化后，内核会启动第一个用户态进程 init

4. 初始化 (Init)：

内核启动 init 进程（通常是/bin/init 或/sbin/init）作为第一个用户态进程。init 负责启动和管理其他用户态进程，并初始化系统的各种资源。在现代系统中，init 通常被替代为更先进的 init 系统，如 systemd、Upstart 等。

5. 系统初始化 (System Initialization)：

在 init 或 init 系统的管理下，系统会进行初始化，包括加载系统配置、设置网络、加载驱动程序等。用户空间初始化 (User Space Initialization)：用户空间初始化涉及启动各种用户态进程和服务。启动登录管理器（如 GDM、LightDM），以便用户登录。用户登录后，登录管理器启动 X 服务器（如 Xorg）以及用户的窗口管理器或桌面环境。

6. 用户登录 (User Login)：

用户通过登录界面输入用户名和密码。登录管理器验证用户信息，如果正确，会创建用户的会话环境。

7. 用户会话 (User Session)：

一旦用户成功登录，桌面环境启动并提供一个用户界面。用户可以运行应用程序、访问文件、使用系统资源等

## 设备树详解

### 基础知识

- dts

硬件的相应信息都会写在.dts 为后缀的文件中，每一款硬件可以单独写一份例如 stm32mp157a-dk1.dts，一般在 Linux 源码中存在大量的 dts 文件，对于 arm 架构可以在 arch/arm/boot/dts 找到相应的 dts，一个 dts 文件对应一个 ARM 的 machine

- dtsi

对于一些相同的 dts 配置可以抽象到 dtsi 文件中，然后类似于 C 语言的方式可以 include 到 dts 文件中，对于同一个节点的设置情况，dts 中的配置会覆盖 dtsi 中的配置

- dtc

dtc 是编译 dts 的工具，可以在 Ubuntu 系统上通过指令 apt-get install device-tree-compiler 安装 dtc 工具，不过在内核源码 scripts/dtc 路径下已经包含了 dtc 工具

- dtb

dtb(Device Tree Blob)，dts 经过 dtc 编译之后会得到 dtb 文件，dtb 通过 Bootloader 引导程序加载到内核。所以 Bootloader 需要支持设备树才行；Kernel 也需要加入设备树的支持；

### DTS 结构与语法

```dts
[label:] node-name[@unit-address] {
  [properties definitions]
  [child nodes]
}
```

device tree 的基本单元是 node。这些 node 被组织成树状结构，除了 root node，每个 node 都只有一个 parent。一个 device tree 文件中只能有一个 root node。每个 node 中包含了若干的 property/value 来描述该 node 的一些特性。每个 node 用节点名字（node name）标识，节点名字的格式是 node-name@unit-address。如果 node 没有 reg 属性，该节点名字中必须不能包括@和 unit-address。

unit-address 的具体格式是和设备挂在哪个 bus 上相关；如对于 cpu，其 unit-address 就是从 0 开始编址，以此加一；如以太网控制器，其 unit-address 就是寄存器地址

设备树源文件的结构为

- 1 个 root 节点 /;
- root 节点下面含一系列子节点，node1、 node2...
- 节点 node1 又含有一系列子节点，child-node1 and child-node2
- 各个节点都有一系列属性
  这些属性可能为空，如 an-empty-property;可能为字符串，如 a-string-property;可能为字符串树组，如 a-string-list-property;可能为 Cells（由 u32 整数组成），如 second-child-property

### dts 组成

#### compatible

每一个 dts 文件都是由一个 root 的根节点组成，内核通过根节点/的兼容性即可判断它启动的是什么设备，其代码结构如下

```cpp
/ {
  model = "HQYJ FS-MP1A Discovery Board";  //model 属性值是，它指定制造商的设备型号。推荐的格式是：manufacturer，model
  compatible = "st,stm32mp157a-dk1", "st,stm32mp157", "hqyj,fsmp1a"; //compatible 属性值是,指定了系统的名称，是一个字符串列表，它包含了一个<制造商>,<型号>形式的字符串

  aliases {
    ethernet0 = &ethernet0;
    serial0 = &uart4;
    serial5 = &usart3;
  };
  chosen {   //chosen 节点不代表一个真正的设备，但功能与在固件和操作系统间传递数据的地点一样，如根参数，取代以前 bootloader 的启动参数，控制台的输入输出参数等
    stdout-path = "serial0:115200n8";
  };
//  ... ...
};
```

#### #address-cells 和#size-cells

```cpp
port {
  #address-cells = <1>; //#address-cells = <1>: 基地址、片选号等绝对起始地址所占字长，单位 uint32。
  #size-cells = <0>; //#size-cells = <1>: 长度所占字长，单位 uint32
  ltdc_ep0_out: endpoint@0 {
    reg = <0>;
    remote-endpoint = <&sii9022_in>;
  };
};
```

#### CPU addressing

在讨论寻址时，CPU 节点代表了最简单的情况。 每个 CPU 都分配有一个唯一的 ID，并且没有与 CPUID 相关联的大小

```cpp
cpus {
  #address-cells = <1>;
  #size-cells = <0>;
  cpu0: cpu@0 {
    compatible = "arm,cortex-a7";
    device_type = "cpu";
    reg = <0>;
    clocks = <&rcc CK_MPU>;
    clock-names = "cpu";
    operating-points-v2 = <&cpu0_opp_table>;
    nvmem-cells = <&part_number_otp>;
    nvmem-cell-names = "part_number";
  };
  cpu1: cpu@1 {
    compatible = "arm,cortex-a7";
    device_type = "cpu";
    reg = <1>;
    clocks = <&rcc CK_MPU>;
    clock-names = "cpu";
    operating-points-v2 = <&cpu0_opp_table>;
 };
};
```

在 cpus 节点，#address-cells 被设置成了 1，#size-cells 被设置成了 0。这是说子 reg 值是单独的 uint32，它用无大小字段表示地址。在此情况下，这两个 cpu 分配到的地址为 0 和 1。cpu 节点的#size-cells 是 0 因为每个 cpu 只分配到了一个单独的地址

要注意 reg 值需要与节点名的值相匹配。按照惯例，如果一个节点有一个 reg 属性，那么这个节点名称必须包括 unit-address,这是 reg 属性的第一个 address 值

#### Memory Mapped Devices

与在 cpu 节点中单独的 address 值不同，内存映射设备被分配了一系列将要响应的地址，因此不仅需要包含内存的基地址而且还需要映射地址的长度，因此需要使用#size-cells 用来表示在每个子 reg 元组中长度字段的大小
。
以下示例中，每个 address 值为 1 cell(32 bits),每个长度值也是 1 cell,这在 32 bit 系统是比较典型的。64 bit 设备也许会为#address-cells 和#size-cells 使用数值 2，在 device tree 中获取 64 bit addressing。

```cpp
/dts-v1/;
/ {
  #address-cells = <1>;
  #size-cells = <1>;
  // ...
  timers2: timer@40000000 {
    compatible = "st,stm32-timers";
    reg = <0x40000000 0x400>;
  };
  timers3: timer@40001000 {
    compatible = "st,stm32-timers";
    reg = <0x40001000 0x400>;
  };
  spi2: spi@4000b000 {
    compatible = "st,stm32h7-spi";
    reg = <0x4000b000 0x400>;
  };
  uart7: serial@40018000 {
    compatible = "st,stm32h7-uart";
    reg = <0x40018000 0x400>;
  };
  sai1: sai@4400a000 {
    compatible = "st,stm32h7-sai";
    reg = <0x4400a000 0x4>;
  };
  // ...
};
```

#### Non Memory Mapped Devices

处理器总线的其它设备为非内存映射设备。他们有地址范围，但不能被 CPU 直接寻址。母设备的驱动程序将代替 CPU 进行间接访问。以 i2c 设备为例，每个设备都分配了一个地址，但没有长度或范围与之相匹配。这与 CPU 地址分配很相似

```cpp
etf: etf@50092000 {
  compatible = "arm,coresight-tmc", "arm,primecell";
  reg = <0x50092000 0x1000>;
  clocks = <&rcc CK_TRACE>;
  clock-names = "apb_pclk";
  ports {
    #address-cells = <1>;
    #size-cells = <0>;
    port@0 {
      reg = <0>;
      etf_in_port: endpoint {
        slave-mode;
        remote-endpoint = <&funnel_out_port0>;
      };
    };
    port@1 {
      reg = <0>;
      etf_out_port: endpoint {
        remote-endpoint = <&tpiu_in_port>;
      };
    };
  };
};
```

#### Ranges (Address Translation)

前面已经讨论过如何向设备分配地址，但此时这些地址只是本地设备节点，还没有说明如何从那些地址里映射到 cpu 可以使用的地址。根节点经常描述地址空间的 CPU 视图。根节点的子节点已经使用了 CPU 的 address domain，所以不需要任何明确的映射。例如，serial@101f0000 设备被直接分配了地址 0x101f0000

根节点的非直接子节点是无法使用 CPU 的 address domain 的。为了在 deivce tree 获取内存映射地址必须指定如何从一个域名将地址转换到另一个。Ranges 属性就用于此目的。以下是添加了 ranges 属性的 device tree 示例

```cpp
m4_rproc: m4@0 {
  compatible = "st,stm32mp1-rproc";
  #address-cells = <1>;
  #size-cells = <1>;
  ranges = <0x00000000 0x38000000 0x10000>,
  <0x30000000 0x30000000 0x60000>,
  <0x10000000 0x10000000 0x60000>;  //ranges 是一个地址转换列表。每个输入 ranges 表格的是包含子地址的元组，母地址和子地址空间的范围大小。每个字段的大小都由获取的子地址的#address-cells 值，母地址的#address-cell 值和子地址的#size-cells 值而定。以外部总线为例，子地址是 2 cells，母地址是 1 cell,大小也为 1 cell
  resets = <&rcc MCU_R>;
  reset-names = "mcu_rst";
  st,syscfg-pdds = <&pwr 0x014 0x1>;
  st,syscfg-holdboot = <&rcc 0x10C 0x1>;
  st,syscfg-tz = <&rcc 0x000 0x1>;
  st,syscfg-rsc-tbl = <&tamp 0x144 0xFFFFFFFF>;
  status = "disabled";
  m4_system_resources {
    compatible = "rproc-srm-core";
    status = "disabled";
  };
};
```

#### status

device tree 中的 status 标识了设备的状态，使用 status 可以去禁止设备或者启用设备，看下设备树规范中的 status 可选值。

```txt
okay            表示设备正在运行
disabled        表示该设备目前尚未运行，但将来可能会运行
fail            表示设备无法运行。在设备中检测到严重错误，确实如此没有修理就不可能投入运营
fail-sss        表示设备无法运行。在设备中检测到严重错误，它是没有修理就不可能投入运营。值的
sss 部分特定于设备并指示检测到的错误情况
```

#### 中断映射

与遵循树的自然结构而进行的地址转换不同，机器上的任何设备都可以发起和终止中断信号。另外地址的编址也不同于中断信号，前者是设备树的自然表示，而后者者表现为独立于设备树结构的节点之间的链接

#### 特殊节点

aliases 节点为了解决节点路径名过长的问题，引入了节点别名的概念，可以引用到一个全路径的节点。如/external-bus/ethernet@0,0,但当用户想知道具体内容的时候显得太累赘

## BootLoader（Uboot）移植
