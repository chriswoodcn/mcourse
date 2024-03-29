.equ MODER, 0x54004000  ;GPIOZ 模式寄存器基址 0x54004000
.equ OTYPER, MODER+0x04 ;GPIOZ 输出类型寄存器基址 0x54004000+偏移
.equ ODR, MODER+0x14 ;GPIOZ 输出数据寄存器基址 0x54004000+偏移
 
.text  ;声明代码段
.global _start  ;标号设为全局变量 用于链接文件使用
_start:
  ldr r0,=MODER
  mov r1,#0x0    ;r1清零
  str r1,[r0]    ;r0地址保存到r1

  ldr r0,=MODER
  mov r1,#(0x15 << 10)  ;00000000000000000101010000000000 pz5 pz6 pz7通用输出模式
  str r1,[r0]      ;r1保存到r0地址

  ldr r0,=OTYPER 
  mov r1,#0x0    ;pz5 pz6 pz7推挽模式
  str r1,[r0]    ;r1保存到r0地址

loop:            ;循环点灯
  ldr r0,=ODR
  mov r1,#(0x7 << 5)  ;0111左移5位 000000011100000 pz pz6 pz7 output 1
  str r1,[r0]         ;r1保存到r0地址
  bl delay            ;跳delay

  ldr r0,=ODR
  mov r1,#0x0         ;清零
  str r1,[r0]         ;r1保存到r0地址
  bl delay            ;跳delay

  b loop

delay:
  ldr r2,=50000000

del:
  sub r2,r2,#1
  nop
  cmp r2,#0
  bne del
  mov pc, lr

stop:
  b stop

.end