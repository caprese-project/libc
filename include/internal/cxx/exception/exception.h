#ifndef CAPRESE_LIBC_INTERNAL_CXX_EXCEPTION_EXCEPTION_H_
#define CAPRESE_LIBC_INTERNAL_CXX_EXCEPTION_EXCEPTION_H_

#include <internal/attribute.h>

namespace std {
  class exception {
  public:
    exception() __noexcept                 = default;
    exception(const exception&)            = default;
    exception(exception&&)                 = default;
    exception& operator=(const exception&) = default;
    exception& operator=(exception&&)      = default;
    virtual ~exception() __noexcept        = default;
    virtual const char* what() const __noexcept;
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_EXCEPTION_EXCEPTION_H_
