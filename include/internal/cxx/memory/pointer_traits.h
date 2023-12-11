#ifndef CAPRESE_LIBC_INTERNAL_CXX_MEMORY_POINTER_TRAITS_H_
#define CAPRESE_LIBC_INTERNAL_CXX_MEMORY_POINTER_TRAITS_H_

#include <cstddef>
#include <internal/cxx/memory/addressof.h>
#include <internal/cxx/type_traits/detection.h>
#include <internal/cxx/type_traits/logic.h>
#include <internal/cxx/type_traits/type.h>

namespace std {
  template<typename Ptr>
  struct pointer_traits {
  private:
    template<typename T>
    using __difference_type = typename T::difference_type;

    template<typename T>
    using __element_type = typename T::element_type;

    template<typename T, typename U>
    using __rebind = typename T::template rebind<U>;

  public:
    using pointer         = Ptr;
    using difference_type = typename __detect_type<__difference_type, ptrdiff_t, pointer>::type;
    using element_type    = typename __detect_type<__element_type, __ill_formed, pointer>::type;

    template<typename U>
    using rebind = typename __detect_type<__rebind, __ill_formed, pointer, U>::type;

    static __constexpr_cxx_std_20 auto pointer_to(element_type& ref) -> decltype(pointer::pointer_to(ref)) {
      return pointer::pointer_to(ref);
    }
  };

  template<typename T>
  struct pointer_traits<T*> {
  public:
    using pointer         = T*;
    using element_type    = T;
    using difference_type = ptrdiff_t;

    template<typename U>
    using rebind = U*;

    static __constexpr_cxx_std_20 pointer pointer_to(typename __conditional<__is_void<T>::value, __ill_formed, T>::type& ref) __noexcept {
      return __addressof(ref);
    }
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_MEMORY_POINTER_TRAITS_H_
