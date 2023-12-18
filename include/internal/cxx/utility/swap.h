#ifndef CAPRESE_LIBC_INTERNAL_CXX_UTILITY_SWAP_H_
#define CAPRESE_LIBC_INTERNAL_CXX_UTILITY_SWAP_H_

#include <internal/attribute.h>
#include <internal/cxx/stddef.h>
#include <internal/cxx/utility/fwd.h>

namespace std {
  template<typename T>
  __constexpr_cxx_std_20 void swap(T& a, T& b) __noexcept {
    T tmp = move(a);
    a     = move(b);
    b     = move(tmp);
  }

  template<typename T, __size_t N>
  __constexpr_cxx_std_20 void swap(T (&a)[N], T (&b)[N]) __noexcept {
    for (__size_t i = 0; i < N; ++i) {
      swap(a[i], b[i]);
    }
  }
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_UTILITY_SWAP_H_
