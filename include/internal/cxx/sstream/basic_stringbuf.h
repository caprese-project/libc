#ifndef CAPRESE_LIBC_INTERNAL_CXX_SSTREAM_BASIC_STRINGBUF_H_
#define CAPRESE_LIBC_INTERNAL_CXX_SSTREAM_BASIC_STRINGBUF_H_

#include <internal/cxx/ios/ios_base.h>
#include <internal/cxx/ios/types.h>
#include <internal/cxx/streambuf/basic_streambuf.h>
#include <internal/cxx/string/basic_string.h>
#include <internal/cxx/utility/swap.h>

namespace std {
  template<typename Char, typename Traits, typename Allocator>
  class __basic_stringbuf: public std::__basic_streambuf<Char, Traits> {
  public:
    using char_type      = Char;
    using traits_type    = Traits;
    using int_type       = typename traits_type::int_type;
    using pos_type       = typename traits_type::pos_type;
    using off_type       = typename traits_type::off_type;
    using allocator_type = Allocator;

    using __streambuf_type = __basic_streambuf<char_type, traits_type>;
    using __string_type    = __basic_string<char_type, traits_type, allocator_type>;
    using __size_type      = typename __string_type::size_type;

  private:
    __string_type      _buf;
    ios_base::openmode _mode;

  private:
    void _init() {
      if (_mode & ios_base::out) {
        this->_put_beg = _buf.data();
        this->_put_end = _buf.data() + _buf.size();

        if (_mode & ios_base::app) {
          this->_put_cur = this->_put_end;
        } else {
          this->_put_cur = this->_put_beg;
        }
      }

      if (_mode & ios_base::in) {
        this->_get_beg = _buf.data();
        this->_get_end = _buf.data() + _buf.size();
        this->_get_cur = this->_get_beg;
      }
    }

    void _pbump(char_type* buf, char_type* end, off_type off) {
      setp(buf, end);
      pbump(off);
    }

    void _sync(char_type* buf, __size_type in, __size_type out) {
      char_type* put_end = buf + _buf.capacity();
      char_type* get_end = buf + _buf.size();

      if (buf != _buf.data()) {
        get_end += in;
        put_end = get_end;

        in = 0;
      }

      if (_mode & ios_base::in) {
        setg(buf, buf + in, get_end);
      }

      if (_mode & ios_base::out) {
        _pbump(buf, put_end, out);
        if ((_mode & ios_base::in) == 0) {
          setg(get_end, get_end, get_end);
        }
      }
    }

    void _update_egptr() {
      char_type* _pptr = pptr();
      if (_pptr != nullptr && egptr() != nullptr) {
        if (_mode & ios_base::in) {
          setg(eback(), gptr(), _pptr);
        } else {
          setg(_pptr, _pptr, _pptr);
        }
      }
    }

  protected:
    virtual int_type underflow() {
      int_type result;

      if (_mode & ios_base::in) {
        _update_egptr();
        if (gptr() < egptr()) {
          result = traits_type::to_int_type(*gptr());
        } else {
          result = traits_type::eof();
        }
      } else {
        result = traits_type::eof();
      }

      return result;
    }

    virtual int_type pbackfail(int_type ch = traits_type::eof()) {
      int_type result;

      if (eback() < gptr()) {
        if (traits_type::eq_int_type(ch, traits_type::eof())) {
          gbump(-1);
          result = traits_type::not_eof(ch);
        } else {
          bool eq = traits_type::eq(traits_type::to_char_type(ch), gptr()[-1]);
          if (eq || (_mode & ios_base::out)) {
            gbump(-1);
            if (!eq) {
              *gptr() = traits_type::to_char_type(ch);
            }
            result = ch;
          }
        }
      } else {
        result = traits_type::eof();
      }

      return result;
    }

    virtual int_type overflow(int_type ch = traits_type::eof()) {
      int_type result;

      if (_mode & ios_base::out) {
        if (traits_type::eq_int_type(ch, traits_type::eof())) {
          result = traits_type::not_eof(ch);
        } else {
          __size_type capacity = _buf.capacity();
          char_type*  data     = _buf.data();
          if (epptr() - pbase() < capacity) {
            _pbump(data, data + capacity, pptr() - ppbase());
            if (_mode & ios_base::in) {
              setg(data, data + (gptr() - eback()), data + (egptr() - eback()) + 1);
            }
            *pptr() = traits_type::to_char_type(ch);
            pbump(1);
            result = ch;
          } else if (pptr() < epptr()) {
            __string_type tmpbuf(_buf.get_allocator());
            tmpbuf.reserve(std::max<__size_type>(2 * capacity, 512));
            if (pbase() != nullptr) {
              tmpbuf.append(pbase(), epptr() - pbase());
            }
            tmpbuf.push_back(traits_type::to_char_type(ch));
            _buf.swap(tmpbuf);
            _sync(_buf.data(), gptr() - eback(), pptr() - pbase());
            result = ch;
          } else if (_buf.max_size() == capacity) {
            result = traits_type::eof();
          } else {
            *pptr() = traits_type::to_char_type(ch);
            result  = ch;
          }
        }
      } else {
        result = traits_type::eof();
      }

      return result;
    }

    virtual __streambuf_type* setbuf(char_type* str, streamsize n) {
      if (str != nullptr && n >= 0) {
        _buf.clear();
        _sync(str, n, 0);
      }
      return this;
    }

    virtual pos_type seekoff(off_type off, std::ios_base::seekdir dir, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out) {
      pos_type result = (pos_type)(off_type)-1;

      bool in   = mode & _mode & ios_base::in;
      bool out  = mode & _mode & ios_base::out;
      bool both = in && out && dir != ios_base::cur;
      in        = in & !(_mode & ios_base::out);
      out       = out & !(_mode & ios_base::in);

      char_type* beg = in ? eback() : pbase();

      if ((beg != nullptr || off != 0) && (in || out || both)) {
        _update_egptr();

        off_type offin;
        off_type offout;

        switch (dir) {
          case ios_base::beg:
            offin  = off;
            offout = off;
          case ios_base::cur:
            offin  = off + gptr() - beg;
            offout = off + pptr() - beg;
            break;
          case ios_base::end:
            offin  = off + egptr() - beg;
            offout = offin;
            break;
          default:
            return result;
        }

        if ((in || both) && offin >= 0 && egptr() - beg >= offin) {
          setg(eback(), eback() + offin, egptr());
          result = (pos_type)offin;
        }

        if ((out || both) && offout >= 0 && egptr() - beg >= offout) {
          _pbump(pbase(), epptr(), offout);
          result = (pos_type)offout;
        }
      }

      return result;
    }

    virtual pos_type seekpos(pos_type sp, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out) {
      pos_type result = (pos_type)(off_type)-1;

      bool in  = _mode & mode & ios_base::in;
      bool out = _mode & mode & ios_base::out;

      char_type* beg = in ? eback() : pbase();

      if ((beg != nullptr || sp != 0) && (in || out)) {
        _update_egptr();

        off_type pos = sp;
        if (pos >= 0 && pos <= egptr() - beg) {
          if (in) {
            setg(eback(), eback() + pos, egptr());
          }
          if (out) {
            _pbump(pbase(), epptr(), pos);
          }
          result = sp;
        }
      }

      return result;
    }

  public:
    __basic_stringbuf(): __basic_stringbuf(ios_base::in | ios_base::out) { }

    explicit __basic_stringbuf(ios_base::openmode mode): _mode(mode) {
      _init();
    }

    explicit __basic_stringbuf(const __string_type& str, ios_base::openmode mode = ios_base::in | ios_base::out): _mode(mode) {
      _init();
    }

    __basic_stringbuf(__basic_stringbuf&& other): _mode(other._mode), _buf(std::move(other._buf)) { }

    __basic_stringbuf& operator=(__basic_stringbuf&& other) {
      const __streambuf_type& base = other;

      __streambuf_type::operator=(base);

      _mode = other._mode;
      _buf  = std::move(other._buf);

      return *this;
    }

    __basic_stringbuf(const __basic_stringbuf&)            = delete;
    __basic_stringbuf& operator=(const __basic_stringbuf&) = delete;

    void swap(__basic_stringbuf& other) {
      using std::swap;

      const __streambuf_type& base = other;
      __streambuf_type::swap(base);

      swap(_mode, other._mode);
      swap(_buf, other._buf);
    }

    __string_type str() const {
      if (_mode & ios_base::openmode::out) {
        return __string_type(this->pbase(), this->epptr());
      } else {
        return __string_type(this->eback(), this->egptr());
      }
    }
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_SSTREAM_BASIC_STRINGBUF_H_
