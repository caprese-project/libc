#include <internal/branch.h>
#include <string.h>

#include "./__has_null.h"

__weak size_t strlen(const char* s) {
  const char* p = s;

#ifndef __OPTIMIZE_SIZE__

  const size_t s_offset = (uintptr_t)s & (sizeof(uintptr_t) - 1);

  __if_unlikely (s_offset != 0) {
    const size_t offset = sizeof(uintptr_t) - s_offset;
    for (size_t i = 0; i < offset; ++i) {
      __if_unlikely (s[i] == '\0') {
        return i;
      }
    }
    p += offset;
  }

  const uintptr_t* a = (const uintptr_t*)p;
  while (!__has_null(*a)) {
    ++a;
  }
  p = (const char*)a;

#endif // __OPTIMIZE_SIZE__

  while (*p != '\0') {
    ++p;
  }

  return p - s;
}
