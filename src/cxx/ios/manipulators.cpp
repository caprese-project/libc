#include <internal/cxx/ios/manipulators.h>

namespace std {
  ios_base& boolalpha(ios_base& str) {
    str.setf(ios_base::boolalpha);
    return str;
  }

  ios_base& noboolalpha(ios_base& str) {
    str.unsetf(ios_base::boolalpha);
    return str;
  }

  ios_base& showbase(ios_base& str) {
    str.setf(ios_base::showbase);
    return str;
  }

  ios_base& noshowbase(ios_base& str) {
    str.unsetf(ios_base::showbase);
    return str;
  }

  ios_base& showpoint(ios_base& str) {
    str.setf(ios_base::showpoint);
    return str;
  }

  ios_base& noshowpoint(ios_base& str) {
    str.unsetf(ios_base::showpoint);
    return str;
  }

  ios_base& showpos(ios_base& str) {
    str.setf(ios_base::showpos);
    return str;
  }

  ios_base& noshowpos(ios_base& str) {
    str.unsetf(ios_base::showpos);
    return str;
  }

  ios_base& skipws(ios_base& str) {
    str.setf(ios_base::skipws);
    return str;
  }

  ios_base& noskipws(ios_base& str) {
    str.unsetf(ios_base::skipws);
    return str;
  }

  ios_base& uppercase(ios_base& str) {
    str.setf(ios_base::uppercase);
    return str;
  }

  ios_base& nouppercase(ios_base& str) {
    str.unsetf(ios_base::uppercase);
    return str;
  }

  ios_base& unitbuf(ios_base& str) {
    str.setf(ios_base::unitbuf);
    return str;
  }

  ios_base& nounitbuf(ios_base& str) {
    str.unsetf(ios_base::unitbuf);
    return str;
  }

  ios_base& internal(ios_base& str) {
    str.setf(ios_base::internal);
    return str;
  }

  ios_base& left(ios_base& str) {
    str.setf(ios_base::left);
    return str;
  }

  ios_base& right(ios_base& str) {
    str.setf(ios_base::right);
    return str;
  }

  ios_base& dec(ios_base& str) {
    str.setf(ios_base::dec);
    return str;
  }

  ios_base& hex(ios_base& str) {
    str.setf(ios_base::hex);
    return str;
  }

  ios_base& oct(ios_base& str) {
    str.setf(ios_base::oct);
    return str;
  }

  ios_base& fixed(ios_base& str) {
    str.setf(ios_base::fixed);
    return str;
  }

  ios_base& scientific(ios_base& str) {
    str.setf(ios_base::scientific);
    return str;
  }

  ios_base& hexfloat(ios_base& str) {
    str.setf(ios_base::fixed | ios_base::scientific, ios_base::floatfield);
    return str;
  }

  ios_base& defaultfloat(ios_base& str) {
    str.unsetf(ios_base::floatfield);
    return str;
  }
} // namespace std
