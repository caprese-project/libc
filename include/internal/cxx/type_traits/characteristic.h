#ifndef CAPRESE_LIBC_INTERNAL_CXX_TYPE_TRAITS_CHARACTERISTIC_H_
#define CAPRESE_LIBC_INTERNAL_CXX_TYPE_TRAITS_CHARACTERISTIC_H_

#include <internal/cxx/stddef.h>
#include <internal/cxx/type_traits/constant.h>
#include <internal/cxx/type_traits/logic.h>
#include <internal/cxx/type_traits/modify.h>
#include <internal/cxx/utility/declval.h>

namespace std {
  template<typename T>
  struct __is_void;

  template<typename T>
  struct __is_function_t;

  template<typename T>
  struct __is_array;

  template<typename T>
  struct __is_reference;

  template<typename T>
  struct __is_scalar;

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

  template<typename T>
  struct __is_bounded_array: public __false_type { };

  template<typename T, __size_t N>
  struct __is_bounded_array<T[N]>: public __true_type { };

  template<typename T>
  struct __is_unbounded_array: public __false_type { };

  template<typename T>
  struct __is_unbounded_array<T[]>: public __true_type { };

  template<typename T, typename... Args>
  struct __is_constructible_t: public __bool_constant<__is_constructible(T, Args...)> { };

  template<typename T>
  struct __is_default_constructible: public __is_constructible_t<T> { };

  template<typename T, bool = __is_referenceable<T>::value>
  struct __is_copy_constructible;

  template<typename T>
  struct __is_copy_constructible<T, false>: public __false_type { };

  template<typename T>
  struct __is_copy_constructible<T, true>: public __is_constructible_t<T, const T&> { };

  template<typename T, bool = __is_referenceable<T>::value>
  struct __is_move_constructible;

  template<typename T>
  struct __is_move_constructible<T, false>: public __false_type { };

  template<typename T>
  struct __is_move_constructible<T, true>: public __is_constructible_t<T, T&&> { };

  template<typename T, typename... Args>
  struct __is_nothrow_constructible_t: public __bool_constant<__is_nothrow_constructible(T, Args...)> { };

  template<typename T>
  struct __is_nothrow_default_constructible: public __is_nothrow_constructible_t<T> { };

  template<typename T, bool = __is_referenceable<T>::value>
  struct __is_nothrow_copy_constructible_helper;

  template<typename T>
  struct __is_nothrow_copy_constructible_helper<T, false>: public __false_type { };

  template<typename T>
  struct __is_nothrow_copy_constructible_helper<T, true>: public __is_nothrow_constructible_t<T, const T&> { };

  template<typename T>
  struct __is_nothrow_copy_constructible: public __is_nothrow_copy_constructible_helper<T> { };

  template<typename T, bool = __is_referenceable<T>::value>
  struct __is_nothrow_move_constructible_helper;

  template<typename T>
  struct __is_nothrow_move_constructible_helper<T, false>: public __false_type { };

  template<typename T>
  struct __is_nothrow_move_constructible_helper<T, true>: public __is_nothrow_constructible_t<T, T&&> { };

  template<typename T>
  struct __is_nothrow_move_constructible: public __is_nothrow_move_constructible_helper<T> { };

  template<typename T, typename U>
  struct __is_assignable_t: public __bool_constant<__is_assignable(T, U)> { };

  template<typename T, bool = __is_referenceable<T>::value>
  struct __is_copy_assignable_helper;

  template<typename T>
  struct __is_copy_assignable_helper<T, false>: public __false_type { };

  template<typename T>
  struct __is_copy_assignable_helper<T, true>: public __is_assignable_t<T&, const T&> { };

  template<typename T>
  struct __is_copy_assignable: public __is_copy_assignable_helper<T> { };

  template<typename T, bool = __is_referenceable<T>::value>
  struct __is_move_assignable_helper;

  template<typename T>
  struct __is_move_assignable_helper<T, false>: public __false_type { };

  template<typename T>
  struct __is_move_assignable_helper<T, true>: public __is_assignable_t<T&, T&&> { };

  template<typename T>
  struct __is_move_assignable: public __is_move_assignable_helper<T> { };

  template<typename T,
           bool = __disjunction<typename __is_void<T>::type, typename __is_function_t<T>::type, typename __is_array<T>::type, typename __is_reference<T>::type, typename __is_scalar<T>::type>::value>
  struct __is_destructible_helper: public __disjunction<typename __is_reference<T>::type, typename __is_scalar<T>::type> { };

  template<typename T>
  struct __is_destructible_helper<T, false> {
  private:
    template<typename _T, typename = decltype(__declval<_T&>().~T())>
    static __true_type __type(int);

    template<typename>
    static __false_type __type(...);

  public:
    using type = decltype(__type<T>(0));
  };

  template<typename T>
  struct __is_destructible_t: public __is_destructible_helper<T>::type { };

  template<typename T, typename... Args>
  struct __is_trivially_constructible_t: public __bool_constant<__is_trivially_constructible(T, Args...)> { };

  template<typename T>
  struct __is_trivially_default_constructible: public __is_trivially_constructible_t<T> { };

  template<typename T, bool = __is_referenceable<T>::value>
  struct __is_trivially_copy_constructible_helper;

  template<typename T>
  struct __is_trivially_copy_constructible_helper<T, false>: public __false_type { };

  template<typename T>
  struct __is_trivially_copy_constructible_helper<T, true>: public __is_trivially_constructible_t<T, const T&> { };

  template<typename T>
  struct __is_trivially_copy_constructible: public __is_trivially_copy_constructible_helper<T> { };

  template<typename T, bool = __is_referenceable<T>::value>
  struct __is_trivially_move_constructible_helper;

  template<typename T>
  struct __is_trivially_move_constructible_helper<T, false>: public __false_type { };

  template<typename T>
  struct __is_trivially_move_constructible_helper<T, true>: public __is_trivially_constructible_t<T, T&&> { };

  template<typename T>
  struct __is_trivially_move_constructible: public __is_trivially_move_constructible_helper<T> { };

  template<typename T>
  struct __is_trivially_destructible_t: public __conjunction<typename __is_destructible_t<T>::type, __bool_constant<__has_trivial_destructor(T)>> { };

  template<typename T, typename U>
  struct __is_nothrow_assignable_t: public __bool_constant<__is_nothrow_assignable(T, U)> { };

  template<typename T, bool = __is_referenceable<T>::value>
  struct __is_nothrow_copy_assignable_helper;

  template<typename T>
  struct __is_nothrow_copy_assignable_helper<T, false>: public __false_type { };

  template<typename T>
  struct __is_nothrow_copy_assignable_helper<T, true>: public __is_nothrow_assignable_t<T&, const T&> { };

  template<typename T>
  struct __is_nothrow_copy_assignable: public __is_nothrow_copy_assignable_helper<T> { };

  template<typename T, bool = __is_referenceable<T>::value>
  struct __is_nothrow_move_assignable_helper;

  template<typename T>
  struct __is_nothrow_move_assignable_helper<T, false>: public __false_type { };

  template<typename T>
  struct __is_nothrow_move_assignable_helper<T, true>: public __is_nothrow_assignable_t<T&, T&&> { };

  template<typename T>
  struct __is_nothrow_move_assignable: public __is_nothrow_move_assignable_helper<T> { };

#endif // __GNUC__
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_TYPE_TRAITS_CHARACTERISTIC_H_
