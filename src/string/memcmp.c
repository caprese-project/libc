#include <internal/branch.h>
#include <internal/unreachable.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

__weak int memcmp(const void* s1, const void* s2, size_t n) {
  const uint8_t* p1 = (const uint8_t*)s1;
  const uint8_t* p2 = (const uint8_t*)s2;

#ifndef __OPTIMIZE_SIZE__

  const size_t s1_offset = (uintptr_t)s1 & (sizeof(uintptr_t) - 1);
  const size_t s2_offset = (uintptr_t)s2 & (sizeof(uintptr_t) - 1);

  __if_likely (n >= sizeof(uintptr_t) && s1_offset == s2_offset) {
    __if_unlikely (s1_offset != 0) {
      const size_t offset = sizeof(uintptr_t) - s1_offset;
      for (size_t i = 0; i < offset; ++i) {
        __if_unlikely (p1[i] != p2[i]) {
          return (int)p1[i] - (int)p2[i];
        }
      }
      p1 += offset;
      p2 += offset;
      n -= offset;
    }

    const uintptr_t* a1 = (const uintptr_t*)p1;
    const uintptr_t* a2 = (const uintptr_t*)p2;
    for (size_t i = 0; i < n / sizeof(uintptr_t); ++i) {
      __if_unlikely (a1[i] != a2[i]) {
        p1 = (const uint8_t*)&a1[i];
        p2 = (const uint8_t*)&a2[i];
        for (size_t j = 0; j < sizeof(uintptr_t); ++j) {
          __if_unlikely (p1[j] != p2[j]) {
            return (int)p1[j] - (int)p2[j];
          }
        }
        __unreachable();
      }
    }

    const size_t rem = n % sizeof(uintptr_t);
    p1 += n - rem;
    p2 += n - rem;
    n = rem;
  }

#endif // __OPTIMIZE_SIZE__

  for (size_t i = 0; i < n; ++i) {
    __if_unlikely (p1[i] != p2[i]) {
      return (int)p1[i] - (int)p2[i];
    }
  }

  return 0;
}
