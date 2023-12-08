#ifndef CAPRESE_LIBC_INTERNAL_CXX_IOS_MANIPULATORS_H_
#define CAPRESE_LIBC_INTERNAL_CXX_IOS_MANIPULATORS_H_

#include <internal/cxx/ios/ios_base.h>

namespace std {
  ios_base& boolalpha(ios_base& str);
  ios_base& noboolalpha(ios_base& str);
  ios_base& showbase(ios_base& str);
  ios_base& noshowbase(ios_base& str);
  ios_base& showpoint(ios_base& str);
  ios_base& noshowpoint(ios_base& str);
  ios_base& showpos(ios_base& str);
  ios_base& noshowpos(ios_base& str);
  ios_base& skipws(ios_base& str);
  ios_base& noskipws(ios_base& str);
  ios_base& uppercase(ios_base& str);
  ios_base& nouppercase(ios_base& str);
  ios_base& unitbuf(ios_base& str);
  ios_base& nounitbuf(ios_base& str);
  ios_base& internal(ios_base& str);
  ios_base& left(ios_base& str);
  ios_base& right(ios_base& str);
  ios_base& dec(ios_base& str);
  ios_base& hex(ios_base& str);
  ios_base& oct(ios_base& str);
  ios_base& fixed(ios_base& str);
  ios_base& scientific(ios_base& str);
  ios_base& hexfloat(ios_base& str);
  ios_base& defaultfloat(ios_base& str);
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_IOS_MANIPULATORS_H_
