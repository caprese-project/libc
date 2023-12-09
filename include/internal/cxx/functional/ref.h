#ifndef CAPRESE_LIBC_INTERNAL_CXX_FUNCTIONAL_REF_H_
#define CAPRESE_LIBC_INTERNAL_CXX_FUNCTIONAL_REF_H_

#include <internal/attribute.h>
#include <internal/cxx/memory/addressof.h>
#include <internal/cxx/type_traits/detection.h>
#include <internal/cxx/type_traits/logic.h>
#include <internal/cxx/type_traits/modify.h>
#include <internal/cxx/type_traits/type_relation.h>
#include <internal/cxx/utility/fwd.h>

namespace std {
  template<typename T>
  class reference_wrapper {
    T* _ptr;

  public:
    using type = T;

  public:
    template<typename U>
    __constexpr_cxx_std_20 reference_wrapper(__enable_if<__disjunction<__is_rvalue_reference<U>, __is_same_t<typename __remove_cv<U>::type, reference_wrapper<T>>>::value, U>&& ref) __noexcept
        : _ptr(__addressof(std::forward<U>(ref))) {};

    __constexpr_cxx_std_20 reference_wrapper(const reference_wrapper& other) __noexcept            = default;
    ~reference_wrapper() __noexcept                                                                = default;
    __constexpr_cxx_std_20 reference_wrapper& operator=(const reference_wrapper& other) __noexcept = default;

    __constexpr_cxx_std_20 operator T&() const __noexcept {
      return get();
    }

    __constexpr_cxx_std_20 T& get() const __noexcept {
      return *_ptr;
    }
  };

#if __cpp_deduction_guides
  template<typename T>
  reference_wrapper(T&) -> reference_wrapper<T>;
#endif

  template<typename T>
  __constexpr_cxx_std_20 inline reference_wrapper<T> ref(T& ref) __noexcept {
    return reference_wrapper<T>(ref);
  }

  template<typename T>
  __constexpr_cxx_std_20 inline reference_wrapper<const T> cref(const T& ref) __noexcept {
    return reference_wrapper<const T>(ref);
  }

  template<typename T>
  void ref(const T&&) = delete;

  template<typename T>
  void cref(const T&&) = delete;

  template<typename T>
  __constexpr_cxx_std_20 inline reference_wrapper<T> ref(reference_wrapper<T> ref) __noexcept {
    return ref;
  }

  template<typename T>
  __constexpr_cxx_std_20 inline reference_wrapper<const T> cref(reference_wrapper<T> ref) __noexcept {
    return { ref.get() };
  }
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_FUNCTIONAL_REF_H_
