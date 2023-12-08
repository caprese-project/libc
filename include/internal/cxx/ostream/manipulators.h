#ifndef CAPRESE_LIBC_INTERNAL_CXX_OSTREAM_MANIPULATORS_H_
#define CAPRESE_LIBC_INTERNAL_CXX_OSTREAM_MANIPULATORS_H_

#include <internal/cxx/ostream/basic_ostream.h>

namespace std {
  template<typename Char, typename Traits>
  __basic_ostream<Char, Traits>& endl(__basic_ostream<Char, Traits>& os) {
    os.put(os.widen('\n'));
    os.flush();

    return os;
  }

  template<typename Char, typename Traits>
  __basic_ostream<Char, Traits>& ends(__basic_ostream<Char, Traits>& os) {
    os.put(Char());

    return os;
  }

  template<typename Char, typename Traits>
  __basic_ostream<Char, Traits>& flush(__basic_ostream<Char, Traits>& os) {
    os.flush();

    return os;
  }
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_OSTREAM_MANIPULATORS_H_
