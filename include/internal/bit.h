#ifndef CAPRESE_LIBC_INTERNAL_BIT_H_
#define CAPRESE_LIBC_INTERNAL_BIT_H_

#include <internal/datamodel.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __GNUC__
#define __countr_zero32(x) ((size_t)__builtin_ctz(x))
#define __countr_zero64(x) ((size_t)__builtin_ctzl(x))
#else  // ^^^ __GNUC__ ^^^ / vvv !__GNUC__ vvv
static inline size_t __countr_zero32(uint32_t x) {
  if (x == 0) {
    return 32;
  }

  size_t result = 0;
  while ((x & 1) == 0) {
    x >>= 1;
    ++result;
  }
  return result;
}

static inline size_t __countr_zero64(uint64_t x) {
  if (x == 0) {
    return 64;
  }

  size_t result = 0;
  while ((x & 1) == 0) {
    x >>= 1;
    ++result;
  }
  return result;
}
#endif // !__GNUC__

#if defined(__LP64)
#define __countr_zerosz(x) (__countr_zero64(x))
#elif defined(__ILP32)
#define __countr_zerosz(x) (__countr_zero32(x))
#else
#define __countr_zerosz(x) (__countr_zero64(x))
#endif // __LP64

#endif // CAPRESE_LIBC_INTERNAL_BIT_H_
