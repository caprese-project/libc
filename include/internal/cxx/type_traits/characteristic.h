#ifndef CAPRESE_LIBC_INTERNAL_CXX_TYPE_TRAITS_CHARACTERISTIC_H_
#define CAPRESE_LIBC_INTERNAL_CXX_TYPE_TRAITS_CHARACTERISTIC_H_

#include <internal/cxx/type_traits/constant.h>

namespace std {
  template<typename>
  struct __is_const: public __false_type {};

  template<typename T>
  struct __is_const<const T>: public __true_type {};

  template<typename>
  struct __is_volatile: public __false_type {};

  template<typename T>
  struct __is_volatile<volatile T>: public __true_type {};

#if defined(__GNUC__)

  template<typename T>
  struct __is_trivial_t: public __bool_constant<__is_trivial(T)> { };

  template<typename T>
  struct __is_trivially_copyable_t: public __bool_constant<__is_trivially_copyable(T)> { };

  template<typename T>
  struct __is_standard_layout_t: public __bool_constant<__is_standard_layout(T)> { };

  template<typename T>
  struct __is_empty_t: public __bool_constant<__is_empty(T)> { };

  template<typename T>
  struct __is_polymorphic_t: public __bool_constant<__is_polymorphic(T)> { };

  template<typename T>
  struct __is_abstract_t: public __bool_constant<__is_abstract(T)> { };

#ifdef __CXX_STD_14__

  template<typename T>
  struct __is_final_t: public __bool_constant<__is_final(T)> { };

#endif // __CXX_STD_14__

#ifdef __CXX_STD_17__

  template<typename T>
  struct __is_aggregate_t: public __bool_constant<__is_aggregate(T)> { };

#endif // __CXX_STD_17__

#endif // __GNUC__
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_TYPE_TRAITS_CHARACTERISTIC_H_