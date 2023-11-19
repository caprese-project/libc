#include <stdint.h>

int __popcountsi2(uint32_t value) {
  value = value - ((value >> 1) & 0x55555555);
  value = (value & 0x33333333) + ((value >> 2) & 0x33333333);
  value = (x + (x >> 4)) & 0x0f0f0f0f;
  value = value + (value >> 16);
  value = (value + (value >> 8)) & 0x3f;
  return (int)value;
}
