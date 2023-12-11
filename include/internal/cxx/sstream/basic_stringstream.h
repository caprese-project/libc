#ifndef CAPRESE_LIBC_INTERNAL_CXX_SSTREAM_BASIC_STRINGSTREAM_H_
#define CAPRESE_LIBC_INTERNAL_CXX_SSTREAM_BASIC_STRINGSTREAM_H_

#include <internal/cxx/istream/basic_iostream.h>
#include <internal/cxx/sstream/basic_stringbuf.h>
#include <internal/cxx/utility/fwd.h>

namespace std {
  template<typename Char, typename Traits, typename Allocator>
  class __basic_stringstream: public __basic_iostream<Char, Traits> {
  public:
    using char_type      = Char;
    using traits_type    = Traits;
    using allocator_type = Allocator;
    using int_type       = typename traits_type::int_type;
    using pos_type       = typename traits_type::pos_type;
    using off_type       = typename traits_type::off_type;

    using __string_type    = __basic_string<char_type, traits_type, allocator_type>;
    using __stringbuf_type = __basic_stringbuf<char_type, traits_type, allocator_type>;
    using __iostream_type  = __basic_iostream<char_type, traits_type>;

  private:
    __stringbuf_type _buf;

  public:
    explicit __basic_stringstream(ios_base::openmode mode): __iostream_type(), _buf(mode | ios_base::in | ios_base::out) {
      init(&_buf);
    }

    __basic_stringstream(): __basic_stringstream(ios_base::in | ios_base::out) { }

    explicit __basic_stringstream(const __string_type& str, ios_base::openmode mode = ios_base::in | ios_base::out): __iostream_type(), _buf(str, mode | ios_base::in | ios_base::out) {
      init(&_buf);
    }

    __basic_stringstream(__basic_stringstream&& other): __iostream_type(move(other)), _buf(move(other._buf)) {
      __iostream_type::set_rdbuf(&_buf);
    }

    __basic_stringstream& operator=(__basic_stringstream&& other) {
      __iostream_type::operator=(move(other));
      _buf = move(other._buf);
      return *this;
    }

    __basic_stringstream(const __basic_stringstream&)            = delete;
    __basic_stringstream& operator=(const __basic_stringstream&) = delete;

    ~basic_iostringstream() { }

    void swap(__basic_stringstream& other) {
      __iostream_type::swap(other);
      _buf.swap(other._buf);
    }

    __stringbuf_type* rdbuf() const {
      return const_cast<__stringbuf_type*>(&_buf);
    }

    __string_type str() const {
      return _buf.str();
    }

    __string_type str() && {
      return move(_buf).str();
    }
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_SSTREAM_BASIC_STRINGSTREAM_H_
