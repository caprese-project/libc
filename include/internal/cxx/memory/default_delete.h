#ifndef CAPRESE_LIBC_INTERNAL_CXX_MEMORY_DEFAULT_DELETE_H_
#define CAPRESE_LIBC_INTERNAL_CXX_MEMORY_DEFAULT_DELETE_H_

#include <internal/attribute.h>
#include <internal/cxx/type_traits/detection.h>
#include <internal/cxx/type_traits/type.h>
#include <internal/cxx/type_traits/type_relation.h>

namespace std {
  template<typename T>
  struct default_delete {
    __constexpr default_delete() __noexcept = default;

    template<typename U, typename = typename __enable_if<__is_convertible<U*, T*>::value>::type>
    __constexpr_cxx_std_23 default_delete(const default_delete<U>&) __noexcept { }

    ~default_delete() = default;

    __constexpr_cxx_std_23 void operator()(T* ptr) const __noexcept {
      static_assert(!__is_void<T>::value, "Cannot delete pointer to incomplete type.");
      static_assert(sizeof(T) > 0, "Cannot delete pointer to incomplete type.");
      delete ptr;
    }
  };

  template<typename T>
  struct default_delete<T[]> {
    __constexpr default_delete() __noexcept = default;

    template<typename U, typename = typename __enable_if<__is_convertible<U (*)[], T (*)[]>::value>::type>
    __constexpr_cxx_std_23 default_delete(const default_delete<U[]>&) __noexcept { }

    template<typename U, typename = typename __enable_if<__is_convertible<U (*)[], T (*)[]>::value>::type>
    __constexpr_cxx_std_23 void operator()(U* ptr) const __noexcept {
      static_assert(sizeof(U) > 0, "Cannot delete pointer to incomplete type.");
      delete[] ptr;
    }
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_MEMORY_DEFAULT_DELETE_H_
