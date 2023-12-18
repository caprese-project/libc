#ifndef CAPRESE_LIBC_INTERNAL_CXX_IOS_BASIC_IOS_H_
#define CAPRESE_LIBC_INTERNAL_CXX_IOS_BASIC_IOS_H_

#include <internal/attribute.h>
#include <internal/cxx/fwd/iteratorfwd.h>
#include <internal/cxx/fwd/localefwd.h>
#include <internal/cxx/fwd/streambuffwd.h>
#include <internal/cxx/ios/ios_base.h>
#include <internal/cxx/locale/ctype.h>
#include <internal/cxx/locale/facet.h>
#include <internal/cxx/memory/addressof.h>

namespace std {
  template<typename Char, typename Traits>
  class __basic_ostream;

  template<typename Char, typename Traits>
  class __basic_ios: public ios_base {
  public:
    using char_type   = Char;
    using traits_type = Traits;

    using int_type = typename traits_type::int_type;
    using pos_type = typename traits_type::pos_type;
    using off_type = typename traits_type::off_type;

    using __streambuf_type = __basic_streambuf<char_type, traits_type>;
    using __ostream_type   = __basic_ostream<char_type, traits_type>;
    using __num_get_type   = num_get<Char, istreambuf_iterator<char_type, traits_type>>;
    using __num_put_type   = num_put<Char, ostreambuf_iterator<char_type, traits_type>>;
    using __ctype_type     = ctype<Char>;

  protected:
    __streambuf_type*     _rdbuf;
    __ostream_type*       _tie;
    const __num_get_type* _num_get;
    const __num_put_type* _num_put;
    const __ctype_type*   _ctype;
    iostate               _exceptions;
    char_type             _fillch;

  protected:
    __basic_ios() { }

    void init(__streambuf_type* buf) {
      _rdbuf      = buf;
      _tie        = nullptr;
      _exceptions = goodbit;

      _num_get = __addressof(use_facet<__num_get_type>(locale::classic()));
      _num_put = __addressof(use_facet<__num_put_type>(locale::classic()));
      _ctype   = __addressof(use_facet<__ctype_type>(locale::classic()));

      _fillch = widen(' ');

      ios_base::_init();

      if (buf == nullptr) {
        _set_iostate(badbit);
      }
      _set_fmtflags(skipws | dec);
    }

    void set_rdbuf(__streambuf_type* buf) {
      _rdbuf = buf;
    }

    void move(__basic_ios& other) {
      ios_base::_move(other);
      _rdbuf   = nullptr;
      _num_get = other._num_get;
      _num_put = other._num_put;
      _ctype   = other._ctype;
      this->tie(other.tie(nullptr));
      _exceptions = other._exceptions;
      _fillch     = other._fillch;
    }

    void move(__basic_ios&& other) {
      ios_base::_move(other);
      _rdbuf   = nullptr;
      _num_get = other._num_get;
      _num_put = other._num_put;
      _ctype   = other._ctype;
      this->tie(other.tie(nullptr));
      _exceptions = other._exceptions;
      _fillch     = other._fillch;
    }

    void swap(__basic_ios& other) __noexcept {
      using std::swap;

      ios_base::_swap(other);

      swap(_tie, other._tie);
      swap(_num_get, other._num_get);
      swap(_num_put, other._num_put);
      swap(_ctype, other._ctype);
      swap(_exceptions, other._exceptions);
      swap(_fillch, other._fillch);
    }

  public:
    explicit __basic_ios(__streambuf_type* buf) {
      init(buf);
    }

    __basic_ios(__basic_ios&)       = delete;
    __basic_ios(const __basic_ios&) = delete;

    ~__basic_ios() { }

    iostate rdstate() const {
      return _get_iostate();
    }

    void clear(iostate state = goodbit) {
      _set_iostate(state);

      if (_rdbuf == nullptr) {
        _set_iostate(_get_iostate() | badbit);
      }
    }

    void setstate(iostate state) {
      clear(rdstate() | state);
    }

    bool good() const {
      return rdstate() == goodbit;
    }

    bool eof() const {
      return (rdstate() & eofbit) != 0;
    }

    bool fail() const {
      return (rdstate() & (failbit | badbit)) != 0;
    }

    bool bad() const {
      return (rdstate() & badbit) != 0;
    }

    explicit operator bool() const {
      return !fail();
    }

    bool operator!() const {
      return fail();
    }

    iostate exceptions() const {
      return _exceptions;
    }

    iostate exceptions(iostate except) {
      iostate old_except = _exceptions;
      _exceptions        = except & _iostate_mask;
      return old_except;
    }

    __streambuf_type* rdbuf() const {
      return _rdbuf;
    }

    __streambuf_type* rdbuf(__streambuf_type* buf) {
      __streambuf_type* old_buf = _rdbuf;
      _rdbuf                    = buf;
      clear();
      return old_buf;
    }

    __ostream_type* tie() const {
      return _tie;
    }

    __ostream_type* tie(__ostream_type* tie) {
      __ostream_type* old_tie = _tie;
      _tie                    = tie;
      return old_tie;
    }

    __basic_ios& copyfmt(const __basic_ios& rhs) {
      if (this != __addressof(rhs)) {
        _set_fmtflags(rhs._get_fmtflags());
      }

      return *this;
    }

    char_type fill() const {
      return _fillch;
    }

    char_type fill(char_type fillch) {
      char_type old_fillch = _fillch;
      _fillch              = fillch;
      return old_fillch;
    }

    char_type widen(char ch) const {
      return _ctype->widen(ch);
    }
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_IOS_BASIC_IOS_H_
