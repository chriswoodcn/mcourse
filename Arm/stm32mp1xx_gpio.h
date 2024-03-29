#ifndef __STM32MP1xx_GPIO_H__
#define __STM32MP1xx_GPIO_H__

typedef struct {
  volatile unsigned int MODER;   // 0x00
  volatile unsigned int OTYPER;  // 0x04
  volatile unsigned int OSPEEDR; // 0x08
  volatile unsigned int PUPDR;   // 0x0C
  volatile unsigned int IDR;     // 0x10
  volatile unsigned int ODR;     // 0x14
  volatile unsigned int BSRR;    // 0x18
  volatile unsigned int LCKR;    // 0x1C
  volatile unsigned int AFRL;    // 0x20
  volatile unsigned int AFRH;    // 0x24
  volatile unsigned int BRR;     // 0x28
  volatile unsigned int res;
  volatile unsigned int SECCFGR; // 0x30

} gpio_t;

#define GPIOA ((volatile gpio_t *)0x50002000)
#define GPIOB ((volatile gpio_t *)0x50003000)
#define GPIOC ((volatile gpio_t *)0x50004000)
#define GPIOD ((volatile gpio_t *)0x50005000)
#define GPIOE ((volatile gpio_t *)0x50006000)
#define GPIOF ((volatile gpio_t *)0x50007000)
#define GPIOG ((volatile gpio_t *)0x50008000)
#define GPIOH ((volatile gpio_t *)0x50009000)
#define GPIOI ((volatile gpio_t *)0x5000A000)
#define GPIOJ ((volatile gpio_t *)0x5000B000)
#define GPIOK ((volatile gpio_t *)0x5000C000)
#define GPIOZ ((volatile gpio_t *)0x54004000)

#endif // __STM32MP1xx_GPIO_H__
