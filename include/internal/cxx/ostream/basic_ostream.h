#ifndef CAPRESE_LIBC_INTERNAL_CXX_OSTREAM_BASIC_OSTREAM_H_
#define CAPRESE_LIBC_INTERNAL_CXX_OSTREAM_BASIC_OSTREAM_H_

#include <internal/attribute.h>
#include <internal/cxx/fwd/iteratorfwd.h>
#include <internal/cxx/fwd/localefwd.h>
#include <internal/cxx/ios/basic_ios.h>
#include <internal/cxx/stddef.h>
#include <internal/exception.h>

namespace std {
  template<typename Char, typename Traits>
  class __basic_ostream: virtual public __basic_ios<Char, Traits> {
  public:
    class sentry {
      friend class __basic_ostream;

      bool _ok;

    public:
      explicit sentry(__basic_ostream& os): _ok(false) {
        if (os.good() && os.tie() != nullptr) {
          os.tie()->flush();
        }

        if (os.good()) {
          _ok = true;
        } else {
          os.setstate(ios_base::failbit);
        }
      }

      sentry(const sentry&)            = delete;
      sentry& operator=(const sentry&) = delete;

      ~sentry() { }

      explicit operator bool() const {
        return _ok;
      }
    };

    friend class sentry;

    using __ios_type       = __basic_ios<Char, Traits>;
    using __iterator_type  = ostreambuf_iterator<Char, Traits>;
    using __num_put_type   = num_put<Char, __iterator_type>;
    using __streambuf_type = typename __ios_type::__streambuf_type;

    using char_type   = typename __ios_type::char_type;
    using traits_type = typename __ios_type::traits_type;
    using int_type    = typename __ios_type::int_type;
    using pos_type    = typename __ios_type::pos_type;
    using off_type    = typename __ios_type::off_type;

  private:
    __num_put_type _num_put;

  protected:
    __basic_ostream(const __basic_ostream&) = delete;

    __basic_ostream(__basic_ostream&& other) {
      __ios_type::move(other);
    }

  public:
    explicit __basic_ostream(__streambuf_type* buf) {
      __ios_type::init(buf);
    }

    ~__basic_ostream() { }

    __basic_ostream& operator<<(__basic_ostream& (*pf)(__basic_ostream&)) {
      return pf(*this);
    }

    __basic_ostream& operator<<(__ios_type& (*pf)(__ios_type&)) {
      pf(*this);
      return *this;
    }

    __basic_ostream& operator<<(ios_base& (*pf)(ios_base&)) {
      pf(*this);
      return *this;
    }

    __basic_ostream& operator<<(bool n) {
      return insert(n);
    }

    __basic_ostream& operator<<(signed short n) {
      if (_is_oct() || _is_hex()) {
        return insert<long>(static_cast<unsigned short>(n));
      } else {
        return insert<long>(n);
      }
    }

    __basic_ostream& operator<<(unsigned short n) {
      return insert<unsigned long>(n);
    }

    __basic_ostream& operator<<(signed int n) {
      if (_is_oct() || _is_hex()) {
        return insert<long>(static_cast<unsigned int>(n));
      } else {
        return insert<long>(n);
      }
    }

    __basic_ostream& operator<<(unsigned int n) {
      return insert<unsigned long>(n);
    }

    __basic_ostream& operator<<(signed long n) {
      return insert(n);
    }

    __basic_ostream& operator<<(unsigned long n) {
      return insert(n);
    }

    __basic_ostream& operator<<(signed long long n) {
      return insert(n);
    }

    __basic_ostream& operator<<(unsigned long long n) {
      return insert(n);
    }

    __basic_ostream& operator<<(const void* p) {
      return insert(p);
    }

    __basic_ostream& operator<<(nullptr_t) {
      return *this << "nullptr";
    }

    __basic_ostream& put(char_type ch) {
      sentry sentry(*this);

      if (sentry) {
        ios_base::iostate err = ios_base::goodbit;

        __try {
          if (traits_type::eq_int_type(this->rdbuf()->sputc(ch), traits_type::eof())) {
            setstate(ios_base::badbit);
          }
        }
        __catch (...) {
          // basic_ostream::setstate may throw an exception.
          ios_base::_set_iostate(ios_base::badbit);
        }

        if (err != ios_base::goodbit) {
          setstate(err);
        }
      }

      return *this;
    }

    __basic_ostream& write(const char_type* str, streamsize n) {
      sentry sentry(*this);

      if (sentry) {
        ios_base::iostate err = ios_base::goodbit;

        __try {
          if (this->rdbuf()->sputn(str, n) != n) {
            setstate(ios_base::badbit);
          }
        }
        __catch (...) {
          // basic_ostream::setstate may throw an exception.
          ios_base::_set_iostate(ios_base::badbit);
        }

        if (err != ios_base::goodbit) {
          setstate(err);
        }
      }

      return *this;
    }

    __basic_ostream& flush() {
      ios_base::iostate err = ios_base::goodbit;

      __try {
        if (this->rdbuf()->pubsync() == -1) {
          err |= ios_base::badbit;
        }
      }
      __catch (...) {
        // basic_ostream::setstate may throw an exception.
        ios_base::_set_iostate(ios_base::badbit);
      }

      if (err != ios_base::goodbit) {
        setstate(err);
      }
    }

    pos_type tellp() {
      pos_type result = pos_type(-1);

      __try {
        if (!fail()) {
          result = this->rdbuf()->pubseekoff(0, ios_base::cur, ios_base::out);
        }
      }
      __catch (...) {
        // basic_ostream::setstate may throw an exception.
        ios_base::_set_iostate(ios_base::badbit);
      }

      return result;
    }

    __basic_ostream& seekp(pos_type pos) {
      ios_base::iostate err = ios_base::goodbit;

      __try {
        if (!fail()) {
          if (this->rdbuf()->pubseekpos(pos, ios_base::out) == pos_type(-1)) {
            err |= ios_base::failbit;
          }
        }
      }
      __catch (...) {
        // basic_ostream::setstate may throw an exception.
        ios_base::_set_iostate(ios_base::badbit);
      }

      if (err != ios_base::goodbit) {
        setstate(err);
      }

      return *this;
    }

  private:
    template<typename T>
    __basic_ostream& insert(T n) {
      sentry sentry(*this);

      if (sentry) {
        ios_base::iostate err = ios_base::goodbit;

        __try {
          if (_num_put.put(*this, *this, this->fill(), n).failed()) {
            err |= ios_base::badbit;
          }
        }
        __catch (...) {
          // basic_ostream::setstate may throw an exception.
          ios_base::_set_iostate(ios_base::badbit);
        }

        if (err != ios_base::goodbit) {
          setstate(err);
        }
      }

      return *this;
    }
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_OSTREAM_BASIC_OSTREAM_H_
