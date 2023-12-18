#ifndef CAPRESE_LIBC_INTERNAL_CXX_UTILITY_IN_PLACE_INDEX_H_
#define CAPRESE_LIBC_INTERNAL_CXX_UTILITY_IN_PLACE_INDEX_H_

#include <internal/cxx/stddef.h>

namespace std {
  template<__size_t I>
  struct in_place_index_t {
    explicit in_place_index_t() = default;
  };

  template<__size_t I>
  inline constexpr in_place_index_t<I> in_place_index {};
}; // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_UTILITY_IN_PLACE_INDEX_H_
