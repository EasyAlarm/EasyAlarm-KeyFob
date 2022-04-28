#include "reset.h"
void reset()
{
  asm volatile (" jmp 0");
}