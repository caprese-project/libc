#ifndef CAPRESE_LIBC_INTERNAL_CXX_ISTREAM_BASIC_ISTREAM_H_
#define CAPRESE_LIBC_INTERNAL_CXX_ISTREAM_BASIC_ISTREAM_H_

#include <internal/cxx/fwd/iteratorfwd.h>
#include <internal/cxx/fwd/localefwd.h>
#include <internal/cxx/ios/basic_ios.h>
#include <internal/cxx/type_traits/detection.h>
#include <internal/cxx/type_traits/logic.h>
#include <internal/cxx/type_traits/type.h>
#include <internal/cxx/type_traits/type_relation.h>

namespace std {
  template<typename Char, typename Traits>
  class __basic_istream: virtual public __basic_ios<Char, Traits> {
  public:
    class sentry {
      friend class __basic_istream;

      bool _ok;

    public:
      explicit sentry(__basic_istream& is, bool noskipws = false): _ok(false) {
        ios_base::iostate err = ios_base::goodbit;

        if (is.good()) {
          __try {
            if (is.tie() != nullptr) {
              is.tie()->flush();
            }

            if (!noskipws && is._is_skipws()) {
              auto ch = is.rdbuf()->sgetc();

              while (!traits_type::eq_int_type(ch, traits_type::eof())) {
                if (!is._ctype.is(ctype_base::space, traits_type::to_char_type(ch))) {
                  break;
                }

                ch = is.rdbuf()->snextc();
              }

              if (trais_type::eq_int_type(ch, traits_type::eof())) {
                err |= ios_base::eofbit;
              }
            }
          }
          __catch (...) {
            // basic_istream::setstate may throw an exception.
            ios_base::_set_iostate(ios_base::badbit);
          }
        }

        if (is.good() && err == ios_base::goodbit) {
          _ok = true;
        } else {
          setstate(err | ios_base::failbit);
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

    using __ios_type      = __basic_ios<Char, Traits>;
    using __iterator_type = istreambuf_iterator<Char, Traits>;
    using __num_get_type  = num_get<Char, __iterator_type>;

  private:
    __num_get_type num_get;
    streamsize     _gcount;

  protected:
    __basic_istream(const __basic_istream&) = delete;

    __basic_istream(__basic_istream&& other): _gcount(other._gcount) {
      __ios_type::move(other);
    }

  public:
    explicit __basic_istream(__streambuf_type* buf): _gcount(0) {
      __ios_type::init(buf);
    }

    ~__basic_istream() { }

    __basic_istream& operator>>(__basic_istream& (*pf)(__basic_istream&)) {
      return pf(*this);
    }

    __basic_istream& operator>>(__basic_ios& (*pf)(__basic_ios&)) {
      pf(*this);
      return *this;
    }

    __basic_istream& operator>>(ios_base& (*pf)(ios_base&)) {
      pf(*this);
      return *this;
    }

    __basic_istream& operator>>(bool& n) {
      return extract(n);
    }

    __basic_istream& operator>>(short& n) {
      return extract(n);
    }

    __basic_istream& operator>>(unsigned short& n) {
      return extract(n);
    }

    __basic_istream& operator>>(int& n) {
      return extract(n);
    }

    __basic_istream& operator>>(unsigned int& n) {
      return extract(n);
    }

    __basic_istream& operator>>(long& n) {
      return extract(n);
    }

    __basic_istream& operator>>(unsigned long& n) {
      return extract(n);
    }

    __basic_istream& operator>>(long long& n) {
      return extract(n);
    }

    __basic_istream& operator>>(unsigned long long& n) {
      return extract(n);
    }

    __basic_istream& operator>>(void*& n) {
      return extract(n);
    }

    int_type get() {
      _gcount                  = 0;
      ios_base::iostate err    = ios_base::goodbit;
      int_type          result = traits_type::eof();

      sentry sentry(*this, true);

      if (sentry) {
        __try {
          result = rdbuf()->sbumpc();

          if (traits_type::eq_int_type(result, traits_type::eof())) {
            err |= ios_base::eofbit;
          } else {
            _gcount = 1;
          }
        }
        __catch (...) {
          // basic_istream::setstate may throw an exception.
          ios_base::_set_iostate(ios_base::badbit);
        }
      }

      if (_gcount == 0) {
        err |= ios_base::failbit;
      }

      if (err != ios_base::goodbit) {
        setstate(err);
      }

      return result;
    }

    __basic_istream& get(char_type& ch) {
      _gcount               = 0;
      ios_base::iostate err = ios_base::goodbit;

      sentry sentry(*this, true);

      if (sentry) {
        __try {
          int_type result = rdbuf()->sbumpc();

          if (traits_type::eq_int_type(result, traits_type::eof())) {
            err |= ios_base::eofbit;
          } else {
            gcount = 1;
            ch     = traits_type::to_char_type(result);
          }
        }
        __catch (...) {
          // basic_istream::setstate may throw an exception.
          ios_base::_set_iostate(ios_base::badbit);
        }
      }

      if (_gcount == 0) {
        err |= ios_base::failbit;
      }

      if (err != ios_base::goodbit) {
        setstate(err);
      }

      return *this;
    }

    __basic_istream& get(char_type* str, streamsize n) {
      return get(str, n, widen('\n'));
    }

    __basic_istream& get(char_type* str, streamsize n, char_type delim) {
      _gcount               = 0;
      ios_base::iostate err = ios_base::goodbit;

      sentry sentry(*this, true);

      if (sentry) {
        __try {
          int_type          idelim = traits_type::to_int_type(delim);
          int_type          eof    = traits_type::eof();
          __streambuf_type* buf    = rdbuf();

          int_type ch = buf->sgetc();

          while (_gcount < n - 1) {
            if (trais_type::eq_int_type(ch, eof) || traits_type::eq_int_type(ch, idelim)) {
              break;
            }

            *str++ = traits_type::to_char_type(ch);
            ++_gcount;
            ch = buf->snextc();
          }

          if (traits_type::eq_int_type(ch, eof)) {
            err |= ios_base::eofbit;
          }
        }
        __catch (...) {
          // basic_istream::setstate may throw an exception.
          ios_base::_set_iostate(ios_base::badbit);
        }
      }

      if (n > 0) {
        *str = char_type();
      }

      if (_gcount == 0) {
        err |= ios_base::failbit;
      }

      if (err != ios_base::goodbit) {
        setstate(err);
      }

      return *this;
    }

    __basic_istream& getline(char_type* str, streamsize n) {
      return getline(str, n, widen('\n'));
    }

    __basic_istream& getline(char_type* str, streamsize n, char_type delim) {
      _gcount               = 0;
      ios_base::iostate err = ios_base::goodbit;

      sentry sentry(*this, true);

      if (sentry) {
        __try {
          int_type          idelim = traits_type::to_int_type(delim);
          int_type          eof    = traits_type::eof();
          __streambuf_type* buf    = rdbuf();

          int_type ch = buf->sgetc();

          while (_gcount < n - 1) {
            if (trais_type::eq_int_type(ch, eof) || traits_type::eq_int_type(ch, idelim)) {
              break;
            }

            *str++ = traits_type::to_char_type(ch);
            ++_gcount;
            ch = buf->snextc();
          }

          if (traits_type::eq_int_type(ch, eof)) {
            err |= ios_base::eofbit;
          } else if (trais_type::eq_int_type(ch, idelim)) {
            buf->sbumpc();
            ++_gcount;
          } else {
            err |= ios_base::failbit;
          }
        }
        __catch (...) {
          // basic_istream::setstate may throw an exception.
          ios_base::_set_iostate(ios_base::badbit);
        }
      }

      if (n > 0) {
        *str = char_type();
      }

      if (_gcount == 0) {
        err |= ios_base::failbit;
      }

      if (err != ios_base::goodbit) {
        setstate(err);
      }

      return *this;
    }

    int_type peek() {
      _gcount                  = 0;
      int_type          result = traits_type::eof();
      ios_base::iostate err    = ios_base::goodbit;

      sentry sentry(*this, true);

      if (sentry) {
        __try {
          result = rdbuf()->sgetc();

          if (traits_type::eq_int_type(result, traits_type::eof())) {
            err |= ios_base::eofbit;
          }
        }
        __catch (...) {
          // basic_istream::setstate may throw an exception.
          ios_base::_set_iostate(ios_base::badbit);
        }
      }

      if (err != ios_base::goodbit) {
        setstate(err);
      }

      return result;
    }

    __basic_istream& read(char_type* str, streamsize n) {
      _gcount               = 0;
      ios_base::iostate err = ios_base::goodbit;

      sentry sentry(*this, true);

      if (sentry) {
        __try {
          _gcount = rdbuf()->sgetn(str, n);

          if (_gcount != n) {
            err |= ios_base::eofbit | ios_base::failbit;
          }
        }
        __catch (...) {
          // basic_istream::setstate may throw an exception.
          ios_base::_set_iostate(ios_base::badbit);
        }
      }

      if (err != ios_base::goodbit) {
        setstate(err);
      }

      return *this;
    }

    streamsize readsome(char_type* str, streamsize n) {
      _gcount               = 0;
      ios_base::iostate err = ios_base::goodbit;

      sentry sentry(*this, true);

      if (sentry) {
        __try {
          streamsize result = rdbuf()->in_avail();

          if (result > 0) {
            _gcount = rdbuf()->sgetn(str, min(result, n));
          } else if (result == -1) {
            err |= ios_base::eofbit;
          }
        }
        __catch (...) {
          // basic_istream::setstate may throw an exception.
          ios_base::_set_iostate(ios_base::badbit);
        }
      }

      if (err != ios_base::goodbit) {
        setstate(err);
      }

      return _gcount;
    }

    __basic_istream& ignore(streamsize n = 1, int_type delim = traits_type::eof()) {
      _gcount               = 0;
      ios_base::iostate err = ios_base::goodbit;

      sentry sentry(*this, true);

      bool large = false;

      if (sentry) {
        __try {
          int_type          eof = trais_type::eof();
          __streambuf_type* buf = rdbuf();

          int_type ch = buf->sgetc();

          while (true) {
            while (_gcount < n) {
              if (traits_type::eq_int_type(ch, eof) || traits_type::eq_int_type(ch, delim)) {
                break;
              }

              ++_gcount;
              ch = buf->snextc();
            }

            if (n == __numeric_limits<streamsize>::max() && !traits_type::eq_int_type(ch, eof) && !traits_type::eq_int_type(ch, delim)) {
              _gcount = __numeric_limits<streamsize>::min();
              large   = true;
            } else {
              break;
            }
          }

          if (n == __numeric_limits<streamsize>::max()) {
            if (large) {
              _gcount = __numeric_limits<streamsize>::max();
            }

            if (traits_type::eq_int_type(ch, eof)) {
              err |= ios_base::eofbit;
            } else {
              if (_gcount != n) {
                ++_gcount;
              }
              buf->sbumpc();
            }
          } else if (_gcount < n) {
            if (traits_type::eq_int_type(ch, eof)) {
              err |= ios_base::eofbit;
            } else {
              ++_gcount;
              buf->sbumpc();
            }
          }
        }
        __catch (...) {
          // basic_istream::setstate may throw an exception.
          ios_base::_set_iostate(ios_base::badbit);
        }
      }

      if (err != ios_base::goodbit) {
        setstate(err);
      }

      return *this;
    }

    __basic_istream& putback(char_type ch) {
      _gcount               = 0;
      ios_base::iostate err = ios_base::goodbit;

      clear(rdstate() & ~ios_base::eofbit);

      sentry sentry(*this, true);

      if (sentry) {
        __try {
          __streambuf_type* buf = rdbuf();
          if (buf == nullptr || traits_type::eq_int_type(buf->sputbackc(ch), traits_type::eof())) {
            err |= ios_base::badbit;
          }
        }
        __catch (...) {
          // basic_istream::setstate may throw an exception.
          ios_base::_set_iostate(ios_base::badbit);
        }
      }

      if (err != ios_base::goodbit) {
        setstate(err);
      }

      return *this;
    }

    __basic_istream& unget() {
      _gcount               = 0;
      ios_base::iostate err = ios_base::goodbit;

      clear(rdstate() & ~ios_base::eofbit);

      sentry sentry(*this, true);

      if (sentry) {
        __try {
          __streambuf_type* buf = rdbuf();
          if (buf == nullptr || traits_type::eq_int_type(buf->sungetc(), traits_type::eof())) {
            err |= ios_base::badbit;
          }
        }
        __catch (...) {
          // basic_istream::setstate may throw an exception.
          ios_base::_set_iostate(ios_base::badbit);
        }
      }

      if (err != ios_base::goodbit) {
        setstate(err);
      }

      return *this;
    }

    int sync() {
      int result = -1;

      sentry sentry(*this, true);
      if (sentry) {
        ios_base::iostate err = ios_base::goodbit;

        __try {
          __streambuf_type* buf = rdbuf();
          if (buf != nullptr) {
            result = buf->pubsync() ? 0 : -1;
            if (result == -1) {
              err |= ios_base::badbit;
            }
          } else {
            result = 0;
          }
        }
        __catch (...) {
          // basic_istream::setstate may throw an exception.
          ios_base::_set_iostate(ios_base::badbit);
        }

        if (err != ios_base::goodbit) {
          setstate(err);
        }
      }

      return result;
    }

    pos_type tellg() {
      pos_type result = pos_type(-1);

      sentry sentry(*this, true);
      if (sentry) {
        __try {
          if (!fail()) {
            __streambuf_type* buf = rdbuf();
            if (buf != nullptr) {
              result = buf->pubseekoff(0, ios_base::cur, ios_base::in);
            }
          }
        }
        __catch (...) {
          // basic_istream::setstate may throw an exception.
          ios_base::_set_iostate(ios_base::badbit);
        }
      }

      return result;
    }

    __basic_istream& seekg(pos_type pos) {
      clear(rdstate() & ~ios_base::eofbit);

      sentry sentry(*this, true);
      if (sentry) {
        ios_base::iostate err = ios_base::goodbit;

        __try {
          if (!fail()) {
            __streambuf_type* buf = rdbuf();
            if (buf == nullptr || buf->pubseekpos(pos, ios_base::in) == pos_type(-1)) {
              err |= ios_base::failbit;
            }
          }
        }
        __catch (...) {
          // basic_istream::setstate may throw an exception.
          ios_base::_set_iostate(ios_base::badbit);
        }

        if (err != ios_base::goodbit) {
          setstate(err);
        }
      }
    }

    __basic_istream& seekg(off_type off, ios_base::seekdir dir) {
      clear(rdstate() & ~ios_base::eofbit);

      sentry sentry(*this, true);
      if (sentry) {
        ios_base::iostate err = ios_base::goodbit;

        __try {
          if (!fail()) {
            __streambuf_type* buf = rdbuf();
            if (buf == nullptr || buf->pubseekoff(off, dir, ios_base::in) == pos_type(-1)) {
              err |= ios_base::failbit;
            }
          }
        }
        __catch (...) {
          // basic_istream::setstate may throw an exception.
          ios_base::_set_iostate(ios_base::badbit)
        }

        if (err != ios_base::goodbit) {
          setstate(err);
        }
      }

      return *this;
    }

  private:
    template<typename T>
    __basic_istream& extract(typename __enable_if<!__disjunction<__is_same_t<T, short>::value, __is_same_t<T, int>::value>::value, T>::type& n) {
      sentry sentry(*this);

      if (sentry) {
        ios_base::iostate err = ios_base::goodbit;

        __try {
          num_get.get(*this, 0, *this, err, n);
        }
        __catch (...) {
          // basic_istream::setstate may throw an exception.
          ios_base::_set_iostate(ios_base::badbit);
        }

        if (err != ios_base::goodbit) {
          setstate(err);
        }
      }

      return *this;
    }

    template<typename T>
    __basic_istream& extract(typename __enable_if<__disjunction<__is_same_t<T, short>::value, __is_same_t<T, int>::value>::value, T>::type& n) {
      sentry sentry(*this);

      if (sentry) {
        ios_base::iostate err = ios_base::goodbit;

        __try {
          long result;
          num_get.get(*this, 0, *this, err, result);

          if (result < __numeric_limits<T>::min()) {
            err |= ios_base::failbit;
            n = __numeric_limits<T>::min();
          } else if (result > __numeric_limits<T>::max()) {
            err |= ios_base::failbit;
            n = __numeric_limits<T>::max();
          } else {
            n = static_cast<T>(result);
          }
        }
        __catch (...) {
          // basic_istream::setstate may throw an exception.
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

#endif // CAPRESE_LIBC_INTERNAL_CXX_ISTREAM_BASIC_ISTREAM_H_
