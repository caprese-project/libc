#include "./__has_null.h"

#include <internal/attribute.h>
#include <internal/branch.h>
#include <string.h>

__weak size_t strnlen(const char* s, size_t n) {
  const char* p = s;

#ifndef __OPTIMIZE_SIZE__

  const size_t s_offset = (uintptr_t)s & (sizeof(uintptr_t) - 1);

  __if_unlikely (s_offset != 0) {
    const size_t offset = sizeof(uintptr_t) - s_offset;
    for (size_t i = 0; i < offset; ++i) {
      __if_unlikely (i >= n || s[i] == '\0') {
        return i;
      }
    }
    p += offset;
  }

  const uintptr_t* a = (const uintptr_t*)p;
  while ((const char*)a - s + sizeof(uintptr_t) - 1 < n && !__has_null(*a)) {
    ++a;
  }
  p = (const char*)a;

#endif // __OPTIMIZE_SIZE__

  while (*p != '\0' && p - s < n) {
    ++p;
  }

  return p - s;
}
