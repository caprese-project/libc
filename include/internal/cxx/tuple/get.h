#ifndef CAPRESE_LIBC_INTERNAL_CXX_TUPLE_GET_H_
#define CAPRESE_LIBC_INTERNAL_CXX_TUPLE_GET_H_

#include <internal/cxx/tuple/tuple.h>

namespace std {
  template<__size_t Index, typename Head, typename... Tn>
  constexpr Head& __get_helper(__tuple_helper<Index, Head, Tn...>& tuple) noexcept {
    return __tuple_helper<Index, Head, Tn...>::__get_head(tuple);
  }

  template<__size_t Index, typename Head, typename... Tn>
  constexpr const Head& __get_helper(const __tuple_helper<Index, Head, Tn...>& tuple) noexcept {
    return __tuple_helper<Index, Head, Tn...>::__get_head(tuple);
  }

  template<__size_t Index, typename... Tn>
  constexpr decltype(auto) get(__tuple<Tn...>& tuple) {
    return __get_helper<Index>(tuple);
  }
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_TUPLE_GET_H_
