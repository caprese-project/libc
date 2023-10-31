#include <internal/branch.h>
#include <internal/unreachable.h>
#include <string.h>

#include "./__has_null.h"

__weak int strncmp(const char* s1, const char* s2, size_t n) {
#ifndef __OPTIMIZE_SIZE__

  const size_t s1_offset = (uintptr_t)s1 & (sizeof(uintptr_t) - 1);
  const size_t s2_offset = (uintptr_t)s2 & (sizeof(uintptr_t) - 1);

  __if_likely (n >= sizeof(uintptr_t) && s1_offset == s2_offset) {
    __if_unlikely (s1_offset != 0) {
      const size_t offset = sizeof(uintptr_t) - s1_offset;
      for (size_t i = 0; i < offset; ++i) {
        __if_unlikely (s1[i] != s2[i]) {
          return (int)(uint8_t)s1[i] - (int)(uint8_t)s2[i];
        } else __if_unlikely (s1[i] == '\0') {
          return 0;
        }
      }
      s1 += offset;
      s2 += offset;
      n -= offset;
    }

    const uintptr_t* a1 = (const uintptr_t*)s1;
    const uintptr_t* a2 = (const uintptr_t*)s2;
    for (size_t i = 0; i < n / sizeof(uintptr_t); ++i) {
      __if_unlikely (a1[i] != a2[i] || __has_null(a1[i]) || __has_null(a2[i])) {
        s1 = (const char*)&a1[i];
        s2 = (const char*)&a2[i];
        for (size_t j = 0; j < sizeof(uintptr_t); ++j) {
          __if_unlikely (s1[j] != s2[j]) {
            return (int)(uint8_t)s1[j] - (int)(uint8_t)s2[j];
          } else __if_unlikely (s1[j] == '\0') {
            return 0;
          }
        }
        __unreachable();
      }
    }

    const size_t rem = n % sizeof(uintptr_t);
    s1 += n - rem;
    s2 += n - rem;
    n = rem;
  }

#endif // __OPTIMIZE_SIZE__

  for (size_t i = 0; i < n; ++i) {
    __if_unlikely (s1[i] != s2[i]) {
      return (int)(uint8_t)s1[i] - (int)(uint8_t)s2[i];
    } else __if_unlikely (s1[i] == '\0') {
      return 0;
    }
  }

  return 0;
}
