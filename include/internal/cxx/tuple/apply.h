#ifndef CAPRESE_LIBC_INTERNAL_CXX_TUPLE_APPLY_H_
#define CAPRESE_LIBC_INTERNAL_CXX_TUPLE_APPLY_H_

#include <internal/cxx/tuple/get.h>
#include <internal/cxx/tuple/tuple.h>
#include <internal/cxx/type_traits/modify.h>
#include <internal/cxx/utility/sequence.h>

namespace std {
  template<typename Fn, typename Tuple, __size_t... Index>
  constexpr decltype(auto) __apply_helper(Fn&& fn, Tuple&& tuple, __index_sequence<Index...>) {
    return fn(__get<Index>(std::forward<Tuple>(tuple)...));
  }

  template<typename Fn, typename Tuple>
  constexpr decltype(auto) apply(Fn&& fn, Tuple&& tuple) noexcept {
    return __apply_helper(std::forward<Fn>(fn), std::forward<Tuple>(tuple), __make_index_sequence<typename __tuple_size<typename __remove_reference<Tuple>::type>::value>());
  }
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_TUPLE_APPLY_H_
