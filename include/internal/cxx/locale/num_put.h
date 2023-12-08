#ifndef CAPRESE_LIBC_INTERNAL_CXX_LOCALE_NUM_PUT_H_
#define CAPRESE_LIBC_INTERNAL_CXX_LOCALE_NUM_PUT_H_

#include <internal/cxx/algorithm/seq.h>
#include <internal/cxx/fwd/iteratorfwd.h>
#include <internal/cxx/fwd/stringfwd.h>
#include <internal/cxx/iterator/functions.h>
#include <internal/cxx/limits/numeric_limits.h>
#include <internal/cxx/locale/locale.h>
#include <internal/cxx/stddef.h>

namespace std {
  template<typename Char, typename OutputIterator = ostreambuf_iterator<Char, char_traits<Char>>>
  class num_put: locale::facet {
  public:
    using char_type = Char;
    using iter_type = OutputIterator;

  public:
    static locale::id id;

  protected:
    virtual ~num_put() { }

    template<typename T>
    streamsize itoa(char_type* buf, T value, ios_base& ios) {
      __constexpr const char* digits = "0123456789abcdef";

      char_type* ptr = buf;
      if (ios._is_dec()) {
        do {
          *--ptr = digits[value % 10];
          value /= 10;
        } while (value != 0);
      } else if (ios._is_oct()) {
        do {
          *--ptr = digits[value & 0b111];
          value >>= 3;
        } while (value != 0);
      } else {
        do {
          *--ptr = digits[value & 0b1111];
          value >>= 4;
        } while (value != 0);
      }

      return buf - ptr;
    }

    template<typename T>
    iter_type put_int(iter_type it, ios_base& ios, char_type fill, T value) const {
      char_type buf[32];

      streamsize size = itoa(buf, value, ios);
      buf += std::size(buf) - size;

      if (ios._is_dec()) {
        if (value >= 0) {
          if (ios._is_showpos() && __numeric_limits<T>::is_signed) {
            *--buf = '+';
            ++size;
          }
        } else {
          *--buf = '-';
          ++size;
        }
      } else if (ios._is_showbase() && value != 0) {
        if (ios._is_oct()) {
          *--buf = '0';
          ++size;
        } else {
          if (ios._is_uppercase()) {
            *--buf = 'X';
          } else {
            *--buf = 'x';
          }
          *--buf = '0';
          size += 2;
        }
      }

      streamsize width = ios.width();
      if (width > size) {
        streamsize fill_len = width - size;
        if (ios._is_left()) {
          it = copy_n(buf, size, it);
          it = fill_n(it, fill_len, fill);
        } else {
          it = fill_n(it, fill_len, fill);
          it = copy_n(buf, size, it);
        }
      } else {
        copy_n(buf, size, it);
      }

      ios.width(0);
      return it;
    }

    virtual iter_type do_put(iter_type it, ios_base& ios, char_type fill, bool value) const {
      if (ios._is_boolalpha()) {
        const char_type* val;
        streamsize       size;
        if (value) {
          val  = "true";
          size = 4;
        } else {
          val  = "false";
          size = 5;
        }

        streamsize width = ios.width();
        if (width > size) {
          streamsize fill_len = width - size;
          if (ios._is_left()) {
            it = copy_n(val, size, it);
            it = fill_n(it, fill_len, fill);
          } else {
            it = fill_n(it, fill_len, fill);
            it = copy_n(val, size, it);
          }
        } else {
          copy_n(val, size, it);
        }
      } else {
        it = put_int(it, ios, fill, static_cast<long>(value));
      }

      ios.width(0);
      return it;
    }

    virtual iter_type do_put(iter_type it, ios_base& ios, char_type fill, signed long value) const {
      return put_int(it, ios, fill, value);
    }

    virtual iter_type do_put(iter_type it, ios_base& ios, char_type fill, unsigned long value) const {
      return put_int(it, ios, fill, value);
    }

    virtual iter_type do_put(iter_type it, ios_base& ios, char_type fill, signed long long value) const {
      return put_int(it, ios, fill, value);
    }

    virtual iter_type do_put(iter_type it, ios_base& ios, char_type fill, unsigned long long value) const {
      return put_int(it, ios, fill, value);
    }

    virtual iter_type do_put(iter_type it, ios_base& ios, char_type fill, const void* value) const {
      const ios_base::fmtflags old_flags = ios.flags();
      const ios_base::fmtflags new_flags = (old_flags & ~(ios_base::basefield | ios_base::uppercase)) | ios_base::hex | ios_base::showbase;

      ios.flags(new_flags);
      it = put_int(it, ios, fill, reinterpret_cast<unsigned long long>(value));
      ios.flags(old_flags);
      return it;
    }

  public:
    explicit num_put(__size_t refs = 0): facet(refs) { }

    iter_type put(iter_type it, ios_base& ios, char_type fill, bool value) const {
      return do_put(it, ios, fill, value);
    }

    iter_type put(iter_type it, ios_base& ios, char_type fill, signed long value) const {
      return do_put(it, ios, fill, value);
    }

    iter_type put(iter_type it, ios_base& ios, char_type fill, unsigned long value) const {
      return do_put(it, ios, fill, value);
    }

    iter_type put(iter_type it, ios_base& ios, char_type fill, signed long long value) const {
      return do_put(it, ios, fill, value);
    }

    iter_type put(iter_type it, ios_base& ios, char_type fill, unsigned long long value) const {
      return do_put(it, ios, fill, value);
    }

    iter_type put(iter_type it, ios_base& ios, char_type fill, const void* value) const {
      return do_put(it, ios, fill, value);
    }
  };

  template<typename Char, typename OutputIterator>
  locale::id num_put<Char, OutputIterator>::id;
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_LOCALE_NUM_PUT_H_
