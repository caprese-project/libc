#ifndef CAPRESE_LIBC_INTERNAL_CXX_TYPE_TRAITS_CONSTANT_H_
#define CAPRESE_LIBC_INTERNAL_CXX_TYPE_TRAITS_CONSTANT_H_

#include <internal/attribute.h>
#include <internal/version.h>

namespace std {
  template<typename T, T _v>
  struct __integral_constant {
    static constexpr T value = _v;
    using value_type         = T;
    using type               = __integral_constant<T, _v>;

    constexpr operator value_type() const __noexcept_cxx_std_14 {
      return value;
    }

#ifdef __CXX_STD_14__
    constexpr value_type operator()() const __noexcept {
      return value;
    }
#endif // __CXX_STD_14__
  };

  template<bool B>
  using __bool_constant = __integral_constant<bool, B>;

  using __true_type  = __bool_constant<true>;
  using __false_type = __bool_constant<false>;
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_TYPE_TRAITS_CONSTANT_H_
