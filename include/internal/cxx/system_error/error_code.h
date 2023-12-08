#ifndef CAPRESE_LIBC_INTERNAL_CXX_SYSTEM_ERROR_ERROR_CODE_H_
#define CAPRESE_LIBC_INTERNAL_CXX_SYSTEM_ERROR_ERROR_CODE_H_

#include <internal/cxx/system_error/errc.h>
#include <internal/cxx/system_error/error_category.h>

namespace std {
  class error_code {
    int             _code;
    error_category* _category;

  public:
    error_code() noexcept;
    error_code(int code, error_category& category) noexcept;
    error_code(const error_code&) noexcept;
    error_code(error_code&&) noexcept;
    ~error_code() noexcept;
    error_code&           operator=(const error_code&) noexcept;
    error_code&           operator=(error_code&&) noexcept;
    int                   value() const noexcept;
    const error_category& category() const noexcept;
    const char*           message() const noexcept;
  };

  error_code make_error_code(errc e) noexcept;
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_SYSTEM_ERROR_ERROR_CODE_H_
