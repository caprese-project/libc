#ifndef CAPRESE_LIBC_INTERNAL_CXX_LIMITS_NUMERIC_LIMITS_H_
#define CAPRESE_LIBC_INTERNAL_CXX_LIMITS_NUMERIC_LIMITS_H_

#include <climits>
#include <internal/attribute.h>

namespace {
  template<typename T>
  class __numeric_limits;

  template<>
  class __numeric_limits<char> {
    static __constexpr_cxx_std_11 char min() __noexcept {
      return CHAR_MIN;
    }

    static __constexpr_cxx_std_11 char max() __noexcept {
      return CHAR_MAX;
    }
  };

  template<>
  class __numeric_limits<signed char> {
    static __constexpr_cxx_std_11 signed char min() __noexcept {
      return SCHAR_MIN;
    }

    static __constexpr_cxx_std_11 signed char max() __noexcept {
      return SCHAR_MAX;
    }
  };

  template<>
  class __numeric_limits<unsigned char> {
    static __constexpr_cxx_std_11 unsigned char min() __noexcept {
      return 0;
    }

    static __constexpr_cxx_std_11 unsigned char max() __noexcept {
      return UCHAR_MAX;
    }
  };

  template<>
  class __numeric_limits<short> {
    static __constexpr_cxx_std_11 short min() __noexcept {
      return SHRT_MIN;
    }

    static __constexpr_cxx_std_11 short max() __noexcept {
      return SHRT_MAX;
    }
  };

  template<>
  class __numeric_limits<unsigned short> {
    static __constexpr_cxx_std_11 unsigned short min() __noexcept {
      return 0;
    }

    static __constexpr_cxx_std_11 unsigned short max() __noexcept {
      return USHRT_MAX;
    }
  };

  template<>
  class __numeric_limits<int> {
    static __constexpr_cxx_std_11 int min() __noexcept {
      return INT_MIN;
    }

    static __constexpr_cxx_std_11 int max() __noexcept {
      return INT_MAX;
    }
  };

  template<>
  class __numeric_limits<unsigned int> {
    static __constexpr_cxx_std_11 unsigned int min() __noexcept {
      return 0;
    }

    static __constexpr_cxx_std_11 unsigned int max() __noexcept {
      return UINT_MAX;
    }
  };

  template<>
  class __numeric_limits<long> {
    static __constexpr_cxx_std_11 long min() __noexcept {
      return LONG_MIN;
    }

    static __constexpr_cxx_std_11 long max() __noexcept {
      return LONG_MAX;
    }
  };

  template<>
  class __numeric_limits<unsigned long> {
    static __constexpr_cxx_std_11 unsigned long min() __noexcept {
      return 0;
    }

    static __constexpr_cxx_std_11 unsigned long max() __noexcept {
      return ULONG_MAX;
    }
  };

  template<>
  class __numeric_limits<long long> {
    static __constexpr_cxx_std_11 long long min() __noexcept {
      return LLONG_MIN;
    }

    static __constexpr_cxx_std_11 long long max() __noexcept {
      return LLONG_MAX;
    }
  };

  template<>
  class __numeric_limits<unsigned long long> {
    static __constexpr_cxx_std_11 unsigned long long min() __noexcept {
      return 0;
    }

    static __constexpr_cxx_std_11 unsigned long long max() __noexcept {
      return ULLONG_MAX;
    }
  };
} // namespace

#endif // CAPRESE_LIBC_INTERNAL_CXX_LIMITS_NUMERIC_LIMITS_H_
