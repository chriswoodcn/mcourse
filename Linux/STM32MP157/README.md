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

### stm32mp157a 实操

1. 导入源码

基于 en.SOURCES-stm32mp1-openstlinux-5-4-dunfell-mp1-20-06-24.tar.xz 官方源码，解压后进入 u-boot 源码，安装 readme 打补丁 `` for p in `ls -1 ../*.patch\\`; do patch -p1 < $p; done ``

2. 基于 TF 卡，TF 卡分区

```shell
umount /dev/sdb1
sudo parted -s /dev/sdb mklabel msdos
sudo sgdisk --resize-table=128 -a 1 -n 1:34:545 -c 1:fsbl1 -n 2:546:1057 -c 2:fsbl2 -n \
3:1058:5153 -c 3:ssbl -n 4:5154:136225 -c 4:bootfs -n 5:136226 -c 5:rootfs -A 4:set:2 -p /dev/sdb -g
# 看到 the operation has complete successfully成功
```

3. 建立自己的平台

```shell
# SDK交叉编译工具配置好
# 增加板级相关文件 主要是使用stm官方的通用设备树文件 配自己的设备树
cp configs/stm32mp15_basic_defconfig configs/stm32mp15_fsmp1a_basic_defconfig
cp arch/arm/dts/stm32mp15xx-dkx.dtsi arch/arm/dts/stm32mp15xx-fsmp1x.dtsi
cp arch/arm/dts/stm32mp157a-dk1.dts arch/arm/dts/stm32mp157a-fsmp1a.dts
cp arch/arm/dts/stm32mp157a-dk1-u-boot.dtsi arch/arm/dts/stm32mp157a-fsmp1a-u-boot.dtsi
# 修改arch/arm/dts/stm32mp157a-fsmp1a.dts
# #include "stm32mp15xx-fsmp1x.dtsi" >>> #include "stm32mp15xx-dkx.dtsi"
# 配置 u-boot
make ARCH=arm stm32mp15_fsmp1a_basic_defconfig
# 编译 u-boot
make ARCH=arm CROSS_COMPILE=arm-fsmp1x-linux-gnueabihf- DEVICE_TREE=stm32mp157a-fsmp1a all
# 固件烧写
sudo dd if=u-boot-spl.stm32 of=/dev/sdb1 conv=fdatasync
sudo dd if=u-boot-spl.stm32 of=/dev/sdb2 conv=fdatasync
sudo dd if=u-boot.img of=/dev/sdb3 conv=fdatasync
# 以tf卡启动开发板
```

生成 Trusted 镜像

```shell
# 1.建立基础的 Trusted 配置文件
cp configs/stm32mp15_trusted_defconfig configs/stm32mp15_fsmp1a_trusted_defconfig
make ARCH=arm stm32mp15_fsmp1a_trusted_defconfig
# 2. 去掉 PMIC 的配置选项，去掉 ADC 功能,按空格将方括号内*号去掉
make ARCH=arm menuconfig
# 去掉 PMIC
# Device Drivers --->
#     Power --->
#         [ ] Enable support for STMicroelectronics STPMIC1 PMIC
# 去掉 ADC 功能
# Command line interface --->
#     Device access commands --->
#         [ ] adc - Access Analog to Digital Converters info and data
#     Device Drivers --->
#         [ ] Enable ADC drivers using Driver Model
# 添加 MAE0621A 驱动
# Device Drivers --->
#     -*- Ethernet PHY (physical media interface) support --->
#     [*] Realtek Ethernet PHYs support
#     [*] supports the Maxio MAEXXXX PHY
# 3. 修改配置文件
cp .config configs/stm32mp15_fsmp1a_trusted_defconfig
# 4. 修改上层目录下的 Makefile.sdk 编译脚本在 UBOOT_CONFIGS 配置项中添加stm32mp15_fsmp1a_trusted_defconfig,trusted,u-boot.stm32在 DEVICE_TREE 配置项中添加stm32mp157a-fsmp1a
UBOOT_CONFIGS ?= stm32mp15_fsmp1a_trusted_defconfig,trusted,u-boot.stm32 stm32mp15_trusted_defconfig,trusted,u-boot.stm32 stm32mp15_trusted_defconfig,optee,u-boot.stm32 stm32mp15_basic_defconfig,basic,u-boot.img
DEVICE_TREE ?= stm32mp157a-fsmp1a stm32mp157a-dk1 stm32mp157d-dk1 stm32mp157c-dk2 stm32mp157f-dk2 stm32mp157c-ed1 stm32mp157f-ed1 stm32mp157a-ev1 stm32mp157c-ev1 stm32mp157d-ev1 stm32mp157f-ev1
# 5. 编译 trusted 镜像
make distclean
make ARCH=arm CROSS_COMPILE=arm-fsmp1x-linux-gnueabihf- -f $PWD/../Makefile.sdk all UBOOT_CONFIGS=stm32mp15_fsmp1a_trusted_defconfig,trusted,u-boot.stm32
# 编译完成后生成的镜像文件在上级目录下的 build-trusted 文件夹中有一个u-boot-stm32mp157a-fsmp1a-trusted.stm32
```

4. 调整设备树电源配置
   由于官方参考板 DK1 采用电源管理芯片做电源管理，而 FS-MP1A 采用分离电路作为电源管理，需要将文件中原有电源管理芯片相关内容去掉，增加上固定电源

- 去掉原有电源管理内容
  DK1 参考板电源管理芯片挂在 I2C4 上，而 FS-MP1A 并未使用 I2C4 总线，所以直接将 I2C4 相关内容完全删除即可；由于 DK1 I2C4 总线上有个 USB type C 的控制器，删除 I2C4 节点的同时将 type C 控制器的描述删除，所以需要将引用 type C 控制器的内容删掉

```cpp
// stm32mp15xx-fsmp1x.dtsi 文件 &i2c4节点相关内容整体删除
&i2c4 {
  // ...
}
// stm32mp15xx-fsmp1x.dtsi 文件，删除如下内容
&cpu0{
  cpu-supply = <&vddcore>;
};
&cpu1{
  cpu-supply = <&vddcore>;
};
// stm32mp157a-fsmp1a-u-boot.dtsi文件 删除如下
&pmic {
  u-boot,dm-pre-reloc;
};
// stm32mp15xx-fsmp1x.dtsi 文件  删除port部分
&usbotg_hs {
  phys = <&usbphyc_port1 0>;
  phy-names = "usb2-phy";
  usb-role-switch;
  status = "okay";
  port {
    usbotg_hs_ep: endpoint {
      remote-endpoint = <&con_usbotg_hs_ep>;
    };
  };
};


// 添加固定电源配置
// stm32mp15xx-fsmp1x.dtsi 文件 固定电源配置通常添加在根节点下，在根节点末尾位置添加如下内容
v3v3: regulator-3p3v {
  compatible = "regulator-fixed";
  regulator-name = "v3v3";
  regulator-min-microvolt = <3300000>;
  regulator-max-microvolt = <3300000>;
  regulator-always-on;
  regulator-boot-on;
};
v1v8_audio: regulator-v1v8-audio {
  compatible = "regulator-fixed";
  regulator-name = "v1v8_audio";
  regulator-min-microvolt = <1800000>;
  regulator-max-microvolt = <1800000>;
  regulator-always-on;
  regulator-boot-on;
};
v3v3_hdmi: regulator-v3v3-hdmi {
  compatible = "regulator-fixed";
  regulator-name = "v3v3_hdmi";
  regulator-min-microvolt = <3300000>;
  regulator-max-microvolt = <3300000>;
  regulator-always-on;
  regulator-boot-on;
};
v1v2_hdmi: regulator-v1v2-hdmi {
  compatible = "regulator-fixed";
  regulator-name = "v1v2_hdmi";
  regulator-min-microvolt = <1200000>;
  regulator-max-microvolt = <1200000>;
  regulator-always-on;
  regulator-boot-on;
};
vdd: regulator-vdd {
  compatible = "regulator-fixed";
  regulator-name = "vdd";
  regulator-min-microvolt = <3300000>;
  regulator-max-microvolt = <3300000>;
  regulator-always-on;
  regulator-boot-on;
};
vdd_usb: regulator-vdd-usb {
  compatible = "regulator-fixed";
  regulator-name = "vdd_usb";
  regulator-min-microvolt = <3300000>;
  regulator-max-microvolt = <3300000>;
  regulator-always-on;
  regulator-boot-on;
};
```

5. emmc 移植

eMMC 使用的是 SDMMC2 总线，当前所使用的设备树文件中没有 SDMMC2 的支持，所以需要增加相关内容才能正常驱动 eMMC

```
根据原理图确认后管脚对应关系
原理图网络编号          对应管脚          管脚功能             管脚功能码
SD2_DATA0               PB14             SDMMC2_D0             AF9
SD2_DATA1               PB15             SDMMC2_D1             AF9
SD2_DATA2               PB3              SDMMC2_D2             AF9
SD2_DATA3               PB4              SDMMC2_D3             AF9
SD2_DATA4               PA8              SDMMC2_D4             AF9
SD2_DATA5               PA9              SDMMC2_D5             AF10
SD2_DATA6               PE5              SDMMC2_D6             AF9
SD2_DATA7               PD3              SDMMC2_D7             AF9
SD2_CLK                 PE3              SDMMC2_CK             AF9
SD2_CMD                 PG6              SDMMC2_CMD            AF10

u-boot 中 STM32MP1 默认管脚定义在文件 fdts/stm32mp15-pinctrl.dtsi 中,查看后确认有 SDMMC2 的管脚定义，且与 FS-MP1A 硬件使用情况一致，定义如下
sdmmc2_b4_pins_a: sdmmc2-b4-0 {
    pins1 {
        pinmux = <STM32_PINMUX('B', 14, AF9)>, /* SDMMC2_D0 */
        <STM32_PINMUX('B', 15, AF9)>, /* SDMMC2_D1 */
        <STM32_PINMUX('B', 3, AF9)>, /* SDMMC2_D2 */
        <STM32_PINMUX('B', 4, AF9)>, /* SDMMC2_D3 */
        <STM32_PINMUX('G', 6, AF10)>; /* SDMMC2_CMD */
        slew-rate = <1>;
        drive-push-pull;
        bias-pull-up;
    };
    pins2 {
        pinmux = <STM32_PINMUX('E', 3, AF9)>; /* SDMMC2_CK */
        slew-rate = <2>;
        drive-push-pull;
        bias-pull-up;
    };
};
```

修改 fdts/stm32mp15xx-fsmp1x.dtsi 增加 SDMMC2 的信息,在原有 sdmmc1 节点下增加 sdmmc2 的内容

```cpp
&sdmmc2 {
    pinctrl-names = "default";
    pinctrl-0 = <&sdmmc2_b4_pins_a &sdmmc2_d47_pins_a>;
    non-removable;
    st,neg-edge;
    bus-width = <8>;
    vmmc-supply = <&v3v3>;
    vqmmc-supply = <&v3v3>;
    status = "okay";
};
```

重新编译烧写后可以通过 ums 或者 scp 的方式更新 eMMC 中的 u-boot 即可

## Trusted Firmware-A 移植

### stm32mp157a 实操

1. 导入源码

基于 en.SOURCES-stm32mp1-openstlinux-5-4-dunfell-mp1-20-06-24.tar.xz 官方源码，解压后进入 tf-a-stm32mp-2.2.r1-r0 源码，安装 readme 打补丁 `` for p in `ls -1 ../*.patch`; do patch -p1 < $p; done ``

2. 基于 TF 卡，TF 卡分区，操作同 BootLoader（Uboot）移植

3. 建立自己的平台

```shell
# SDK交叉编译工具配置好
# 增加板级相关文件 进入到 tf-a 源码目录
cp fdts/stm32mp15xx-dkx.dtsi fdts/stm32mp15xx-fsmp1x.dtsi
cp fdts/stm32mp157a-dk1.dts fdts/stm32mp157a-fsmp1a.dts
# 修改上层目录下的 Makefile.sdk 编译脚本在 TFA_DEVICETREE 配置项中添加 stm32mp157a-fsmp1a
TFA_DEVICETREE ?= stm32mp157a-fsmp1a stm32mp157a-dk1 stm32mp157d-dk1 stm32mp157c-dk2 stm32mp157f-dk2 stm32mp157c-ed1 stm32mp157f-ed1 stm32mp157a-ev1 stm32mp157c-ev1 stm32mp157d-ev1 stm32mp157f-ev1
# 修改上层目录下的 Makefile.sdk 的编译器
EXTRA_OEMAKE=CROSS_COMPILE=arm-fsmp1x-linux-gnueabihf- DEBUG=1 LOG_LEVEL=40 PLAT=stm32mp1 ARCH=aarch32 ARM_ARCH_MAJOR=7 STM32MP_SDMMC=1 STM32MP_EMMC=1 STM32MP_SPI_NOR=1 STM32MP_RAW_NAND=1 STM32MP_SPI_NAND=1
# 修改 fdts/stm32mp157a-fsmp1a.dts
# #include "stm32mp15xx-fsmp1x.dtsi" >>> #include "stm32mp15xx-dkx.dtsi"
# 编译源码
make -f $PWD/../Makefile.sdk TFA_DEVICETREE=stm32mp157a-fsmp1a TF_A_CONFIG=trusted ELF_DEBUG_ENABLE='1' all
# 固件烧写
sudo dd if=tf-a-stm32mp157a-fsmp1a-trusted.stm32 of=/dev/sdb1
sudo dd if=tf-a-stm32mp157a-fsmp1a-trusted.stm32 of=/dev/sdb2
sudo dd if=u-boot-stm32mp157a-fsmp1a-trusted.stm32 of=/dev/sdb3 #此处u-boot-stm32mp157a-fsmp1a-trusted.stm32需要在u-boot移植中生成
# 以tf卡启动开发板
```

4. 调整设备树电源配置，操作同 BootLoader（Uboot）移植

5. emmc 移植，操作同 BootLoader（Uboot）移植

## Linux 内核目录

初次接触 Linux 内核，最好仔细阅读顶层目录的 readme 文件，它是 Linux 内核的概述和编译命令说明。readme 的说明更加针对 X86 等通用的平台，对于某些特殊的体系结构，可能有些特殊的地方

此处以 linux 5.4.31 为例来介绍 linux 内核目录结构

```md
# 第一级目录

## arch

包含各体系结构特定的代码，如 arm、x86、ia64、mips 等，在每个体系结构目录下通常都有：
(1) /boot：内核需要的 特定平台代码。
(2) /kernel：体系结构特有的代码。
(3) /lib：通用函数在特定体系结构的实现。
(4) /math-emu：模拟 FPU 的代码。
(5) /mm：特定体系结构的内存管理实现。
(6) /include：特定体系的头文件 。

## block

存放块设备相关代码

## crpyto

存放加密、压缩、CRC 校验等算法相关代码

## Documentation

存放相关说明文档，很多实用文档，包括驱动编写等

## drivers

存放 Linux 内核设备驱动程序源码。驱动源码在 Linux 内核源码中站了很大比例，常见外设几乎都有可参考源码，对驱动
开发而言，该目录非常重要。该目录包含众多驱动，目录按照 设备类别 进行分类，如 char、block、input、i2c、
spi、pci、usb 等

## firmware

存放处理器相关的一些特殊固件

## fs

存放所有文件系统代码，如 fat、ext2、ext3、ext4、ubifs、nfs、sysfs 等

## include

存放内核所需、与平台无关的头文件，与平台相关的头文件已经被移动到 arch 平台的 include 目录，如 ARM 的头文件目录<arch/arm/include/asm/>

## init

包含内核初始化代码

## ipc

存放进程间通信代码

## kernel

包含 Linux 内核管理代码

## lib

库文件代码实现

## mm

存放内存管理代码

## net

存放网络相关代码

## samples

存放提供的一些内核编程范例，如 kfifo；相关用户态编程范例，如 hidraw。

## scripts

存放一些脚本文件，如 menuconfig 脚本

## security

存放系统安全性相关代码

## sound

存放声音、声卡相关驱动

## tools

编译过程中一些主机必要工具

## usr

cpio 相关实现

## virt

内核虚拟机 KVM
```

## Linux 内核配置及编译

### 解压内核

```shell
# 1.解压内核
tar -xvf en.SOURCES-stm32mp1-openstlinux-5-4-dunfell-mp1-20-06-24.tar.xz
cd ~/FS-MP1A/stm32mp1-openstlinux-5.4-dunfell-mp1-20-06-24/sources/arm-ostl-linux-gnueabi/linux-stm32mp-5.4.31-r0
tar -xvf linux-5.4.31.tar.xz
cd linux-5.4.31
```

### 添加 STMicroelectronics 官方补丁

将上层目录下所有的 patch 补丁文件应用到当前的内核中

```shell
for p in `ls -1 ../*.patch`; do patch -p1 < $p; done
```

### 生成标准板配置文件

```shell
# 生成 multi_v7_defconfig 默认配置
make ARCH=arm multi_v7_defconfig "fragment*.config"
# 在默认 multi_v7_defconfig 配置中加入 ST 官方提供的 fragment config
for f in `ls -1 ../fragment*.config`; do scripts/kconfig/merge_config.sh -m -r .config $f; done
yes '' | make ARCH=arm oldconfig
# 生成自己的默认配置文件
cp .config arch/arm/configs/stm32_fsmp1a_defconfig
# 取消 git 中的 SHA1
echo "" > .scmversion
```

### 配置内核

准备好交叉编译工具链；如果需要编译额外的功能或者驱动，可以使用 meunconfig 来对内核进行配置

```shell
make ARCH=arm menuconfig
```

### 编译内核

```shell
make -j4 ARCH=arm CROSS_COMPILE=arm-fsmp1x-linux-gnueabihf- uImage vmlinux LOADADDR=0xC2000040
```

编译后在内核源码目录下，能够在生成一个 vmlinux 文件，该文件是没有经过压缩的内核镜像，这个镜像导出了所有的内核符号可以用作仿真调试;此外在 arch/arm/boot 目录下还生成了一个 uImage 文件，这就是经过压缩的内核镜像。可以用作系统启动

### 编译内核模块

将内核中配置为模块的源码进行编译，最终得到 ko 文件;即 menuconfig 可视化配置界面中被标记为 m 的模块

```shell
make ARCH=arm CROSS_COMPILE=arm-fsmp1x-linux-gnueabihf- modules
```

### 生成设备树

以参考板 DK1 设备树文件 stm32mp15xx-dkx.dtsi 和 stm32mp157a-dk1.dts 为参考，增加 stm32mp15xx-fsmp1x.dtsi 和 stm32mp157a-fsmp1a.dts；对 stm32mp15xx-fsmp1x.dtsi 内容进行整理，去掉没有被使用的节点信息和明显与 FS-MP1A 的硬件没
有关系的节点信息；整理出一个相对简单的设备树文件，确保内核可以正常启动。后续各个外设移植时会陆续增加文件的相关内容

```
在 arch/arm/boot/dts/ 目录下新建stm32mp15xx-fsmp1x.dtsi
...
在 arch/arm/boot/dts/ 目录下新建stm32mp157a-fsmp1a.dts
...

修改 arch/arm/boot/dts/Makefile
添加 stm32mp157a-fsmp1a.dts 的编译选项
dtb-$(CONFIG_ARCH_STM32) += \
...
stm32mp157a-fsmp1a.dtb \
...

重新编译设备树文件
make ARCH=arm CROSS_COMPILE=arm-fsmp1x-linux-gnueabihf- dtbs

编译完成后会在 arch/arm/boot/dts/目录下生成 stm32mp157a-fsmp1a.dtb 文件

cp arch/arm/boot/uImage /tftpboot/
cp arch/arm/boot/dts/stm32mp157a-fsmp1a.dtb /tftpboot/
```

### 配置 tftp

使用网线直连方式，需要将网线的一端接到电脑的网口上面，一端接到开发板的网口上面;

1. 在虚拟机中设置静态 IP 地址，这里设置为 192.168.11.78

```
vi /etc/network/interfaces

auto ens33
iface ens33 inet static
  address 192.168.11.78
  netmask 255.255.255.0
  gateway 192.168.11.1
  dns-nameserver 192.168.11.1
```

2. 将 VMware 网卡桥接到有线网卡
3. 进入 uboot 模式下，设置开发板环境变量;设置 ipaddr,ipaddr 的设置需要和虚拟机的 ip 地址在同一网段

```
env set ipaddr 192.168.11.77
env set serverip 192.168.11.78
env save
```

4. 在 tftp 服务器工作目录中（/tftpboot）建立 pxelinux.cfg 文件夹。

该文件夹下建立 01-00-80-e1-42-60-17 文件;00-80-e1-42-60-17 为开发板的默认 mac 地址，可以使用 env set -f ethaddr xx:xx:xx:xx:xx:xx 来修改 mac 地址

文件内容

```
menu title Select the boot mode
timeout 20
default stm32mp157a-fsmp1a-buildroot
label stm32mp157a-fsmp1a-buildroot
  kernel /uImage
  devicetree /stm32mp157a-fsmp1a.dtb
  append root=PARTUUID=c12a7328-f81f-11d2-ba4b-00a0c93ec93b rootwait rw
```

## Linux 内核 eMMC 驱动移植

## Linux 内核网卡驱动移植

## Linux HDMI 驱动移植

## Linux 内核 MIPI LCD 驱动移植

## Linux 内核 5 寸触摸屏驱动移植

## Linux 内核 RGB LCD 驱动移植

## Linux 内核 7 寸触摸屏驱动移植

## Linux 内核音频驱动移植

## Linux 内核摄像头驱动移植

## Linux 内核蓝牙驱动移植

## Linux 内核 Wi-Fi 驱动移植

## Linux 根文件系统制作（buildroot）

## Linux 根文件系统制作（busybox）

## 修改默认启动选项

## 扩展板驱动移植准备

## 扩展板 LED 灯驱动移植

## 扩展板蜂鸣器驱动移植

## 扩展板风扇驱动移植

## 扩展板振动马达驱动移植

## 扩展板空气温湿度传感器驱动移植

## 扩展板环境光/接近/红外传感器驱动移植

## 扩展板心率/血氧传感器驱动移植

## 扩展板 ADC 驱动移植

## 扩展板数码管驱动移植

## 扩展板 RS485 总线驱动移植

## 扩展板 CAN 总线驱动移植
