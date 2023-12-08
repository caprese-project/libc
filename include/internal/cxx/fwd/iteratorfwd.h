#ifndef CAPRESE_LIBC_INTERNAL_CXX_FWD_ITERATORFWD_H_
#define CAPRESE_LIBC_INTERNAL_CXX_FWD_ITERATORFWD_H_

namespace std {
  template<typename Category, typename T, typename Distance, typename Pointer, typename Reference>
  struct iterator;

  template<typename I>
  struct iterator_traits;

  template<typename Iterator, typename Container>
  class __iterator_base;

  template<typename I>
  class reverse_iterator;

  template<typename Char, typename Traits>
  class istreambuf_iterator;

  template<typename Char, typename Traits>
  class ostreambuf_iterator;
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_FWD_ITERATORFWD_H_
