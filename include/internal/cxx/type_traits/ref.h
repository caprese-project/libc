#ifndef CAPRESE_INTERNAL_CXX_TYPE_TRAITS_REF_H_
#define CAPRESE_INTERNAL_CXX_TYPE_TRAITS_REF_H_

#include <internal/cxx/functional/ref.h>
#include <internal/cxx/type_traits/decay.h>

namespace std {
  template<typename T>
  struct __unwrap_reference {
    using type = T;
  };

  template<typename T>
  struct __unwrap_reference<reference_wrapper<T>> {
    using type = T&;
  };

  template<typename T>
  struct __unwrap_ref_decay: __unwrap_reference<typename __decay<T>::type> { };
} // namespace std

#endif // CAPRESE_INTERNAL_CXX_TYPE_TRAITS_REF_H_
