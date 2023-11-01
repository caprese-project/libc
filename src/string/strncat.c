#include <internal/attribute.h>
#include <internal/branch.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "./__has_null.h"

__weak char* strncat(char* __restrict dst, const char* __restrict src, size_t n) {
  uint8_t*       d = (uint8_t*)dst + strlen(dst);
  const uint8_t* s = (const uint8_t*)src;

#ifndef __OPTIMIZE_SIZE__

  size_t d_offset = (uintptr_t)d & (sizeof(uintptr_t) - 1);
  size_t s_offset = (uintptr_t)s & (sizeof(uintptr_t) - 1);
  __if_likely (((d_offset + s_offset) & (sizeof(uintptr_t) - 1)) == 0 && s_offset <= n) {
    __if_unlikely (d_offset != 0) {
      const size_t offset = sizeof(uintptr_t) - d_offset;
      for (size_t i = 0; i < offset; ++i) {
        d[i] = s[i];
        __if_unlikely (s[i] == '\0') {
          return dst;
        }
      }
      d += offset;
      s += offset;
      n -= offset;
    }

    uintptr_t*       a1 = (uintptr_t*)d;
    const uintptr_t* a2 = (const uintptr_t*)s;
    while (n >= sizeof(uintptr_t)) {
      __if_unlikely (__has_null(*a2)) {
        break;
      }
      *a1++ = *a2++;
      --n;
    }

    d = (uint8_t*)a1;
    s = (const uint8_t*)a2;
  }

#endif // __OPTIMIZE_SIZE__

  for (size_t i = 0; i < n; ++i) {
    __if_unlikely (s[i] == '\0') {
      break;
    }
    d[i] = s[i];
  }

  d[n] = '\0';

  return dst;
}
