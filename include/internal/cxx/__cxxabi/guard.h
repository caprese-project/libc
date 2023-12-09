#ifndef CAPRESE_LIBC_INTERNAL_CXX___CXXABI_GUARD_H_
#define CAPRESE_LIBC_INTERNAL_CXX___CXXABI_GUARD_H_

#include <internal/attribute.h>

namespace __cxxabiv1 {
  extern "C" {
    int  __cxa_guard_acquire(int* guard) __noexcept;
    void __cxa_guard_release(int* guard) __noexcept;
    void __cxa_guard_abort(int* guard) __noexcept;
  }
} // namespace __cxxabiv1

#endif // CAPRESE_LIBC_INTERNAL_CXX___CXXABI_GUARD_H_
