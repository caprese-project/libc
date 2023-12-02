#ifndef CAPRESE_INTERNAL_CXX_TYPE_TRAITS_SIGN_H_
#define CAPRESE_INTERNAL_CXX_TYPE_TRAITS_SIGN_H_

#include <internal/cxx/type_traits/type.h>

namespace std {
  template<typename T>
  struct __make_signed;

  template<>
  struct __make_signed<char> {
    using type = signed char;
  };

  template<>
  struct __make_signed<signed char> {
    using type = signed char;
  };

  template<>
  struct __make_signed<unsigned char> {
    using type = signed char;
  };

  template<>
  struct __make_signed<short> {
    using type = signed short;
  };

  template<>
  struct __make_signed<unsigned short> {
    using type = signed short;
  };

  template<>
  struct __make_signed<int> {
    using type = signed int;
  };

  template<>
  struct __make_signed<unsigned int> {
    using type = signed int;
  };

  template<>
  struct __make_signed<long> {
    using type = signed long;
  };

  template<>
  struct __make_signed<unsigned long> {
    using type = signed long;
  };

  template<>
  struct __make_signed<long long> {
    using type = signed long long;
  };

  template<>
  struct __make_signed<unsigned long long> {
    using type = signed long long;
  };

  template<typename T>
  struct __make_unsigned;

  template<>
  struct __make_unsigned<char> {
    using type = unsigned char;
  };

  template<>
  struct __make_unsigned<signed char> {
    using type = unsigned char;
  };

  template<>
  struct __make_unsigned<unsigned char> {
    using type = unsigned char;
  };

  template<>
  struct __make_unsigned<short> {
    using type = unsigned short;
  };

  template<>
  struct __make_unsigned<unsigned short> {
    using type = unsigned short;
  };

  template<>
  struct __make_unsigned<int> {
    using type = unsigned int;
  };

  template<>
  struct __make_unsigned<unsigned int> {
    using type = unsigned int;
  };

  template<>
  struct __make_unsigned<long> {
    using type = unsigned long;
  };

  template<>
  struct __make_unsigned<unsigned long> {
    using type = unsigned long;
  };

  template<>
  struct __make_unsigned<long long> {
    using type = unsigned long long;
  };

  template<>
  struct __make_unsigned<unsigned long long> {
    using type = unsigned long long;
  };
} // namespace std

#endif // CAPRESE_INTERNAL_CXX_TYPE_TRAITS_SIGN_H_
