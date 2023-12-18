#ifndef CAPRESE_LIBC_INTERNAL_CXX_VARIANT_VARIANT_SIZE_H_
#define CAPRESE_LIBC_INTERNAL_CXX_VARIANT_VARIANT_SIZE_H_

#include <internal/cxx/stddef.h>
#include <internal/cxx/type_traits/constant.h>

namespace std {
  template<typename... Types>
  class variant;

  template<typename T>
  struct variant_size;

  template<typename T>
  struct variant_size<const T>: variant_size<T> { };

  template<typename T>
  struct variant_size<volatile T>: variant_size<T> { };

  template<typename T>
  struct variant_size<const volatile T>: variant_size<T> { };

  template<typename... Types>
  struct variant_size<variant<Types...>>: __integral_constant<__size_t, sizeof...(Types)> { };

  template<typename T>
  inline constexpr __size_t variant_size_v = variant_size<T>::value;
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_VARIANT_VARIANT_SIZE_H_
