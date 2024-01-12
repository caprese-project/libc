#ifndef CAPRESE_LIBC_INTERNAL_CXX_UTILITY_IN_PLACE_H_
#define CAPRESE_LIBC_INTERNAL_CXX_UTILITY_IN_PLACE_H_

namespace std {
  struct in_place_t {
    explicit in_place_t() = default;
  };

  inline constexpr in_place_t in_place {};
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_UTILITY_IN_PLACE_H_
