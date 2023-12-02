#ifndef CAPRESE_LIBC_INTERNAL_CXX_STDEXCEPT_LOGIC_ERROR_H_
#define CAPRESE_LIBC_INTERNAL_CXX_STDEXCEPT_LOGIC_ERROR_H_

#include <internal/cxx/exception/exception.h>
#include <string>

namespace std {
  class logic_error: public exception {
    string _msg;

  public:
    explicit logic_error(const char* msg);
    explicit logic_error(const string& msg);
    virtual const char* what() const noexcept;
  };

  class domain_error: public logic_error { };

  class invalid_argument: public logic_error { };

  class length_error: public logic_error { };

  class out_of_range: public logic_error { };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_STDEXCEPT_LOGIC_ERROR_H_
