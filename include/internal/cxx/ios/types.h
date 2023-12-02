#ifndef CAPRESE_LIBC_INTERNAL_CXX_IOS_TYPES_H_
#define CAPRESE_LIBC_INTERNAL_CXX_IOS_TYPES_H_

#include <internal/cxx/stddef.h>

namespace std {
  using streamoff  = __ssize_t;
  using streamsize = __ssize_t;
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_IOS_TYPES_H_
