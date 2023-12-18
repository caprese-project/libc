#ifndef CAPRESE_LIBC_INTERNAL_CXX_VARIANT_VARIANT_ALTERNATIVE_H_
#define CAPRESE_LIBC_INTERNAL_CXX_VARIANT_VARIANT_ALTERNATIVE_H_

#include <internal/cxx/stddef.h>
#include <internal/cxx/type_traits/modify.h>

namespace std {
  template<typename... Types>
  class variant;

  template<__size_t I, typename T>
  struct variant_alternative;

  template<__size_t I, typename T>
  struct variant_alternative<I, const T> {
    using type = typename __add_const<typename variant_alternative<I, T>::type>::type;
  };

  template<__size_t I, typename T>
  struct variant_alternative<I, volatile T> {
    using type = typename __add_volatile<typename variant_alternative<I, T>::type>::type;
  };

  template<__size_t I, typename T>
  struct variant_alternative<I, const volatile T> {
    using type = typename __add_cv<typename variant_alternative<I, T>::type>::type;
  };

  template<__size_t I, typename T, typename... Types>
  struct variant_alternative<I, variant<T, Types...>> {
    using type = typename variant_alternative<I - 1, variant<Types...>>::type;
  };

  template<typename T, typename... Types>
  struct variant_alternative<0, variant<T, Types...>> {
    using type = T;
  };

  template<__size_t I, typename T>
  using variant_alternative_t = typename variant_alternative<I, T>::type;
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_VARIANT_VARIANT_ALTERNATIVE_H_
