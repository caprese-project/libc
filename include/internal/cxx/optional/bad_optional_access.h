#ifndef CAPRESE_LIBC_INTERNAL_CXX_OPTIONAL_BAD_OPTIONAL_ACCESS_H_
#define CAPRESE_LIBC_INTERNAL_CXX_OPTIONAL_BAD_OPTIONAL_ACCESS_H_

#include <exception>
#include <internal/attribute.h>

namespace std {
  class bad_optional_access: public exception {
  public:
    bad_optional_access() __noexcept          = default;
    virtual ~bad_optional_access() __noexcept = default;
    virtual const char* what() const __noexcept;
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_OPTIONAL_BAD_OPTIONAL_ACCESS_H_
