#include <Timer0.h>
#include <at89x52.h>
/**
 * 单片机内部资源 软件计时 替代长时间delay
 * 3个定时器 t0 t1与传统51兼容 t2为52新增资源
 *
 * 时钟 -- 计数 -- 中断
 *
 * 定时器/计数器相关寄存器
 * TCON 定时器控制寄存器
 * TMOD 定时器模式寄存器
 * TL0 timer low 0
 * TL1 timer low 1
 * TH0 timer high 0
 * TH1 timer high 1
 * 中断相关寄存器
 * IE
 * IP
 * IPH
 * TCON
 * SCON
 * T2CON
 * XICON
 */
void main() {
  Timer0_Init();
  P2 = 0xfe;
  while (1) {
  }
}
