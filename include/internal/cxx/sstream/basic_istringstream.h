#ifndef CAPRESE_LIBC_INTERNAL_CXX_SSTREAM_BASIC_ISTRINGSTREAM_H_
#define CAPRESE_LIBC_INTERNAL_CXX_SSTREAM_BASIC_ISTRINGSTREAM_H_

#include <internal/cxx/istream/basic_istream.h>
#include <internal/cxx/sstream/basic_stringbuf.h>
#include <internal/cxx/utility/fwd.h>

namespace std {
  template<typename Char, typename Traits, typename Allocator>
  class __basic_istringstream: public __basic_istream<Char, Traits> {
  public:
    using char_type      = Char;
    using traits_type    = Traits;
    using allocator_type = Allocator;
    using int_type       = typename traits_type::int_type;
    using pos_type       = typename traits_type::pos_type;
    using off_type       = typename traits_type::off_type;

    using __stringbuf_type = __basic_stringbuf<char_type, traits_type, allocator_type>;
    using __string_type    = typename __stringbuf_type::__string_type;
    using __istream_type   = __basic_istream<char_type, traits_type>;

  private:
    __stringbuf_type _buf;

  public:
    explicit __basic_istringstream(ios_base::openmode mode): __istream_type(), _buf(mode | ios_base::in) {
      this->init(&_buf);
    }

    __basic_istringstream(): __basic_istringstream(ios_base::in) { }

    explicit __basic_istringstream(const __string_type& str, ios_base::openmode mode = ios_base::in): __istream_type(), _buf(str, mode | ios_base::in) {
      this->init(&_buf);
    }

#ifdef __CXX_STD_20__

    explicit __basic_istringstream(__string_type&& str, ios_base::openmode mode = ios_base::in): __istream_type(), _buf(move(str), mode | ios_base::in) {
      this->init(&_buf);
    }

#endif // __CXX_STD_20__

    __basic_istringstream(__basic_istringstream&& other): __istream_type(move(other)), _buf(move(other._buf)) {
      __istream_type::set_rdbuf(&_buf);
    }

    __basic_istringstream& operator=(__basic_istringstream&& other) {
      __istream_type::operator=(move(other));
      _buf = move(other._buf);
      return *this;
    }

    __basic_istringstream(const __basic_istringstream&)            = delete;
    __basic_istringstream& operator=(const __basic_istringstream&) = delete;

    ~__basic_istringstream() { }

    void swap(__basic_istringstream& other) {
      __istream_type::swap(other);
      _buf.swap(other._buf);
    }

    __stringbuf_type* rdbuf() const {
      return const_cast<__stringbuf_type*>(&_buf);
    }

    __string_type str() const {
      return _buf.str();
    }
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_SSTREAM_BASIC_ISTRINGSTREAM_H_
