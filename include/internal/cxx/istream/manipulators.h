#ifndef CAPRESE_LIBC_INTERNAL_CXX_ISTREAM_MANIPULATORS_H_
#define CAPRESE_LIBC_INTERNAL_CXX_ISTREAM_MANIPULATORS_H_

#include <internal/cxx/istream/basic_istream.h>

namespace std {
  template<typename Char, typename Traits>
  __basic_istream<Char, Traits>& ws(__basic_istream<Char, Traits>& is) {
    decltype(is)::int_type          eof = Traits::eof();
    decltype(is)::__streambuf_type* buf = is.rdbuf();
    decltype(is)::int_type          ch  = buf->sgetc();

    while (!Traits::eq_int_type(ch, eof)) {
      // TODO: use ctype_type
      if (!Traits::eq(Traits::to_char_type(ch), Char(' '))) {
        break;
      }

      ch = buf->snextc();
    }

    if (Traits::eq_int_type(ch, eof)) {
      is.setstate(ios_base::eofbit);
    }

    return is;
  }
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_ISTREAM_MANIPULATORS_H_
