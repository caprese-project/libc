#ifndef CAPRESE_LIBC_INTERNAL_CXX_STRING_IO_H_
#define CAPRESE_LIBC_INTERNAL_CXX_STRING_IO_H_

#include <internal/cxx/istream/basic_istream.h>
#include <internal/cxx/locale/ctype.h>
#include <internal/cxx/locale/facet.h>
#include <internal/cxx/ostream/basic_ostream.h>
#include <internal/cxx/string/basic_string.h>

namespace std {
  template<typename Char, typename Traits, typename Allocator>
  __basic_ostream<Char, Traits>& operator<<(__basic_ostream<Char, Traits>& stream, const __basic_string<Char, Traits, Allocator>& str) {
    stream.__insert(str.data(), str.size());
    return stream;
  }

  template<typename Char, typename Traits, typename Allocator>
  __basic_istream<Char, Traits>& operator>>(__basic_istream<Char, Traits>& stream, __basic_string<Char, Traits, Allocator>& str) {
    size_t            read_count = 0;
    size_t            max_size   = stream.width();
    ios_base::iostate state      = ios_base::goodbit;

    if (max_size == 0) {
      max_size = str.max_size();
    }

    typename __basic_istream<Char, Traits>::sentry sentry(stream, true);

    if (sentry) {
      __try {
        str.erase();

        typename __basic_istream<Char, Traits>::int_type eof = Traits::eof();
        const ctype<Char>&                               ct  = use_facet<ctype<Char>>(stream.getloc());

        typename __basic_istream<Char, Traits>::__streambuf_type* buf = stream.rdbuf();

        typename __basic_istream<Char, Traits>::int_type ch = buf->sgetc();
        while (read_count < max_size && !Traits::eq_int_type(ch, eof) && !ct.is(ctype_base::space, Traits::to_char_type(ch))) {
          str.push_back(Traits::to_char_type(ch));
          ++read_count;
          ch = buf->snextc();
        }

        if (read_count < max_size && Traits::eq_int_type(ch, eof)) {
          state |= ios_base::eofbit;
        }

        stream.width(0);
      }
      __catch (...) {
        stream.setstate(ios_base::badbit);
      }
    }

    __if_unlikely (read_count == 0) {
      state |= ios_base::failbit;
    }

    __if_unlikely (state != ios_base::goodbit) {
      stream.setstate(state);
    }

    return stream;
  }

  template<typename Char, typename Traits, typename Allocator>
  __basic_istream<Char, Traits>& getline(__basic_istream<Char, Traits>& stream, __basic_string<Char, Traits, Allocator>& str, Char delim) {
    size_t            read_count = 0;
    size_t            max_size   = str.max_size();
    ios_base::iostate state      = ios_base::goodbit;

    typename __basic_istream<Char, Traits>::sentry sentry(stream, true);

    if (sentry) {
      __try {
        str.erase();

        typename __basic_istream<Char, Traits>::int_type idelim = Traits::to_int_type(delim);
        typename __basic_istream<Char, Traits>::int_type eof    = Traits::eof();

        typename __basic_istream<Char, Traits>::__streambuf_type* buf = stream.rdbuf();

        typename __basic_istream<Char, Traits>::int_type ch = buf->sgetc();
        while (read_count < max_size && !Traits::eq_int_type(ch, eof) && !Traits::eq_int_type(ch, idelim)) {
          str.push_back(Traits::to_char_type(ch));
          ++read_count;
          ch = buf->snextc();
        }

        if (Traits::eq_int_type(ch, eof)) {
          state |= ios_base::eofbit;
        } else if (Traits::eq_int_type(ch, idelim)) {
          ++read_count;
          buf->sbumpc();
        } else {
          state |= ios_base::failbit;
        }
      }
      __catch (...) {
        stream.setstate(ios_base::badbit);
      }
    }

    __if_unlikely (read_count == 0) {
      state |= ios_base::failbit;
    }

    __if_unlikely (state != ios_base::goodbit) {
      stream.setstate(state);
    }

    return stream;
  }

  template<typename Char, typename Traits, typename Allocator>
  __basic_istream<Char, Traits>& getline(__basic_istream<Char, Traits>& stream, __basic_string<Char, Traits, Allocator>& str) {
    return getline(stream, str, stream.widen('\n'));
  }

#ifdef __CXX_STD_11__

  template<typename Char, typename Traits, typename Allocator>
  __basic_istream<Char, Traits>& getline(__basic_istream<Char, Traits>&& stream, __basic_string<Char, Traits, Allocator>& str, Char delim) {
    return getline(stream, str, delim);
  }

  template<typename Char, typename Traits, typename Allocator>
  __basic_istream<Char, Traits>& getline(__basic_istream<Char, Traits>&& stream, __basic_string<Char, Traits, Allocator>& str) {
    return getline(stream, str);
  }

#endif // __CXX_STD_11__
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_STRING_IO_H_
