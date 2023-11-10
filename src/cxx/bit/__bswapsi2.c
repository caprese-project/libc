#include <internal/attribute.h>
#include <stdint.h>

__weak uint32_t __bswapsi2(uint32_t value) {
  return ((value & 0xff000000) >> 24) | ((value & 0x00ff0000) >> 8) | ((value & 0x0000ff00) << 8) | ((value & 0x000000ff) << 24);
}
