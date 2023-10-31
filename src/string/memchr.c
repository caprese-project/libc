#include <internal/bit.h>
#include <internal/branch.h>
#include <internal/unreachable.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "./__has_null.h"

__weak void* memchr(const void* s, int ch, size_t n) {
  const uint8_t* p = (const uint8_t*)s;

#ifndef __OPTIMIZE_SIZE__

  const size_t s_offset = (uintptr_t)s & (sizeof(uintptr_t) - 1);

  __if_likely (n >= sizeof(uintptr_t)) {
    __if_unlikely (s_offset != 0) {
      const size_t offset = sizeof(uintptr_t) - s_offset;
      for (size_t i = 0; i < offset; ++i) {
        __if_unlikely (p[i] == (uint8_t)ch) {
          return (void*)&p[i];
        }
      }
      p += offset;
      n -= offset;
    }

    uintptr_t mask = (uint8_t)ch;
    for (size_t i = 0, l = __countr_zerosz(sizeof(uintptr_t)); i < l; ++i) {
      mask |= mask << (8 << i);
    }

    const uintptr_t* a = (const uintptr_t*)p;
    for (size_t i = 0; i < n / sizeof(uintptr_t); ++i) {
      __if_unlikely (__has_null(a[i] ^ mask)) {
        p = (const uint8_t*)&a[i];
        for (size_t j = 0; j < sizeof(uintptr_t); ++j) {
          __if_unlikely (p[j] == (uint8_t)ch) {
            return (void*)&p[j];
          }
        }
        __unreachable();
      }
    }

    const size_t rem = n % sizeof(uintptr_t);
    p += n - rem;
    n = rem;
  }

#endif // __OPTIMIZE_SIZE__

  for (size_t i = 0; i < n; ++i) {
    __if_unlikely (p[i] == (uint8_t)ch) {
      return (void*)&p[i];
    }
  }

  return NULL;
}
