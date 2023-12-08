#ifndef CAPRESE_LIBC_INTERNAL_CXX_ITERATOR_OSTREAMBUF_ITERATOR_H_
#define CAPRESE_LIBC_INTERNAL_CXX_ITERATOR_OSTREAMBUF_ITERATOR_H_

#include <internal/attribute.h>
#include <internal/cxx/iterator/traits.h>
#include <internal/cxx/fwd/iosfwd.h>
#include <internal/cxx/streambuf/basic_streambuf.h>
#include <internal/cxx/string/char_traits.h>

namespace std {
  template<typename Char, class Traits = char_traits<Char>>
  class ostreambuf_iterator: public iterator<output_iterator_tag, void, void, void, void> {
  public:
    using char_type         = Char;
    using traits_type       = Traits;
    using streambuf_type    = __basic_streambuf<char_type, traits_type>;
    using ostream_type      = __basic_ostream<char_type, traits_type>;
    using iterator_category = output_iterator_tag;
    using value_type        = void;
    using difference_type   = void;
    using pointer           = void;
    using reference         = void;

  private:
    streambuf_type* _streambuf;

  public:
    ostreambuf_iterator(ostream_type& os) __noexcept: _streambuf(os.rdbuf()) { }

    ostreambuf_iterator(streambuf_type* buf) __noexcept: _streambuf(buf) { }

    ~ostreambuf_iterator() = default;

    ostreambuf_iterator& operator=(char_type ch) {
      if (_streambuf == nullptr) {
        return *this;
      }

      if (_streambuf->sputc(ch) == traits_type::eof()) {
        _streambuf = nullptr;
      }

      return *this;
    }

    ostreambuf_iterator& operator*() {
      return *this;
    }

    ostreambuf_iterator& operator++() {
      return *this;
    }

    ostreambuf_iterator& operator++(int) {
      return *this;
    }

    bool failed() const __noexcept {
      return _streambuf == nullptr;
    }
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_ITERATOR_OSTREAMBUF_ITERATOR_H_
