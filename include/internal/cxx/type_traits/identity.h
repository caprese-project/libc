#ifndef CAPRESE_LIBC_INTERNAL_CXX_TYPE_TRAITS_IDENTITY_H_
#define CAPRESE_LIBC_INTERNAL_CXX_TYPE_TRAITS_IDENTITY_H_

namespace std {
  template<typename T>
  struct __type_identity {
    using type = T;
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_TYPE_TRAITS_IDENTITY_H_
