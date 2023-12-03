#ifndef CAPRESE_LIBC_INTERNAL_CXX_NEW_BAD_ALLOC_H_
#define CAPRESE_LIBC_INTERNAL_CXX_NEW_BAD_ALLOC_H_

#include <exception>
#include <internal/attribute.h>

namespace std {
  class bad_alloc: public exception {
  public:
    bad_alloc() __noexcept          = default;
    virtual ~bad_alloc() __noexcept = default;
    virtual const char* what() const __noexcept;
  };

  class bad_array_new_length: public bad_alloc {
  public:
    bad_array_new_length() __noexcept          = default;
    virtual ~bad_array_new_length() __noexcept = default;
    virtual const char* what() const __noexcept;
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_NEW_BAD_ALLOC_H_
