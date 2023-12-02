#ifndef CAPRESE_LIBC_INTERNAL_CXX_STRING_CHAR_TRAITS_H_
#define CAPRESE_LIBC_INTERNAL_CXX_STRING_CHAR_TRAITS_H_

#include <cstddef>
#include <cstdint>
#include <internal/attribute.h>
#include <iosfwd>

namespace std {
  template<typename T>
  struct __char_traits_types { };

  template<>
  struct __char_traits_types<char> {
    using int_type   = int;
    using off_type   = streamoff;
    using pos_type   = streampos;
    using state_type = mbstate_t;
  };

  template<>
  struct __char_traits_types<wchar_t> {
    using int_type   = wint_t;
    using off_type   = streamoff;
    using pos_type   = wstreampos;
    using state_type = mbstate_t;
  };

  template<>
  struct __char_traits_types<char8_t> {
    using int_type   = unsigned int;
    using off_type   = streamoff;
    using pos_type   = u8streampos;
    using state_type = mbstate_t;
  };

  template<>
  struct __char_traits_types<char16_t> {
    using int_type   = uint_least16_t;
    using off_type   = streamoff;
    using pos_type   = u16streampos;
    using state_type = mbstate_t;
  };

  template<>
  struct __char_traits_types<char32_t> {
    using int_type   = uint_least32_t;
    using off_type   = streamoff;
    using pos_type   = u32streampos;
    using state_type = mbstate_t;
  };

  template<typename T>
  struct char_traits {
    using char_type  = T;
    using int_type   = typename __char_traits_types<T>::int_type;
    using off_type   = typename __char_traits_types<T>::off_type;
    using pos_type   = typename __char_traits_types<T>::pos_type;
    using state_type = typename __char_traits_types<T>::state_type;

    using __const_char_type = const T;

#ifdef __CXX_STD_20__

    using comparison_category = std::strong_ordering;

#endif // __CXX_STD_20__

    static __constexpr_cxx_std_11 void assign(char_type& r, const char_type& a) __noexcept {
      r = a;
    }

    static __constexpr_cxx_std_20 char_type* assign(char_type* s, size_t n, char_type a) __noexcept {
      for (size_t i = 0; i < n; ++i) {
        s[i] = a;
      }
      return s;
    }

    static __constexpr_cxx_std_11 bool eq(const char_type& a, const char_type& b) __noexcept {
      return a == b;
    }

    static __constexpr_cxx_std_11 bool lt(const char_type& a, const char_type& b) __noexcept {
      return a < b;
    }

    static __constexpr_cxx_std_17 int compare(const char_type* a, const char_type* b, size_t n) __noexcept {
      for (size_t i = 0; i < n; ++i) {
        if (lt(a[i], b[i])) {
          return -1;
        } else if (lt(b[i], a[i])) {
          return 1;
        }
      }
      return 0;
    }

    static __constexpr_cxx_std_17 size_t length(const char_type* s) __noexcept {
      size_t i = 0;
      while (!eq(s[i], char_type())) {
        ++i;
      }
      return i;
    }

    static __constexpr_cxx_std_17 __const_char_type* find(const char_type* s, size_t n, const char_type& a) __noexcept {
      for (size_t i = 0; i < n; ++i) {
        if (eq(s[i], a)) {
          return s + i;
        }
      }
      return nullptr;
    }

    static __constexpr_cxx_std_20 char_type* move(char_type* s1, const char_type* s2, size_t n) __noexcept {
      if (n == 0) {
        return s1;
      }

      if (s1 < s2) {
        for (size_t i = 0; i < n; ++i) {
          assign(s1[i], s2[i]);
        }
      } else {
        for (size_t i = n; i > 0; --i) {
          assign(s1[i - 1], s2[i - 1]);
        }
      }

      return s1;
    }

    static __constexpr_cxx_std_20 char_type* copy(char_type* s1, const char_type* s2, size_t n) __noexcept {
      for (size_t i = 0; i < n; ++i) {
        assign(s1[i], s2[i]);
      }
      return s1;
    }

    static __constexpr_cxx_std_11 char_type to_char_type(const int_type& c) __noexcept {
      return static_cast<char_type>(c);
    }

    static __constexpr_cxx_std_11 int_type to_int_type(const char_type& c) __noexcept {
      return static_cast<int_type>(c);
    }

    static __constexpr_cxx_std_11 bool eq_int_type(const int_type& c1, const int_type& c2) __noexcept {
      return c1 == c2;
    }

    static __constexpr_cxx_std_11 int_type eof() __noexcept {
      return static_cast<int_type>(-1);
    }

    static __constexpr_cxx_std_11 int_type not_eof(const int_type& c) __noexcept {
      return !eq_int_type(c, eof()) ? c : to_int_type(char_type());
    }
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_STRING_CHAR_TRAITS_H_
