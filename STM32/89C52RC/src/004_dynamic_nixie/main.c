#include "NiXie/Nixie.h"

int main(void) {
  unsigned char i = 1;
  while (1) {
    if (i == 9)
      i = 1;
    Nixie(i, i, 1000);
    i++;
  }
}