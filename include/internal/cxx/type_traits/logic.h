#ifndef CAPRESE_LIBC_INTERNAL_CXX_TYPE_TRAITS_LOGIC_H_
#define CAPRESE_LIBC_INTERNAL_CXX_TYPE_TRAITS_LOGIC_H_

#include <internal/cxx/type_traits/constant.h>

namespace std {
  template<bool cond, typename Then, typename Else>
  struct __conditional {
    using type = Then;
  };

  template<typename Then, typename Else>
  struct __conditional<false, Then, Else> {
    using type = Else;
  };

  template<typename... Traits>
  struct __conjunction;

  template<>
  struct __conjunction<>: public __true_type { };

  template<typename T>
  struct __conjunction<T>: public T { };

  template<typename T, typename... Traits>
  struct __conjunction<T, Traits...>: public __conditional<T::value, typename __conjunction<Traits...>::type, T>::type { };

  template<typename... Traits>
  struct __disjunction;

  template<>
  struct __disjunction<>: public __false_type { };

  template<typename T>
  struct __disjunction<T>: public T { };

  template<typename T, typename... Traits>
  struct __disjunction<T, Traits...>: public __conditional<T::value, T, typename __disjunction<Traits...>::type>::type { };

  template<typename T>
  struct __negation: public __bool_constant<!T::value> { };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_TYPE_TRAITS_LOGIC_H_
