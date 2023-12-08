#ifndef CAPRESE_LIBC_INTERNAL_CXX_IOSTREAM_STDIN_STREAMBUF_H_
#define CAPRESE_LIBC_INTERNAL_CXX_IOSTREAM_STDIN_STREAMBUF_H_

#include <cstdio>
#include <internal/branch.h>
#include <internal/cxx/streambuf/basic_streambuf.h>
#include <internal/cxx/string/char_traits.h>

namespace std {
  template<typename Char>
  class __stdin_streambuf: public __basic_streambuf<Char, char_traits<Char>> {
    FILE* fp;

  protected:
    virtual int_type underflow() {
      return _getc(true);
    }

    virtual int_type uflow() {
      return _getc(false);
    }

    virtual int_type pbackfail(int_type ch = traits_type::eof()) {
      if (traits_type::eq_int_type(ch, traits_type::eof())) {
        return ch;
      }

      // TODO: impl

      return ch;
    }

  public:
    __stdin_streambuf(FILE* fp): fp(fp) { }

  private:
    int_type _getc(bool peek) {
      int ch = ::getc(fp);
      __if_unlikely (ch == EOF) {
        return traits_type::eof();
      }

      if (peek) {
        ::ungetc(ch, fp);
      }

      return trais_type::to_int_type(static_cast<char_type>(ch));
    }
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_IOSTREAM_STDIN_STREAMBUF_H_
