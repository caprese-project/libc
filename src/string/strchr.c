#include <internal/bit.h>
#include <internal/branch.h>
#include <internal/unreachable.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "./__has_null.h"

__weak char* strchr(const char* s, int ch) {
#ifdef __OPTIMIZE_SIZE__

  return (char*)memchr(s, ch, strlen(s) + 1);

#else // ^^^ __OPTIMIZE_SIZE__ ^^^ / vvv !__OPTIMIZE_SIZE__ vvv

  const uint8_t* p = (const uint8_t*)s;

  const size_t s_offset = (uintptr_t)s & (sizeof(uintptr_t) - 1);
  __if_unlikely (s_offset != 0) {
    const size_t offset = sizeof(uintptr_t) - s_offset;
    for (size_t i = 0; i < offset; ++i) {
      __if_unlikely (p[i] == (uint8_t)ch) {
        return (char*)&p[i];
      } else __if_unlikely (p[i] == '\0') {
        return NULL;
      }
    }
    p += offset;
  }

  uintptr_t mask = (uint8_t)ch;
  for (size_t i = 0, l = __countr_zerosz(sizeof(uintptr_t)); i < l; ++i) {
    mask |= mask << (8 << i);
  }

  const uintptr_t* a = (const uintptr_t*)p;
  while (true) {
    __if_unlikely (__has_null(*a ^ mask) || __has_null(*a)) {
      p = (const uint8_t*)a;
      for (size_t i = 0; i < sizeof(uintptr_t); ++i) {
        __if_unlikely (p[i] == (uint8_t)ch) {
          return (char*)&p[i];
        } else __if_unlikely (p[i] == '\0') {
          return NULL;
        }
      }
      __unreachable();
    }
    ++a;
  }

#endif // __OPTIMIZE_SIZE__
}
