#include <internal/branch.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "./__has_null.h"

__weak char* strncpy(char* __restrict dst, const char* __restrict src, size_t n) {
#ifdef __OPTIMIZE_SIZE__

  size_t src_len = strlen(src) + 1;
  __if_likely (src_len < n) {
    n = src_len;
  }
  return (char*)memcpy(dst, src, n);

#else // ^^^ __OPTIMIZE_SIZE__ ^^^ / vvv !__OPTIMIZE_SIZE__ vvv

  uint8_t*       d = (uint8_t*)dst;
  const uint8_t* s = (const uint8_t*)src;

  const size_t dst_offset = (uintptr_t)dst & (sizeof(uintptr_t) - 1);
  const size_t src_offset = (uintptr_t)src & (sizeof(uintptr_t) - 1);

  __if_likely (n >= sizeof(uintptr_t) && dst_offset == src_offset && src_offset <= n) {
    __if_unlikely (dst_offset != 0) {
      const size_t offset = sizeof(uintptr_t) - dst_offset;
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

  for (size_t i = 0; i < n; ++i) {
    d[i] = s[i];
    __if_unlikely (s[i] == '\0') {
      break;
    }
  }

  return dst;

#endif // __OPTIMIZE_SIZE__
}
