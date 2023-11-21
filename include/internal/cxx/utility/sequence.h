#ifndef CAPRESE_LIBC_INTERNAL_CXX_UTILITY_SEQUENCE_H_
#define CAPRESE_LIBC_INTERNAL_CXX_UTILITY_SEQUENCE_H_

#include <internal/cxx/stddef.h>

namespace std {
  template<typename T, T... Index>
  struct __integer_sequence {
    using value_type = T;

    static constexpr __size_t size() noexcept {
      return sizeof...(Index);
    }
  };

  template<typename T, T N>
  using __make_integer_sequence = __integer_sequence<T, __integer_pack(N)...>;

  template<__size_t... Index>
  using __index_sequence = __integer_sequence<__size_t, Index...>;

  template<__size_t N>
  using __make_index_sequence = __make_integer_sequence<__size_t, N>;

  template<typename... Tn>
  using __index_sequence_for = __make_integer_sequence<__size_t, sizeof...(Tn)>;
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_UTILITY_SEQUENCE_H_
