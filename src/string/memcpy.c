#include <internal/branch.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

__weak void* memcpy(void* __restrict dst, const void* __restrict src, size_t n) {
  uint8_t*       d = (uint8_t*)dst;
  const uint8_t* s = (const uint8_t*)src;

#ifndef __OPTIMIZE_SIZE__

  const size_t dst_offset = (uintptr_t)dst & (sizeof(uintptr_t) - 1);
  const size_t src_offset = (uintptr_t)src & (sizeof(uintptr_t) - 1);

  __if_likely (n >= sizeof(uintptr_t) && dst_offset == src_offset) {
    __if_unlikely (dst_offset != 0) {
      const size_t offset = sizeof(uintptr_t) - dst_offset;
      for (size_t i = 0; i < offset; ++i) {
        d[i] = s[i];
      }
      d += offset;
      s += offset;
      n -= offset;
    }

    uintptr_t*       a1 = (uintptr_t*)d;
    const uintptr_t* a2 = (const uintptr_t*)s;
    for (size_t i = 0; i < n / sizeof(uintptr_t); ++i) {
      a1[i] = a2[i];
    }

    const size_t rem = n % sizeof(uintptr_t);
    d += n - rem;
    s += n - rem;
    n = rem;
  }

#endif // __OPTIMIZE_SIZE__

  for (size_t i = 0; i < n; ++i) {
    d[i] = s[i];
  }

  return dst;
}
