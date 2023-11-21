#ifndef CAPRESE_LIBC_INTERNAL_CXX_TUPLE_GET_H_
#define CAPRESE_LIBC_INTERNAL_CXX_TUPLE_GET_H_

#include <internal/cxx/tuple/tuple.h>

namespace std {
  template<__size_t Index, typename... Tn>
  constexpr decltype(auto) get(__tuple<Tn...>& tuple) {
    return __tuple_helper<Index, Tn...>::__get_head(tuple);
  }
}

#endif // CAPRESE_LIBC_INTERNAL_CXX_TUPLE_GET_H_
