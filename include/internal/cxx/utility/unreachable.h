#ifndef CAPRESE_LIBC_INTERNAL_CXX_UTILITY_UNREACHABLE_H_
#define CAPRESE_LIBC_INTERNAL_CXX_UTILITY_UNREACHABLE_H_

#include <internal/attribute.h>
#include <internal/version.h>

#ifdef __CXX_STD_23__

namespace std {
  __noreturn __force_inline void unreachable() {
#if defined(__GNUC__)
    __builtin_unreachable();
#else  // ^^^ __GNUC__ ^^^ / vvv !__GNUC__ vvv
    static_assert(false, "Unsupported compiler");
#endif // !__GNUC__
  }
} // namespace std

#endif // __CXX_STD_23__

#endif // CAPRESE_LIBC_INTERNAL_CXX_UTILITY_UNREACHABLE_H_
