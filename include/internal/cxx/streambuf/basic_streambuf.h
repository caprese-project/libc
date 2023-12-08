#ifndef CAPRESE_LIBC_INTERNAL_CXX_STREAMBUF_BASIC_STREAM_BUF_H_
#define CAPRESE_LIBC_INTERNAL_CXX_STREAMBUF_BASIC_STREAM_BUF_H_

#include <internal/cxx/algorithm/minmax.h>
#include <internal/cxx/ios/ios_base.h>
#include <internal/cxx/ios/types.h>
#include <internal/cxx/utility/swap.h>

namespace std {
  template<typename Char, typename Traits>
  class __basic_streambuf {
  public:
    using char_type   = Char;
    using traits_type = Traits;

    using int_type = typename traits_type::int_type;
    using pos_type = typename traits_type::pos_type;
    using off_type = typename traits_type::off_type;

  protected:
    char_type* _get_beg;
    char_type* _get_cur;
    char_type* _get_end;
    char_type* _put_beg;
    char_type* _put_cur;
    char_type* _put_end;

  protected:
    __basic_streambuf(): _get_beg(nullptr), _get_cur(nullptr), _get_end(nullptr), _put_beg(nullptr), _put_cur(nullptr), _put_end(nullptr) {
      // Do nothing.
    }

    __basic_streambuf(const __basic_streambuf&)            = default;
    __basic_streambuf& operator=(const __basic_streambuf&) = default;

#ifdef __CXX_STD_11__

    void swap(__basic_streambuf& other) {
      using std::swap;
      swap(_get_beg, other._get_beg);
      swap(_get_cur, other._get_cur);
      swap(_get_end, other._get_end);
      swap(_put_beg, other._put_beg);
      swap(_put_cur, other._put_cur);
      swap(_put_end, other._put_end);
    }

#endif // __CXX_STD_11__

    virtual __basic_streambuf* setbuf(char_type*, streamsize) {
      return this;
    }

    virtual pos_type seekoff(off_type, ios_base::seekdir, ios_base::openmode = ios_base::in | ios_base::out) {
      return pos_type(off_type(-1));
    }

    virtual pos_type seekpos(pos_type, ios_base::openmode = ios_base::in | ios_base::out) {
      return pos_type(off_type(-1));
    }

    virtual int sync() {
      return 0;
    }

    virtual streamsize showmanyc() {
      return 0;
    }

    virtual int_type underflow() {
      return traits_type::eof();
    }

    virtual int_type uflow() {
      if (!traits_type::eq_int_type(underflow(), traits_type::eof())) {
        int_type result = traits_type::to_int_type(*gptr());
        gbump(1);
        return result;
      } else {
        return traits_type::eof();
      }
    }

    virtual streamsize xsgetn(char_type* s, streamsize count) {
      streamsize result = 0;

      while (result < count) {
        streamsize avail = egptr() - gptr();
        if (avail != 0) {
          streamsize n = min(avail, count - result);
          traits_type::copy(s, gptr(), n);
          result += n;
          s += n;
          gbump(n);
        }

        if (result < count) {
          int_type ch = uflow();
          if (!traits_type::eq_int_type(ch, traits_type::eof())) {
            traits_type::assign(*s++, traits_type::to_char_type(ch));
            ++result;
          } else {
            break;
          }
        }
      }

      return result;
    }

    char_type* eback() const {
      return _get_beg;
    }

    char_type* gptr() const {
      return _get_cur;
    }

    char_type* egptr() const {
      return _get_end;
    }

    void gbump(int count) {
      _get_cur += count;
    }

    void setg(char_type* gbeg, char_type* gcur, char_type* gend) {
      _get_beg = gbeg;
      _get_cur = gcur;
      _get_end = gend;
    }

    virtual streamsize xsputn(const char_type* s, streamsize count) {
      streamsize result = 0;

      while (result < count) {
        streamsize avail = epptr() - pptr();
        if (avail != 0) {
          streamsize n = min(avail, count - result);
          traits_type::copy(pptr(), s, n);
          result += n;
          s += n;
          pbump(n);
        }

        if (result < count) {
          int_type ch = overflow(traits_type::to_int_type(*s));
          if (!traits_type::eq_int_type(ch, traits_type::eof())) {
            ++result;
            ++s;
          } else {
            break;
          }
        }
      }

      return result;
    }

    virtual int_type overflow(int_type = traits_type::eof()) {
      return traits_type::eof();
    }

    char_type* pbase() const {
      return _put_beg;
    }

    char_type* pptr() const {
      return _put_cur;
    }

    char_type* epptr() const {
      return _put_end;
    }

    void pbump(int count) {
      _put_cur += count;
    }

    void setp(char_type* pbeg, char_type* pend) {
      _put_beg = pbeg;
      _put_cur = pbeg;
      _put_end = pend;
    }

    virtual int_type pbackfail(int_type = traits_type::eof()) {
      return traits_type::eof();
    }

  public:
    virtual ~__basic_streambuf() {
      // Do nothing.
    }

    __basic_streambuf* pubsetbuf(char_type* s, streamsize n) {
      return setbuf(s, n);
    }

    pos_type pubseekoff(off_type off, ios_base::seekdir dir, ios_base::openmode which = ios_base::in | ios_base::out) {
      return seekoff(off, dir, which);
    }

    pos_type pubseekpos(pos_type pos, ios_base::openmode which = ios_base::in | ios_base::out) {
      return seekpos(pos, which);
    }

    int pubsync() {
      return sync();
    }

    streamsize in_avail() {
      streamsize avail = egptr() - gptr();
      if (avail != 0) {
        return avail;
      } else {
        return showmanyc();
      }
    }

    int_type snextc() {
      if (!traits_type::eq_int_type(sbumpc(), traits_type::eof())) {
        return sgetc();
      } else {
        return traits_type::eof();
      }
    }

    int_type sbumpc() {
      if (gptr() < egptr()) {
        int_type result = traits_type::to_int_type(*gptr());
        gbump(1);
        return result;
      } else {
        return uflow();
      }
    }

#ifndef __CXX_STD_17__
    __deprecated_cxx_std_14 void stossc() {
      if (gptr() < egptr()) {
        gbump(1);
      } else {
        uflow();
      }
    }
#endif // !__CXX_STD_17__

    int_type sgetc() {
      if (gptr() < egptr()) {
        return traits_type::to_int_type(*gptr());
      } else {
        return underflow();
      }
    }

    streamsize sgetn(char_type* s, streamsize count) {
      return xsgetn(s, count);
    }

    int_type sputc(int_type ch) {
      if (pptr() < epptr()) {
        *pptr() = traits_type::to_char_type(ch);
        pbump(1);
        return ch;
      } else {
        return overflow(ch);
      }
    }

    int_type sputn(const char_type* s, streamsize count) {
      return xsputn(s, count);
    }

    int_type sputbackc(char_type ch) {
      if (eback() >= gptr() || !traits_type::eq(ch, gptr()[-1])) [[unlikely]] {
        return pbackfail(traits_type::to_int_type(ch));
      } else {
        gbump(-1);
        return traits_type::to_int_type(ch);
      }
    }

    int_type sungetc() {
      if (eback() < gptr()) {
        gbump(-1);
        return traits_type::to_int_type(*gptr());
      } else {
        return pbackfail();
      }
    }
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_STREAMBUF_BASIC_STREAM_BUF_H_
