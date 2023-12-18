#ifndef CAPRESE_LIBC_INTERNAL_CXX_VARIANT_MONOSTATE_H_
#define CAPRESE_LIBC_INTERNAL_CXX_VARIANT_MONOSTATE_H_

#include <compare>
#include <internal/attribute.h>

namespace std {
  struct monostate {
    monostate()                            = default;
    ~monostate()                           = default;
    monostate& operator=(const monostate&) = default;
    monostate& operator=(monostate&&)      = default;
  };

  __constexpr bool operator==(const monostate&, const monostate&) __noexcept {
    return true;
  }

#ifdef __CXX_STD_20__

  constexpr strong_ordering operator<=>(const monostate&, const monostate&) noexcept {
    return strong_ordering::equal;
  }

#else // ^^^ __CXX_STD_20__ ^^^ / vvv !__CXX_STD_20__ vvv

  __constexpr bool operator!=(const monostate&, const monostate&) __noexcept {
    return false;
  }

  __constexpr bool operator<(const monostate&, const monostate&) __noexcept {
    return false;
  }

  __constexpr bool operator<=(const monostate&, const monostate&) __noexcept {
    return true;
  }

  __constexpr bool operator>(const monostate&, const monostate&) __noexcept {
    return false;
  }

  __constexpr bool operator>=(const monostate&, const monostate&) __noexcept {
    return true;
  }

#endif // !__CXX_STD_20__
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_VARIANT_MONOSTATE_H_
