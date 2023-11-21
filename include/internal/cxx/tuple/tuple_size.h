#ifndef CAPRESE_LIBC_INTERNAL_CXX_TUPLE_TUPLE_SIZE_H_
#define CAPRESE_LIBC_INTERNAL_CXX_TUPLE_TUPLE_SIZE_H_

#include <internal/cxx/tuple/tuple.h>
#include <internal/cxx/type_traits/constant.h>

namespace std {
  template<typename T>
  class __tuple_size;

  template<typename T>
  class __tuple_size<const T>;

  template<typename... Tn>
  class __tuple_size<__tuple<Tn...>>: public std::__integral_constant<__size_t, sizeof...(Tn)> { };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_TUPLE_TUPLE_SIZE_H_
