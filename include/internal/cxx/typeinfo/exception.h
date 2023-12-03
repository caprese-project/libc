#ifndef CAPRESE_LIBC_INTERNAL_CXX_TYPEINFO_EXCEPTION_H_
#define CAPRESE_LIBC_INTERNAL_CXX_TYPEINFO_EXCEPTION_H_

#include <internal/cxx/exception/exception.h>

namespace std {
  class bad_cast: public exception {
  public:
    bad_cast() __noexcept          = default;
    virtual ~bad_cast() __noexcept = default;
    virtual const char* what() const __noexcept;
  };

  class bad_typeid: public exception {
  public:
    bad_typeid() __noexcept          = default;
    virtual ~bad_typeid() __noexcept = default;
    virtual const char* what() const __noexcept;
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_TYPEINFO_EXCEPTION_H_
