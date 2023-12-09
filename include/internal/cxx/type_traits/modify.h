#ifndef CAPRESE_INTERNAL_CXX_TYPE_TRAITS_MODIFY_H_
#define CAPRESE_INTERNAL_CXX_TYPE_TRAITS_MODIFY_H_

#include <internal/cxx/type_traits/constant.h>

namespace std {
  template<typename...>
  using __void_t = void;

  template<typename Template, typename U>
  struct __replace_first { };

  template<template<typename, typename...> typename Template, typename U, typename T, typename... Tn>
  struct __replace_first<Template<T, Tn...>, U> {
    using type = Template<U, Tn...>;
  };

  template<typename T, typename = void>
  struct __is_referenceable: public __false_type { };

  template<typename T>
  struct __is_referenceable<T, __void_t<T&>>: public __true_type { };

  template<typename T>
  struct __remove_const {
    using type = T;
  };

  template<typename T>
  struct __remove_const<const T> {
    using type = T;
  };

  template<typename T>
  struct __remove_volatile {
    using type = T;
  };

  template<typename T>
  struct __remove_volatile<volatile T> {
    using type = T;
  };

  template<typename T>
  struct __remove_cv {
    using type = T;
  };

  template<typename T>
  struct __remove_cv<const T> {
    using type = T;
  };

  template<typename T>
  struct __remove_cv<volatile T> {
    using type = T;
  };

  template<typename T>
  struct __remove_cv<const volatile T> {
    using type = T;
  };

  template<typename T>
  struct __add_const {
    using type = const T;
  };

  template<typename T>
  struct __add_volatile {
    using type = volatile T;
  };

  template<typename T>
  struct __add_cv {
    using type = const volatile T;
  };

  template<typename T>
  struct __remove_reference {
    using type = T;
  };

  template<typename T>
  struct __remove_reference<T&> {
    using type = T;
  };

  template<typename T>
  struct __remove_reference<T&&> {
    using type = T;
  };

  template<typename T, bool = __is_referenceable<T>::value>
  struct __add_lvalue_reference_helper {
    using type = T;
  };

  template<typename T>
  struct __add_lvalue_reference_helper<T, true> {
    using type = T&;
  };

  template<typename T>
  struct __add_lvalue_reference: public __add_lvalue_reference_helper<T> { };

  template<typename T, bool = __is_referenceable<T>::value>
  struct __add_rvalue_reference_helper {
    using type = T;
  };

  template<typename T>
  struct __add_rvalue_reference_helper<T, true> {
    using type = T&&;
  };

  template<typename T>
  struct __add_rvalue_reference: public __add_rvalue_reference_helper<T> { };

  template<typename T>
  struct __remove_cvref {
    using type = typename __remove_cv<typename __remove_reference<T>::type>::type;
  };
} // namespace std

#endif // CAPRESE_INTERNAL_CXX_TYPE_TRAITS_MODIFY_H_
