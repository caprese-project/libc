#ifndef CAPRESE_LIBC_INTERNAL_CXX_STRING_VIEW_IO_H_
#define CAPRESE_LIBC_INTERNAL_CXX_STRING_VIEW_IO_H_

#include <internal/cxx/istream/basic_istream.h>
#include <internal/cxx/string_view/basic_string_view.h>

namespace std {
  template<typename Char, typename Traits>
  __basic_ostream<Char, Traits>& operator<<(__basic_ostream<Char, Traits>& stream, const basic_string_view<Char, Traits>& str) {
    stream.__insert(str.data(), str.size());
    return stream;
  }
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_STRING_VIEW_IO_H_
