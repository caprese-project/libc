#ifndef CAPRESE_LIBC_INTERNAL_CXX_FWD_LOCALEFWD_H_
#define CAPRESE_LIBC_INTERNAL_CXX_FWD_LOCALEFWD_H_

namespace std {
  class locale;

  template<typename Char, typename InputIterator>
  class num_get;

  template<typename Char, typename OutputIterator>
  class num_put;

  class ctype_base;

  template<typename Char>
  class ctype;
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_FWD_LOCALEFWD_H_
