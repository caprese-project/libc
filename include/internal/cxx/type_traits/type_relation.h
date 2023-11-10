#ifndef CAPRESE_LIBC_INTERNAL_CXX_TYPE_TRAITS_TYPE_RELATION_H_
#define CAPRESE_LIBC_INTERNAL_CXX_TYPE_TRAITS_TYPE_RELATION_H_

#include <internal/cxx/type_traits/logic.h>
#include <internal/cxx/type_traits/type.h>
#include <internal/cxx/utility/declval.h>

namespace std {
  template<typename T, typename U>
  struct __is_same_t: public __bool_constant<__is_same(T, U)> { };

  template<typename Base, typename Derived>
  struct __is_base_of_t: public __bool_constant<__is_base_of(Base, Derived)> { };

  template<typename From, typename To, bool = __disjunction<typename __is_void<From>::type, typename __is_function<To>::type, typename __is_array<To>::type>::value>
  struct __is_convertible_helper: public __is_void<To> { };

  template<typename From, typename To>
  struct __is_convertible_helper<From, To, false> {
  private:
    template<typename _To>
    static void __helper(_To) noexcept;

    template<typename _From, typename _To, typename = decltype(__helper<_To>(__declval<_From>()))>
    static __true_type __type();

    template<typename, typename>
    static __false_type __type(...);

  public:
    using type = decltype(__type<From, To>(0));
  };

  template<typename From, typename To>
  struct __is_convertible: public __is_convertible_helper<From, To> {};
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_TYPE_TRAITS_TYPE_RELATION_H_
