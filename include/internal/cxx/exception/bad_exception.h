#ifndef CAPRESE_LIBC_INTERNAL_CXX_EXCEPTION_BAD_EXCEPTION_H_
#define CAPRESE_LIBC_INTERNAL_CXX_EXCEPTION_BAD_EXCEPTION_H_

#include <internal/attribute.h>
#include <internal/cxx/exception/exception.h>

namespace std {
  class bad_exception: public exception {
  public:
    bad_exception() __noexcept          = default;
    virtual ~bad_exception() __noexcept = default;
    virtual const char* what() const __noexcept;
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_EXCEPTION_BAD_EXCEPTION_H_
