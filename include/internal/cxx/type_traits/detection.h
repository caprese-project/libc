#ifndef CAPRESE_LIBC_INTERNAL_CXX_TYPE_TRAITS_DETECTION_H_
#define CAPRESE_LIBC_INTERNAL_CXX_TYPE_TRAITS_DETECTION_H_

#include <internal/cxx/type_traits/constant.h>
#include <internal/cxx/type_traits/modify.h>

namespace std {
  template<template<typename...> typename, typename = void, typename... Args>
  struct __detect: __false_type { };

  template<template<typename...> typename Cond, typename... Args>
  struct __detect<Cond, __void_t<Cond<Args...>>>: __true_type { };

  template<template<typename...> typename Cond, typename... Args>
  using __detect_t = typename __detect<Cond, __void_t<Cond<Args...>>>::type;

  template<template<typename...> typename Cond, typename... Args>
  using __detect_v = __detect<Cond, __void_t<Cond<Args...>>>::value;

  template<template<typename...> typename Then, typename Else, typename = void, typename... Args>
  struct __detect_type {
    using type = Else;
  };

  template<template<typename...> typename Then, typename Else, typename... Args>
  struct __detect_type<Then, Else, __void_t<Then<Args...>>, Args...> {
    using type = Then<Args...>;
  };

  template<bool, typename = void>
  struct __enable_if { };

  template<typename T>
  struct __enable_if<true, T> {
    using type = T;
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_TYPE_TRAITS_DETECTION_H_
