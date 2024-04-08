#include <at89x52.h>

void Timer0_Init() {
  TMOD &= 0xF0;
  TMOD |= 0x01;
  /*  TCON  */
  TF0 = 0;
  TR0 = 1;
  // 64536 + 1000 = 65536
  TL0 = 0x18;
  TH0 = 0xFC;
  /*  IE   */
  ET0 = 1;
  EA = 1;
  /*  IP   */
  PT0 = 0;
}
unsigned char Count = 0;
void Timer0_Rountine(void) __interrupt TF0_VECTOR {
  TL0 = 0x18;
  TH0 = 0xFC;
  Count++;

  if (Count > 100) {
    Count = 0;
    P2_0 = ~P2_0;
  }
}