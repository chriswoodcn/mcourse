#include "Delay/Delay.h"
#include "STC89xx.h"

unsigned char a = 0;
void main(void) {
  while (1) {
    if (P10 == 0) {
      if (a == 0xFF)
        a = 0;
      Delay(10);
      while (P10 == 0)
        ;
      Delay(10);
      a++;
      P2 = ~a;
    }
  }
}