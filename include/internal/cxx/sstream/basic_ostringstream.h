#ifndef CAPRESE_LIBC_INTERNAL_CXX_SSTREAM_BASIC_OSTRINGSTREAM_H_
#define CAPRESE_LIBC_INTERNAL_CXX_SSTREAM_BASIC_OSTRINGSTREAM_H_

#include <internal/cxx/ostream/basic_ostream.h>
#include <internal/cxx/sstream/basic_stringbuf.h>
#include <internal/cxx/utility/fwd.h>

namespace std {
  template<typename Char, typename Traits, typename Allocator>
  class __basic_ostringstream: public __basic_ostream<Char, Traits> {
  public:
    using char_type      = Char;
    using traits_type    = Traits;
    using allocator_type = Allocator;
    using int_type       = typename traits_type::int_type;
    using pos_type       = typename traits_type::pos_type;
    using off_type       = typename traits_type::off_type;

    using __string_type    = __basic_string<char_type, traits_type, allocator_type>;
    using __stringbuf_type = __basic_stringbuf<char_type, traits_type, allocator_type>;
    using __ostream_type   = __basic_ostream<char_type, traits_type>;

  private:
    __stringbuf_type _buf;

  public:
    explicit __basic_ostringstream(ios_base::openmode mode): __ostream_type(), _buf(mode | ios_base::out) {
      init(&_buf);
    }

    __basic_ostringstream(): __basic_ostringstream(ios_base::out) { }

    explicit __basic_ostringstream(const __string_type& str, ios_base::openmode mode = ios_base::out): __ostream_type(), _buf(str, mode | ios_base::out) {
      init(&_buf);
    }

    __basic_ostringstream(__basic_ostringstream&& other): __ostream_type(move(other)), _buf(move(other._buf)) {
      __ostream_type::set_rdbuf(&_buf);
    }

    __basic_ostringstream& operator=(__basic_ostringstream&& other) {
      __ostream_type::operator=(move(other));
      _buf = move(other._buf);
      return *this;
    }

    __basic_ostringstream(const __basic_ostringstream&)            = delete;
    __basic_ostringstream& operator=(const __basic_ostringstream&) = delete;

    ~__basic_ostringstream() { }

    void swap(__basic_ostringstream& other) {
      __ostream_type::swap(other);
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

#endif // CAPRESE_LIBC_INTERNAL_CXX_SSTREAM_BASIC_OSTRINGSTREAM_H_
