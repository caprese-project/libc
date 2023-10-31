#include <internal/branch.h>
#include <string.h>

#include "./__has_null.h"

__weak int strcmp(const char* s1, const char* s2) {
#ifndef __OPTIMIZE_SIZE__

  const size_t s1_offset = (uintptr_t)s1 & (sizeof(uintptr_t) - 1);
  const size_t s2_offset = (uintptr_t)s2 & (sizeof(uintptr_t) - 1);

  __if_likely (s1_offset == s2_offset) {
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
    }

    const uintptr_t* a1 = (const uintptr_t*)s1;
    const uintptr_t* a2 = (const uintptr_t*)s2;
    while (*a1 == *a2) {
      __if_unlikely (__has_null(*a1)) {
        return 0;
      }
      ++a1;
      ++a2;
    }

    s1 = (const char*)a1;
    s2 = (const char*)a2;
  }

#endif // __OPTIMIZE_SIZE__

  while (*s1 == *s2) {
    __if_unlikely (*s1 == '\0') {
      return 0;
    }
    ++s1;
    ++s2;
  }

  return (int)(uint8_t)*s1 - (int)(uint8_t)*s2;
}
