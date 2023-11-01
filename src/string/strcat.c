#include <internal/attribute.h>
#include <internal/branch.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "./__has_null.h"

__weak char* strcat(char* __restrict dst, const char* __restrict src) {
#ifdef __OPTIMIZE_SIZE__

  return strncat(dst, src, strlen(src));

#else // ^^^ __OPTIMIZE_SIZE__ ^^^ / vvv !__OPTIMIZE_SIZE__ vvv

  uint8_t*       d = (uint8_t*)dst + strlen(dst);
  const uint8_t* s = (const uint8_t*)src;

  size_t d_offset = (uintptr_t)d & (sizeof(uintptr_t) - 1);
  size_t s_offset = (uintptr_t)s & (sizeof(uintptr_t) - 1);
  __if_likely (((d_offset + s_offset) & (sizeof(uintptr_t) - 1)) == 0) {
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
    }

    uintptr_t*       a1 = (uintptr_t*)d;
    const uintptr_t* a2 = (const uintptr_t*)s;
    while (!__has_null(*a2)) {
      *a1++ = *a2++;
    }

    d = (uint8_t*)a1;
    s = (const uint8_t*)a2;
  }

  do {
    *d++ = *s++;
  } while (*s != '\0');

  return dst;

#endif // __OPTIMIZE_SIZE__
}
