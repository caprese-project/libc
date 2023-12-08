#ifndef CAPRESE_LIBC_INTERNAL_CXX_ITERATOR_ISTREAMBUF_ITERATOR_H_
#define CAPRESE_LIBC_INTERNAL_CXX_ITERATOR_ISTREAMBUF_ITERATOR_H_

#include <internal/attribute.h>
#include <internal/cxx/istream/basic_istream.h>
#include <internal/cxx/iterator/traits.h>
#include <internal/cxx/streambuf/basic_streambuf.h>
#include <internal/cxx/string/char_traits.h>

namespace std {
  template<typename Char, typename Traits = char_traits<Char>>
  class istreambuf_iterator: public iterator<input_iterator_tag, Char, typename Traits::off_type, Char*, Char> {
  public:
    using char_type         = Char;
    using traits_type       = Traits;
    using int_type          = typename traits_type::int_type;
    using streambuf_type    = __basic_streambuf<char_type, traits_type>;
    using istream_type      = __basic_istream<char_type, traits_type>;
    using iterator_category = input_iterator_tag;
    using value_type        = char_type;
    using difference_type   = typename traits_type::off_type;
    using pointer           = char_type*;
    using reference         = char_type;

  private:
    mutable streambuf_type* _streambuf;
    mutable int_type        _current;

  public:
    __constexpr istreambuf_iterator() __noexcept: _streambuf(nullptr), _current(traits_type::eof()) { }

    istreambuf_iterator(const istreambuf_iterator&) __noexcept = default;

    istreambuf_iterator(istream_type& is) __noexcept: _streambuf(is.rdbuf()), _current(traits_type::eof()) { }

    istreambuf_iterator(streambuf_type* buf) __noexcept: _streambuf(buf), _current(traits_type::eof()) { }

    ~istreambuf_iterator() = default;

    char_type operator*() const {
      return traits_type::to_char_type(getc());
    }

    istreambuf_iterator& operator++() {
      if (_streambuf == nullptr) {
        return *this;
      }

      _streambuf->sbumpc();
      _current = traits_type::eof();

      return *this;
    }

    istreambuf_iterator& operator++(int) {
      istreambuf_iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    bool equal(const istreambuf_iterator& other) const {
      bool this_eof  = traits_type::eq_int_type(getc(), traits_type::eof());
      bool other_eof = traits_type::eq_int_type(other.getc(), traits_type::eof());
      return this_eof == other_eof;
    }

  private:
    char_type getc() const {
      if (_streambuf == nullptr || traits_type::eq_int_type(_current, traits_type::eof())) {
        return traits_type::eof();
      }

      _current = _streambuf->sgetc();

      if (traits_type::eq_int_type(_current, traits_type::eof())) {
        _streambuf = nullptr;
      }

      return _current;
    }
  };

  template<typename Char, typename Traits>
  inline bool operator==(const istreambuf_iterator<Char, Traits>& lhs, const istreambuf_iterator<Char, Traits>& rhs) {
    return lhs.equal(rhs);
  }

  template<typename Char, typename Traits>
  inline bool operator!=(const istreambuf_iterator<Char, Traits>& lhs, const istreambuf_iterator<Char, Traits>& rhs) {
    return !lhs.equal(rhs);
  }
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_ITERATOR_ISTREAMBUF_ITERATOR_H_
