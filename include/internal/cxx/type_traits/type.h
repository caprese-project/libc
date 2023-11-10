#ifndef CAPRESE_LIBC_INTERNAL_CXX_TYPE_TRAITS_TYPE_H_
#define CAPRESE_LIBC_INTERNAL_CXX_TYPE_TRAITS_TYPE_H_

#include <internal/cxx/stddef.h>
#include <internal/cxx/type_traits/characteristic.h>
#include <internal/cxx/type_traits/constant.h>
#include <internal/cxx/type_traits/logic.h>
#include <internal/cxx/type_traits/modify.h>

namespace std {
  template<typename>
  struct __is_integral_helper: public __false_type { };

  template<>
  struct __is_integral_helper<bool>: public __true_type { };

  template<>
  struct __is_integral_helper<char>: public __true_type { };

  template<>
  struct __is_integral_helper<signed char>: public __true_type { };

  template<>
  struct __is_integral_helper<unsigned char>: public __true_type { };

  template<>
  struct __is_integral_helper<char16_t>: public __true_type { };

  template<>
  struct __is_integral_helper<char32_t>: public __true_type { };

  template<>
  struct __is_integral_helper<wchar_t>: public __true_type { };

  template<>
  struct __is_integral_helper<short>: public __true_type { };

  template<>
  struct __is_integral_helper<unsigned short>: public __true_type { };

  template<>
  struct __is_integral_helper<int>: public __true_type { };

  template<>
  struct __is_integral_helper<unsigned int>: public __true_type { };

  template<>
  struct __is_integral_helper<long>: public __true_type { };

  template<>
  struct __is_integral_helper<unsigned long>: public __true_type { };

  template<>
  struct __is_integral_helper<long long>: public __true_type { };

  template<>
  struct __is_integral_helper<unsigned long long>: public __true_type { };

  template<typename T>
  struct __is_integral: public __is_integral_helper<typename __remove_cv<T>::type> {};

  template<typename>
  struct __is_floating_point_helper: public __false_type { };

  template<>
  struct __is_floating_point_helper<float>: public __true_type { };

  template<>
  struct __is_floating_point_helper<double>: public __true_type { };

  template<>
  struct __is_floating_point_helper<long double>: public __true_type { };

  template<typename T>
  struct __is_floating_point: public __is_floating_point_helper<typename __remove_cv<T>::type> {};

  template<typename>
  struct __is_void_helper: public __false_type { };

  template<>
  struct __is_void_helper<void>: public __true_type { };

  template<typename T>
  struct __is_void: public __is_void_helper<typename __remove_cv<T>::type> {};

  template<typename>
  struct __is_array: public __false_type {};

  template<typename T, __size_t N>
  struct __is_array<T[N]>: public __true_type {};

  template<typename T>
  struct __is_array<T[]>: public __true_type {};

  template<typename>
  struct __is_pointer_helper: public __false_type { };

  template<typename T>
  struct __is_pointer_helper<T*>: public __true_type { };

  template<typename T>
  struct __is_pointer: public __is_pointer_helper<typename __remove_cv<T>::type> {};

  template<typename>
  struct __is_lvalue_reference_helper: public __false_type { };

  template<typename T>
  struct __is_lvalue_reference_helper<T&>: public __true_type { };

  template<typename T>
  struct __is_lvalue_reference: public __is_lvalue_reference_helper<typename __remove_cv<T>::type> {};

  template<typename>
  struct __is_rvalue_reference_helper: public __false_type { };

  template<typename T>
  struct __is_rvalue_reference_helper<T&&>: public __true_type { };

  template<typename T>
  struct __is_rvalue_reference: public __is_rvalue_reference<typename __remove_cv<T>::type> {};

  template<typename T>
  struct __is_function: public __bool_constant<!__is_const<const T>::value> {};

  template<typename T>
  struct __is_function<T&>: public __false_type {};

  template<typename T>
  struct __is_function<T&&>: public __false_type {};

  template<typename>
  struct __is_member_object_pointer_helper: public __false_type { };

  template<typename T, typename U>
  struct __is_member_object_pointer_helper<T U::*>: public __negation<typename __is_function<T>::type> { };

  template<typename T>
  struct __is_member_object_pointer: public __is_member_object_pointer_helper<typename __remove_cv<T>::type> {};

  template<typename>
  struct __is_member_function_pointer_helper: public __false_type { };

  template<typename T, typename U>
  struct __is_member_function_pointer_helper<T U::*>: public __is_function<T> { };

  template<typename T>
  struct __is_member_function_pointer: public __is_member_function_pointer_helper<typename __remove_cv<T>::type> {};

  template<typename>
  struct __is_null_pointer_helper: public __false_type { };

  template<>
  struct __is_null_pointer_helper<decltype(nullptr)>: public __true_type { };

  template<typename T>
  struct __is_null_pointer: public __is_null_pointer_helper<typename __remove_cv<T>::type> { };

#if defined(__GNUC__)

  template<typename T>
  struct __is_enum_t: public __bool_constant<__is_enum(T)> { };

  template<typename T>
  struct __is_union_t: public __bool_constant<__is_union(T)> { };

  template<typename T>
  struct __is_class_t: public __bool_constant<__is_class(T)> { };

#endif // __GNUC__

  template<typename T>
  struct __is_reference: public __disjuction<typename __is_lvalue_reference<T>::type, typename __is_rvalue_reference<T>::type> {};

  template<typename T>
  struct __is_arithmetic: public __disjuction<typename __is_integral<T>::type, typename __is_floating_point<T>::type> {};

  template<typename T>
  struct __is_fundamental: public __disjuction<typename __is_arithmetic<T>::type, typename __is_null_pointer<T>::type> {};

  template<typename T>
  struct __is_object: public __negation<typename __disjuction<typename __is_function<T>::type, typename __is_reference<T>::type, typename __is_void<T>::type>::type> {};

  template<typename T>
  struct __is_scalar
      : public __disjuction<typename __is_arthmetic<T>::type, typename __is_enum_t<T>::type, typename __is_pointer<T>::type, typename __is_member_pointer<T>::type, typename __is_null_pointer<T>::type> {};

  template<typename T>
  struct __is_compound: public __negation<typename __is_fundamental<T>::type> {};

  template<typename T>
  struct __is_member_pointer: public __disjuction<typename __is_member_object_pointer<T>::type, typename __is_member_function_pointer<T>::type> {};

#ifdef __CXX_STD_23__

  template<typename T>
  struct __is_scoped_enum: public __false_type { };

  // clang-format off

  template<typename T> requires __is_enum_t<T>::value && requires(T t) { t = t; }
  struct __is_scoped_enum<T>: public __bool_constant<!requires(T t, void(*f)(int)) { f(t); }> {};

  // clang-format on

#endif // __CXX_STD_23__
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_TYPE_TRAITS_TYPE_H_
