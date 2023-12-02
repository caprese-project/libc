#include <internal/attribute.h>
#include <stdint.h>

__weak int __ctzdi2(uint64_t value) {
  if (value == 0) return 64;

  int count = 0;

  while ((value & 1) == 0) {
    value >>= 1;
    count++;
  }

  return count;
}
