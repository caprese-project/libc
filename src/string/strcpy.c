#include <internal/branch.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "./__has_null.h"

__weak char* strcpy(char* __restrict dst, const char* __restrict src) {
#ifdef __OPTIMIZE_SIZE__

  return (char*)memcpy(dst, src, strlen(src) + 1);

#else // ^^^ __OPTIMIZE_SIZE__ ^^^ / vvv !__OPTIMIZE_SIZE__ vvv

  uint8_t*       d = (uint8_t*)dst;
  const uint8_t* s = (const uint8_t*)src;

  const size_t dst_offset = (uintptr_t)dst & (sizeof(uintptr_t) - 1);
  const size_t src_offset = (uintptr_t)src & (sizeof(uintptr_t) - 1);
  __if_likely (dst_offset == src_offset) {
    __if_unlikely (dst_offset != 0) {
      const size_t offset = sizeof(uintptr_t) - dst_offset;
      for (size_t i = 0; i < offset; ++i) {
        __if_unlikely (s[i] == '\0') {
          return dst;
        }
        d[i] = s[i];
      }
      d += offset;
      s += offset;
    }

    uintptr_t*       a1 = (uintptr_t*)d;
    const uintptr_t* a2 = (const uintptr_t*)s;
    while (true) {
      __if_unlikely (__has_null(*a2)) {
        break;
      }
      *a1++ = *a2++;
    }

    d = (uint8_t*)a1;
    s = (const uint8_t*)a2;
  }

  while (true) {
    __if_unlikely (*s == '\0') {
      break;
    }
    *d++ = *s++;
  }

  return dst;

#endif // __OPTIMIZE_SIZE__
}
