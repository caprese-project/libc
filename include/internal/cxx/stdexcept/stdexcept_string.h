#ifndef CAPRESE_LIBC_INTERNAL_CXX_STDEXCEPT_STDEXCEPT_STRING_H_
#define CAPRESE_LIBC_INTERNAL_CXX_STDEXCEPT_STDEXCEPT_STRING_H_

#include <internal/attribute.h>
#include <internal/cxx/fwd/stringfwd.h>
#include <internal/cxx/stddef.h>

namespace std {
  class __stdexcept_string {
    char*    _data;
    __size_t _size;

  public:
    __stdexcept_string(const char* data);
    __stdexcept_string(const string& data);
    __stdexcept_string(const __stdexcept_string& other);
    __stdexcept_string(__stdexcept_string&& other);
    ~__stdexcept_string() __noexcept;

    const char* c_str() const __noexcept;
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_STDEXCEPT_STDEXCEPT_STRING_H_
