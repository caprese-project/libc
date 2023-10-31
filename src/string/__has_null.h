#ifndef CAPRESE_LIBC_STRING_HAS_NULL_H_
#define CAPRESE_LIBC_STRING_HAS_NULL_H_

#include <internal/datamodel.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static inline bool __has_null(uintptr_t ch) {
#if defined(__LP64)
  return (ch - 0x0101010101010101) & ~ch & 0x8080808080808080;
#elif defined(__ILP32)
  return (ch - 0x01010101) & ~ch & 0x80808080;
#else
  const uint8_t* p = (const uint8_t*)&ch;
  for (size_t i = 0; i < sizeof(uintptr_t); ++i) {
    if (p[i] == '\0') {
      return true;
    }
  }
  return false;
#endif
}

#endif // CAPRESE_LIBC_STRING_HAS_NULL_H_
