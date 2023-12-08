#ifndef CAPRESE_LIBC_INTERNAL_CXX_LIMITS_NUMERIC_LIMITS_H_
#define CAPRESE_LIBC_INTERNAL_CXX_LIMITS_NUMERIC_LIMITS_H_

#include <climits>
#include <internal/attribute.h>

namespace {
  template<typename T>
  class __numeric_limits;

  template<>
  class __numeric_limits<char> {
  public:
    static __constexpr_cxx_std_11 char min() __noexcept {
      return CHAR_MIN;
    }

    static __constexpr_cxx_std_11 char max() __noexcept {
      return CHAR_MAX;
    }

    static __constexpr_cxx_std_11 bool is_signed = CHAR_MIN < 0;
  };

  template<>
  class __numeric_limits<signed char> {
  public:
    static __constexpr_cxx_std_11 signed char min() __noexcept {
      return SCHAR_MIN;
    }

    static __constexpr_cxx_std_11 signed char max() __noexcept {
      return SCHAR_MAX;
    }

    static __constexpr_cxx_std_11 bool is_signed = true;
  };

  template<>
  class __numeric_limits<unsigned char> {
  public:
    static __constexpr_cxx_std_11 unsigned char min() __noexcept {
      return 0;
    }

    static __constexpr_cxx_std_11 unsigned char max() __noexcept {
      return UCHAR_MAX;
    }

    static __constexpr_cxx_std_11 bool is_signed = false;
  };

  template<>
  class __numeric_limits<short> {
  public:
    static __constexpr_cxx_std_11 short min() __noexcept {
      return SHRT_MIN;
    }

    static __constexpr_cxx_std_11 short max() __noexcept {
      return SHRT_MAX;
    }

    static __constexpr_cxx_std_11 bool is_signed = true;
  };

  template<>
  class __numeric_limits<unsigned short> {
  public:
    static __constexpr_cxx_std_11 unsigned short min() __noexcept {
      return 0;
    }

    static __constexpr_cxx_std_11 unsigned short max() __noexcept {
      return USHRT_MAX;
    }

    static __constexpr_cxx_std_11 bool is_signed = false;
  };

  template<>
  class __numeric_limits<int> {
  public:
    static __constexpr_cxx_std_11 int min() __noexcept {
      return INT_MIN;
    }

    static __constexpr_cxx_std_11 int max() __noexcept {
      return INT_MAX;
    }

    static __constexpr_cxx_std_11 bool is_signed = true;
  };

  template<>
  class __numeric_limits<unsigned int> {
  public:
    static __constexpr_cxx_std_11 unsigned int min() __noexcept {
      return 0;
    }

    static __constexpr_cxx_std_11 unsigned int max() __noexcept {
      return UINT_MAX;
    }

    static __constexpr_cxx_std_11 bool is_signed = false;
  };

  template<>
  class __numeric_limits<long> {
  public:
    static __constexpr_cxx_std_11 long min() __noexcept {
      return LONG_MIN;
    }

    static __constexpr_cxx_std_11 long max() __noexcept {
      return LONG_MAX;
    }

    static __constexpr_cxx_std_11 bool is_signed = true;
  };

  template<>
  class __numeric_limits<unsigned long> {
  public:
    static __constexpr_cxx_std_11 unsigned long min() __noexcept {
      return 0;
    }

    static __constexpr_cxx_std_11 unsigned long max() __noexcept {
      return ULONG_MAX;
    }

    static __constexpr_cxx_std_11 bool is_signed = false;
  };

  template<>
  class __numeric_limits<long long> {
  public:
    static __constexpr_cxx_std_11 long long min() __noexcept {
      return LLONG_MIN;
    }

    static __constexpr_cxx_std_11 long long max() __noexcept {
      return LLONG_MAX;
    }

    static __constexpr_cxx_std_11 bool is_signed = true;
  };

  template<>
  class __numeric_limits<unsigned long long> {
  public:
    static __constexpr_cxx_std_11 unsigned long long min() __noexcept {
      return 0;
    }

    static __constexpr_cxx_std_11 unsigned long long max() __noexcept {
      return ULLONG_MAX;
    }

    static __constexpr_cxx_std_11 bool is_signed = false;
  };
} // namespace

#endif // CAPRESE_LIBC_INTERNAL_CXX_LIMITS_NUMERIC_LIMITS_H_
