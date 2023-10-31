#include <internal/branch.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

__weak void* memmove(void* dst, const void* src, size_t n) {
  uint8_t*       d = (uint8_t*)dst;
  const uint8_t* s = (const uint8_t*)src;

  __if_likely (s < d && d < s + n) {
    s += n;
    d += n;

#ifndef __OPTIMIZE_SIZE__

    const size_t d_offset = (uintptr_t)d & (sizeof(uintptr_t) - 1);
    const size_t s_offset = (uintptr_t)s & (sizeof(uintptr_t) - 1);

    __if_likely (d_offset == s_offset) {
      __if_unlikely (d_offset != 0) {
        for (size_t i = 0; i < d_offset; ++i) {
          *--d = *--s;
        }
        n -= d_offset;
      }

      uintptr_t*       a1 = ((uintptr_t*)d) - 1;
      const uintptr_t* a2 = ((const uintptr_t*)s) - 1;
      while (n >= sizeof(uintptr_t)) {
        *a1-- = *a2--;
        n -= sizeof(uintptr_t);
      }

      d = (uint8_t*)a1;
      s = (const uint8_t*)a2;
    }

#endif // __OPTIMIZE_SIZE__

    while (n--) {
      *--d = *--s;
    }
  } else {
    memcpy(dst, src, n);
  }

  return dst;
}
