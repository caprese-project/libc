#ifndef CAPRESE_LIBC_INTERNAL_CXX_ISTREAM_BASIC_IOSTREAM_H_
#define CAPRESE_LIBC_INTERNAL_CXX_ISTREAM_BASIC_IOSTREAM_H_

#include <internal/cxx/istream/basic_istream.h>
#include <internal/cxx/ostream/basic_ostream.h>

namespace std {
  template<typename Char, typename Traits>
  class __basic_iostream: public __basic_istream<Char, Traits>, public __basic_ostream<Char, Traits> { };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_ISTREAM_BASIC_IOSTREAM_H_
