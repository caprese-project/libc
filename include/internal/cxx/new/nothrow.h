#ifndef CAPRESE_LIBC_INTERNAL_CXX_NEW_NOTHROW_H_
#define CAPRESE_LIBC_INTERNAL_CXX_NEW_NOTHROW_H_

namespace std {
  struct nothrow_t {
    explicit nothrow_t() = default;
  };

  extern const nothrow_t nothrow;
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_NEW_NOTHROW_H_
