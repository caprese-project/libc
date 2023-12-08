#ifndef CAPRESE_LIBC_INTERNAL_CXX_IOSTREAM_STDOUT_STREAMBUF_H_
#define CAPRESE_LIBC_INTERNAL_CXX_IOSTREAM_STDOUT_STREAMBUF_H_

#include <cstdio>
#include <internal/branch.h>
#include <internal/cxx/streambuf/basic_streambuf.h>
#include <internal/cxx/string/char_traits.h>

namespace std {
  template<typename Char>
  class __stdout_streambuf: public __basic_streambuf<Char, char_traits<Char>> {
  public:
    using char_type   = typename __basic_streambuf<Char, char_traits<Char>>::char_type;
    using traits_type = typename __basic_streambuf<Char, char_traits<Char>>::traits_type;
    using int_type    = typename __basic_streambuf<Char, char_traits<Char>>::int_type;
    using pos_type    = typename __basic_streambuf<Char, char_traits<Char>>::pos_type;
    using off_type    = typename __basic_streambuf<Char, char_traits<Char>>::off_type;

    FILE* fp;

  protected:
    virtual int_type overflow(int_type ch = traits_type::eof()) {
      if (!traits_type::eq_int_type(ch, traits_type::eof())) {
        char_type buf = traits_type::to_char_type(ch);
        if (::fwrite(&buf, sizeof(char_type), 1, fp) != 1) {
          return traits_type::eof();
        }
      }

      return traits_type::not_eof(ch);
    }

    virtual streamsize xsputn(const char_type* str, streamsize n) {
      return ::fwrite(str, sizeof(char_type), n, fp);
    }

    virtual int sync() {
      if (::fflush(fp) != 0) {
        return -1;
      }
      return 0;
    }

  public:
    __stdout_streambuf(FILE* fp): fp(fp) { }
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_IOSTREAM_STDOUT_STREAMBUF_H_
