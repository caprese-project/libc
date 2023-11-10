#ifndef CAPRESE_LIBC_INTERNAL_CXX_STDDEF_H_
#define CAPRESE_LIBC_INTERNAL_CXX_STDDEF_H_

#include <internal/stddef.h>

namespace std {
  using __ptrdiff_t = __PTRDIFF_TYPE;
  using __size_t    = __SIZE_TYPE;
  using __ssize_t   = __SSIZE_TYPE;
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_STDDEF_H_
