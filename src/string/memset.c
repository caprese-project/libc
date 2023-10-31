#include <internal/bit.h>
#include <internal/branch.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

__weak void* memset(void* s, int ch, size_t n) {
  uint8_t* p = s;

#ifndef __OPTIMIZE_SIZE__

  size_t s_offset = (uintptr_t)s & (sizeof(uintptr_t) - 1);
  __if_unlikely (s_offset != 0) {
    const size_t offset = sizeof(uintptr_t) - s_offset;
    for (size_t i = 0; i < offset; ++i) {
      p[i] = (uint8_t)ch;
    }
    p += offset;
    n -= offset;
  }

  uintptr_t v = (uint8_t)ch;
  for (size_t i = 0, l = __countr_zerosz(sizeof(uintptr_t)); i < l; ++i) {
    v |= v << (8 << i);
  }

  uintptr_t* a = (uintptr_t*)p;
  for (size_t i = 0; i < n / sizeof(uintptr_t); ++i) {
    a[i] = v;
  }

  const size_t rem = n % sizeof(uintptr_t);
  p += n - rem;
  n = rem;

#endif // __OPTIMIZE_SIZE__

  while (n--) {
    *p++ = (uint8_t)ch;
  }

  return s;
}
