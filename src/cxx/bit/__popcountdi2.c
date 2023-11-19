#include <stdint.h>

int __popcountdi2(uint64_t value) {
  value = value - ((value >> 1) & 0x5555555555555555ull);
  value = (value & 0x3333333333333333ull) + ((value >> 2) & 0x3333333333333333ull);
  value = (value + (value >> 4)) & 0x0f0f0f0f0f0f0f0full;

  uint32_t v = (uint32_t)(value + (value >> 32));
  v          = v + (v >> 16);
  v          = (v + (v >> 8)) & 0x7f;
  return (int)v;
}
