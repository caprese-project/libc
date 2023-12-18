#ifndef CAPRESE_LIBC_INTERNAL_CXX_VARIANT_BAD_VARIANT_ACCESS_H_
#define CAPRESE_LIBC_INTERNAL_CXX_VARIANT_BAD_VARIANT_ACCESS_H_

#include <internal/cxx/exception/exception.h>

namespace std {
  class bad_variant_access: public exception {
  public:
    bad_variant_access() noexcept                                     = default;
    ~bad_variant_access() noexcept                                    = default;
    bad_variant_access(const bad_variant_access&) noexcept            = default;
    bad_variant_access(bad_variant_access&&) noexcept                 = default;
    bad_variant_access& operator=(const bad_variant_access&) noexcept = default;
    bad_variant_access& operator=(bad_variant_access&&) noexcept      = default;

    inline virtual const char* what() const noexcept override {
      return "std::bad_variant_access";
    }
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_VARIANT_BAD_VARIANT_ACCESS_H_
