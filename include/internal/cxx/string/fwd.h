#ifndef CAPRESE_LIBC_INTERNAL_CXX_STRING_FWD_H_
#define CAPRESE_LIBC_INTERNAL_CXX_STRING_FWD_H_

namespace std {
  template<typename Char, typename Traits, typename Allocator>
  class __basic_string;

  template<typename T>
  struct char_traits;

  template<typename T>
  class allocator;

  using string  = __basic_string<char, char_traits<char>, allocator<char>>;
  using wstring = __basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t>>;
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_STRING_FWD_H_
