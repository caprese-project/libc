#ifndef CAPRESE_LIBC_INTERNAL_CXX_OSTREAM_OPERATOR_H_
#define CAPRESE_LIBC_INTERNAL_CXX_OSTREAM_OPERATOR_H_

#include <internal/branch.h>
#include <internal/cxx/memory/unique_ptr.h>
#include <internal/cxx/ostream/basic_ostream.h>
#include <internal/cxx/string/char_traits.h>

namespace std {
  template<typename Char, typename Traits>
  __basic_ostream<Char, Traits>& operator<<(__basic_ostream<Char, Traits>& stream, Char ch) {
    stream.__insert(&ch, 1);
    return stream;
  }

  template<typename Char, typename Traits>
  __basic_ostream<Char, Traits>& operator<<(__basic_ostream<Char, Traits>& stream, char ch) {
    return stream << stream.widen(ch);
  }

  template<typename Traits>
  __basic_ostream<char, Traits>& operator<<(__basic_ostream<char, Traits>& stream, char ch) {
    stream.__insert(&ch, 1);
    return stream;
  }

  template<typename Traits>
  __basic_ostream<char, Traits>& operator<<(__basic_ostream<char, Traits>& stream, signed char ch) {
    return stream << static_cast<char>(ch);
  }

  template<typename Traits>
  __basic_ostream<char, Traits>& operator<<(__basic_ostream<char, Traits>& stream, unsigned char ch) {
    return stream << static_cast<char>(ch);
  }

  template<typename Char, typename Traits>
  __basic_ostream<Char, Traits>& operator<<(__basic_ostream<Char, Traits>& stream, const Char* str) {
    __if_unlikely (str == nullptr) {
      stream.setstate(ios_base::badbit);
    } else {
      stream.__insert(str, Traits::length(str));
    }
    return stream;
  }

  template<typename Char, typename Traits>
  __basic_ostream<Char, Traits>& operator<<(__basic_ostream<Char, Traits>& stream, const char* str) {
    __if_unlikely (str == nullptr) {
      stream.setstate(ios_base::badbit);
      return stream;
    }

    streamsize n = char_traits<char>::length(str);

    __try {
      unique_ptr<Char[]> ptr = make_unique<Char[]>(n);
      for (streamsize i = 0; i < n; ++i) {
        ptr[i] = stream.widen(str[i]);
      }
      stream->__insert(ptr.get(), n);
    }
    __catch (...) {
      stream.setstate(ios_base::badbit);
    }

    return stream;
  }

  template<typename Traits>
  __basic_ostream<char, Traits>& operator<<(__basic_ostream<char, Traits>& stream, const char* str) {
    __if_unlikely (str == nullptr) {
      stream.setstate(ios_base::badbit);
    } else {
      stream.__insert(str, char_traits<char>::length(str));
    }
    return stream;
  }

  template<typename Traits>
  __basic_ostream<char, Traits>& operator<<(__basic_ostream<char, Traits>& stream, const signed char* str) {
    return stream << reinterpret_cast<const char*>(str);
  }

  template<typename Traits>
  __basic_ostream<char, Traits>& operator<<(__basic_ostream<char, Traits>& stream, const unsigned char* str) {
    return stream << reinterpret_cast<const char*>(str);
  }
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_OSTREAM_OPERATOR_H_
