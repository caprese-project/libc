#ifndef CAPRESE_LIBC_INTERNAL_CXX_ALGORITHM_MINMAX_H_
#define CAPRESE_LIBC_INTERNAL_CXX_ALGORITHM_MINMAX_H_

#include <internal/attribute.h>

namespace std {
  template<typename T>
  const __constexpr_cxx_std_14 T& min(const T& a, const T& b) {
    return a < b ? a : b;
  }

  template<typename T, typename Compare>
  const __constexpr_cxx_std_14 T& min(const T& a, const T& b, Compare comp) {
    return comp(a, b) ? a : b;
  }

  template<typename T>
  const __constexpr_cxx_std_14 T& max(const T& a, const T& b) {
    return a > b ? a : b;
  }

  template<typename T, typename Compare>
  const __constexpr_cxx_std_14 T& max(const T& a, const T& b, Compare comp) {
    return comp(a, b) ? b : a;
  }
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_ALGORITHM_MINMAX_H_
