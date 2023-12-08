#ifndef CAPRESE_LIBC_INTERNAL_CXX_SYSTEM_ERROR_ERROR_CATEGORY_H_
#define CAPRESE_LIBC_INTERNAL_CXX_SYSTEM_ERROR_ERROR_CATEGORY_H_

#include <compare>
#include <internal/attribute.h>
#include <internal/cxx/system_error/error_code.h>
#include <internal/cxx/system_error/error_condition.h>
#include <internal/version.h>
#include <string>

namespace std {
  class error_category {
  public:
    __constexpr_cxx_std_14 error_category() __noexcept = default;
    error_category(const error_category&)              = delete;
    error_category(error_category&&)                   = delete;
    error_category& operator=(const error_category&)   = delete;
    error_category& operator=(error_category&&)        = delete;
    virtual ~error_category()                          = default;

    bool operator==(const error_category& rhs) const __noexcept;
    bool operator!=(const error_category& rhs) const __noexcept;
    bool operator<(const error_category& rhs) const noexcept;

#ifdef __CXX_STD_20__
    strong_ordering operator<=>(const error_category& rhs) const noexcept;
#endif // __CXX_STD_20__

    virtual error_condition default_error_condition(int code) const __noexcept;

    virtual bool equivalent(int code, const error_condition& condition) const __noexcept;
    virtual bool equivalent(const error_code& code, int condition) const __noexcept;

    virtual const char* name() const __noexcept = 0;
    virtual string      message(int code) const = 0;
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_SYSTEM_ERROR_ERROR_CATEGORY_H_
