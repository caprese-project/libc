#ifndef CAPRESE_LIBC_INTERNAL_CXX_TUPLE_TIE_H_
#define CAPRESE_LIBC_INTERNAL_CXX_TUPLE_TIE_H_

#include <internal/cxx/tuple/tuple.h>

namespace std {
  template<typename... Tn>
  __constexpr_cxx_std_14 __tuple<Tn&...> tie(Tn&... args) noexcept {
    return __tuple<Tn&...>(args...);
  }
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_TUPLE_TIE_H_
