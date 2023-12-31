#ifndef CAPRESE_LIBC_INTERNAL_CXX_STDDEF_H_
#define CAPRESE_LIBC_INTERNAL_CXX_STDDEF_H_

#include <internal/stddef.h>

namespace std {
  struct __ill_formed;

  using __ptrdiff_t = __PTRDIFF_TYPE;
  using __size_t    = __SIZE_TYPE;
  using __ssize_t   = __SSIZE_TYPE;
  using __nullptr_t = decltype(nullptr);
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_STDDEF_H_
