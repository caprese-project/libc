#ifndef CAPRESE_LIBC_INTERNAL_CXX_UTILITY_FWD_H_
#define CAPRESE_LIBC_INTERNAL_CXX_UTILITY_FWD_H_

#include <internal/attribute.h>
#include <internal/cxx/type_traits/modify.h>
#include <internal/cxx/type_traits/type.h>

namespace std {
  template<typename T>
  __constexpr_cxx_std_14 T&& forward(typename __remove_reference<T>::type& t) noexcept {
    return static_cast<T&&>(t);
  }

  template<typename T>
  __constexpr_cxx_std_14 T&& forward(typename __remove_reference<T>::type&& t) noexcept {
    static_assert(!__is_lvalue_reference<T>::value);
    return static_cast<T&&>(t);
  }

  template<typename T>
  __constexpr_cxx_std_14 typename __remove_reference<T>::type&& move(T&& t) noexcept {
    return static_cast<typename __remove_reference<T>::type&&>(t);
  }
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_UTILITY_FWD_H_
