#ifndef CAPRESE_LIBC_INTERNAL_CXX_FWD_STRINGFWD_H_
#define CAPRESE_LIBC_INTERNAL_CXX_FWD_STRINGFWD_H_

#include <internal/cxx/fwd/memoryfwd.h>

namespace std {
  template<typename T>
  struct char_traits;

  template<typename Char, typename Traits, typename Allocator>
  class __basic_string;

  template<typename Char, typename Traits = char_traits<Char>, typename Allocator = allocator<Char>>
  using basic_string = __basic_string<Char, Traits, Allocator>;

  using string  = basic_string<char>;
  using wstring = basic_string<wchar_t>;
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_FWD_STRINGFWD_H_
