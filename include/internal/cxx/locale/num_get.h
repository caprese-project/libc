#ifndef CAPRESE_LIBC_INTERNAL_CXX_LOCALE_NUM_GET_H_
#define CAPRESE_LIBC_INTERNAL_CXX_LOCALE_NUM_GET_H_

#include <internal/cxx/iterator/fwd.h>
#include <internal/cxx/limits/numeric_limits.h>
#include <internal/cxx/locale/locale.h>
#include <internal/cxx/string/fwd.h>
#include <internal/cxx/type_traits/sign.h>

namespace std {
  template<typename Char, typename InputIterator = istreambuf_iterator<Char, char_traits<Char>>>
  class num_get: public locale::facet {
  public:
    using char_type = Char;
    using iter_type = InputIterator;

  public:
    static locale::id id;

  protected:
    virtual ~num_get() { }

    template<typename T>
    int get_digit(int base, T ch) const {
      int result = -1;

      if (base <= 10) {
        if (ch >= T('0') && ch <= T('9')) {
          result = ch - T('0');
        }
      } else {
        if (ch >= T('0') && ch <= T('9')) {
          result = ch - T('0');
        } else if (ch >= T('a') && ch <= T('f')) {
          result = ch - T('a') + 10;
        } else if (ch >= T('A') && ch <= T('F')) {
          result = ch - T('A') + 10;
        }
      }

      return result;
    }

    template<typename T>
    iter_type get_int(iter_type it, iter_type end, ios_base& ios, ios_base::iostate& err, T& value) const {
      typename __make_unsigned<T>::type result = 0;

      bool      eof = it == end;
      char_type ch;

      int base = 10;
      if (ios._is_oct()) {
        base = 8;
      } else if (ios._is_hex()) {
        base = 16;
      }

      bool negative = false;
      if (!eof) {
        ch = *it;

        if (ch == '-') {
          negative = true;
          ++it;
        } else if (ch == '+') {
          ++it;
        }

        if (it != end) {
          ch = *it;
        } else {
          eof = true;
        }
      }

      bool found_zero = false;
      int  pos        = 0;
      while (!eof) {
        if (ch == '0' && (!found_zero || base == 10)) {
          found_zero = true;
          if (ios._is_basefield_unset()) {
            base = 8;
          }
          if (base == 8) {
            pos = 0;
          }
        } else if (found_zero && (ch == 'x' || ch == 'X')) {
          if (ios._is_basefield_unset()) {
            base = 16;
          }
          if (base == 16) {
            found_zero = false;
            pos        = 0;
          } else {
            break;
          }
        } else {
          break;
        }

        ++it;
        if (it != end) {
          ch = *it;
          if (!found_zero) {
            break;
          }
        } else {
          eof = true;
        }
      }

      typename __make_unsigned<T>::type max;
      if (negative && __numeric_limits<T>::is_signed) {
        max = -__numeric_limits<T>::min();
      } else {
        max = __numeric_limits<T>::max();
      }

      const typename __make_unsigned<T>::type smax = max / base;

      bool overflow = false;
      while (!eof) {
        int digit = get_digit(base, ch);
        if (digit == -1) {
          break;
        }

        if (result > smax) {
          overflow = true;
        } else {
          result *= base;
          if (result > max - digit) {
            overflow = true;
          } else {
            result += digit;
          }
          ++pos;
        }

        ++it;
        if (it != end) {
          ch = *it;
        } else {
          eof = true;
        }
      }

      if (pos == 0 && !found_zero) {
        value = 0;
        err   = ios_base::failbit;
      } else if (overflow) {
        if (negative && __numeric_limits<T>::is_signed) {
          value = __numeric_limits<T>::min();
        } else {
          value = __numeric_limits<T>::max();
        }
        err = ios_base::failbit;
      } else {
        value = negative ? -result : result;
      }

      if (eof) {
        err |= ios_base::eofbit;
      }

      return it;
    }

    virtual iter_type do_get(iter_type it, iter_type end, ios_base& ios, ios_base::iostate& err, bool& value) const {
      if (ios._is_boolalpha()) {
        bool       t = true;
        bool       f = true;
        streamsize n = 0;

        while (it != end && (t || f)) {
          const char_type ch = *it;

          if (t) {
            if (n < 4) {
              t = ch == "true"[n];
              if (n == 3) {
                break;
              }
            } else {
              t = false;
            }
          }

          if (f) {
            if (n < 5) {
              f = ch == "false"[n];
              if (n == 4) {
                break;
              }
            } else {
              f = false;
            }
          }

          ++n;
        }

        if (t && n == 3) {
          value = true;
          err   = it == end ? ios_base::eofbit : ios_base::goodbit;
        } else if (f && n == 4) {
          value = false;
          err   = it == end ? ios_base::eofbit : ios_base::goodbit;
        } else {
          value = false;
          err   = ios_base::failbit;
          if (it == end) {
            err |= ios_base::eofbit;
          }
        }
      } else {
        long result = -1;
        it          = get_int(it, end, ios, err, result);
        if (result == 0 || result == 1) {
          value = static_cast<bool>(result);
        } else {
          value = true;
          err   = ios_base::failbit;
          if (it == end) {
            err |= ios_base::eofbit;
          }
        }
      }

      return it;
    }

    virtual iter_type do_get(iter_type it, iter_type end, ios_base& ios, ios_base::iostate& err, unsigned short& value) const {
      return get_int(it, end, ios, err, value);
    }

    virtual iter_type do_get(iter_type it, iter_type end, ios_base& ios, ios_base::iostate& err, unsigned int& value) const {
      return get_int(it, end, ios, err, value);
    }

    virtual iter_type do_get(iter_type it, iter_type end, ios_base& ios, ios_base::iostate& err, signed long& value) const {
      return get_int(it, end, ios, err, value);
    }

    virtual iter_type do_get(iter_type it, iter_type end, ios_base& ios, ios_base::iostate& err, unsigned long& value) const {
      return get_int(it, end, ios, err, value);
    }

    virtual iter_type do_get(iter_type it, iter_type end, ios_base& ios, ios_base::iostate& err, signed long long& value) const {
      return get_int(it, end, ios, err, value);
    }

    virtual iter_type do_get(iter_type it, iter_type end, ios_base& ios, ios_base::iostate& err, unsigned long long& value) const {
      return get_int(it, end, ios, err, value);
    }

    virtual iter_type do_get(iter_type it, iter_type end, ios_base& ios, ios_base::iostate& err, void*& value) const {
      const ios_base::fmtflags old_flags = ios.flags();
      const ios_base::fmtflags new_flags = (old_flags & ~(ios_base::basefield)) | ios_base::hex;

      uintptr_t result;

      ios.flags(new_flags);
      it = get_int(it, end, ios, err, result);
      ios.flags(old_flags);

      value = reinterpret_cast<void*>(result);

      return it;
    }

  public:
    explicit num_get(size_t refs = 0): locale::facet(refs) { }

    iter_type get(iter_type it, iter_type end, ios_base& ios, ios_base::iostate& err, bool& value) const {
      return do_get(it, end, ios, err, value);
    }

    iter_type get(iter_type it, iter_type end, ios_base& ios, ios_base::iostate& err, unsigned short& value) const {
      return do_get(it, end, ios, err, value);
    }

    iter_type get(iter_type it, iter_type end, ios_base& ios, ios_base::iostate& err, unsigned int& value) const {
      return do_get(it, end, ios, err, value);
    }

    iter_type get(iter_type it, iter_type end, ios_base& ios, ios_base::iostate& err, signed long& value) const {
      return do_get(it, end, ios, err, value);
    }

    iter_type get(iter_type it, iter_type end, ios_base& ios, ios_base::iostate& err, unsigned long& value) const {
      return do_get(it, end, ios, err, value);
    }

    iter_type get(iter_type it, iter_type end, ios_base& ios, ios_base::iostate& err, signed long long& value) const {
      return do_get(it, end, ios, err, value);
    }

    iter_type get(iter_type it, iter_type end, ios_base& ios, ios_base::iostate& err, unsigned long long& value) const {
      return do_get(it, end, ios, err, value);
    }

    iter_type get(iter_type it, iter_type end, ios_base& ios, ios_base::iostate& err, void*& value) const {
      return do_get(it, end, ios, err, value);
    }
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_LOCALE_NUM_GET_H_
