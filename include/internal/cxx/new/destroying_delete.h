#ifndef CAPRESE_LIBC_INTERNAL_CXX_NEW_DESTROYING_DELETE_H_
#define CAPRESE_LIBC_INTERNAL_CXX_NEW_DESTROYING_DELETE_H_

#include <internal/version.h>

namespace std {
  struct destroying_delete_t {
    explicit destroying_delete_t() = default;
  };

#ifdef __CXX_STD_20__
  inline constexpr destroying_delete_t destroying_delete {};
#endif // __CXX_STD_20__

} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_NEW_DESTROYING_DELETE_H_
