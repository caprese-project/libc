#ifndef CAPRESE_LIBC_INTERNAL_CXX_STDEXCEPT_RUNTIME_ERROR_H_
#define CAPRESE_LIBC_INTERNAL_CXX_STDEXCEPT_RUNTIME_ERROR_H_

#include <internal/cxx/exception/exception.h>
#include <internal/cxx/stdexcept/stdexcept_string.h>

namespace std {
  class runtime_error: public exception {
    __stdexcept_string _msg;

  public:
    explicit runtime_error(const char* msg);
    explicit runtime_error(const string& msg);
    virtual const char* what() const __noexcept;
  };

  class range_error: public exception { };

  class overflow_error: public exception { };

  class underflow_error: public exception { };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_STDEXCEPT_RUNTIME_ERROR_H_
