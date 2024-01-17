#ifndef CAPRESE_LIBC_INTERNAL_CXX_UTILITY_SWAP_H_
#define CAPRESE_LIBC_INTERNAL_CXX_UTILITY_SWAP_H_

#include <internal/attribute.h>
#include <internal/cxx/stddef.h>
#include <internal/cxx/type_traits/characteristic.h>
#include <internal/cxx/utility/fwd.h>

namespace std {
  template<typename T>
  __constexpr_cxx_std_20 inline typename __enable_if<__conjunction<__negation<__is_tuple_like<T>>, __is_move_constructible<T>, __is_move_assignable<T>>::value>::type swap(T& a, T& b) noexcept(
      __conjunction<__is_nothrow_move_constructible<T>, __is_nothrow_move_assignable<T>>::value) {
    T tmp = move(a);
    a     = move(b);
    b     = move(tmp);
  }

  template<typename T, __size_t N>
  __constexpr_cxx_std_20 inline typename __enable_if<__is_swappable<T>::value>::type swap(T (&a)[N], T (&b)[N]) noexcept(__is_nothrow_swappable<T>::value) {
    for (__size_t i = 0; i < N; ++i) {
      swap(a[i], b[i]);
    }
  }
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_UTILITY_SWAP_H_
