#ifndef CAPRESE_LIBC_INTERNAL_CXX_STRING_VIEW_BASIC_STRING_VIEW_H_
#define CAPRESE_LIBC_INTERNAL_CXX_STRING_VIEW_BASIC_STRING_VIEW_H_

#include <internal/attribute.h>
#include <internal/cxx/algorithm/minmax.h>
#include <internal/cxx/iterator/reverse_iterator.h>
#include <internal/cxx/memory/to_address.h>
#include <internal/cxx/stddef.h>
#include <internal/cxx/stdexcept/logic_error.h>
#include <internal/cxx/string/char_traits.h>
#include <internal/cxx/type_traits/type.h>
#include <internal/cxx/type_traits/type_relation.h>
#include <internal/exception.h>

namespace std {
  template<typename Char, typename Traits = char_traits<Char>>
  class basic_string_view {
    static_assert(!__is_array<Char>::value);
    static_assert(__is_trivial_t<Char>::value && __is_standard_layout_t<Char>::value);
    static_assert(__is_same_t<Char, typename Traits::char_type>::value);

  public:
    using traits_type            = Traits;
    using value_type             = Char;
    using pointer                = value_type*;
    using const_pointer          = const value_type*;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using iterator               = const value_type*;
    using const_iterator         = const value_type*;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using size_type              = __size_t;
    using difference_type        = __ptrdiff_t;

  private:
    const_pointer _data;
    size_type     _size;

  public:
    static constexpr size_type npos = size_type(-1);

  public:
    constexpr basic_string_view() noexcept: _data(nullptr), _size(0) { }

    constexpr basic_string_view(const_pointer str): _data(str), _size(traits_type::length(str)) { }

    constexpr basic_string_view(const_pointer str, size_type len): _data(str), _size(len) { }

    constexpr basic_string_view(const basic_string_view&) noexcept = default;
    ~basic_string_view()                                           = default;
    basic_string_view& operator=(const basic_string_view&)         = default;
    basic_string_view& operator=(basic_string_view&&)              = default;

#ifdef __CXX_STD_20__
    template<class It, class End>
    constexpr basic_string_view(It first, End last) noexcept(noexcept(last - first)): _data(__to_address(first)),
                                                                                      _size(last - first) { }
#endif // __CXX_STD_20__

#ifdef __CXX_STD_23__
    basic_string_view(nullptr_t) = delete;
#endif // __CXX_STD_23__

    constexpr const_iterator begin() const noexcept {
      return this->_data;
    }

    constexpr const_iterator end() const noexcept {
      return this->_data + this->_size;
    }

    constexpr const_iterator cbegin() const noexcept {
      return this->_data;
    }

    constexpr const_iterator cend() const noexcept {
      return this->_data + this->_size;
    }

    constexpr const_reverse_iterator rbegin() const noexcept {
      return const_reverse_iterator(this->end());
    }

    constexpr const_reverse_iterator rend() const noexcept {
      return const_reverse_iterator(this->begin());
    }

    constexpr const_reverse_iterator crbegin() const noexcept {
      return const_reverse_iterator(this->end());
    }

    constexpr const_reverse_iterator crend() const noexcept {
      return const_reverse_iterator(this->begin());
    }

    constexpr size_type size() const noexcept {
      return this->_size;
    }

    constexpr size_type length() const noexcept {
      return this->_size;
    }

    constexpr size_type max_size() const noexcept {
      return (npos - sizeof(this->_data) - sizeof(this->_size)) / sizeof(value_type) / 4;
    }

    [[nodiscard]] constexpr bool empty() const noexcept {
      return this->_size == 0;
    }

    constexpr const_reference operator[](size_type pos) const noexcept {
      return *(this->_data + pos);
    }

    constexpr const_reference at(size_type pos) const {
      if (pos >= this->_size) {
        __throw_exception(out_of_range("basic_string_view::at"));
      }

      return *(this->_data + pos);
    }

    constexpr const_reference front() const noexcept {
      return *this->_data;
    }

    constexpr const_reference back() const noexcept {
      return *(this->_data + this->_size - 1);
    }

    constexpr const_pointer data() const noexcept {
      return this->_data;
    }

    constexpr void remove_prefix(size_type n) noexcept {
      this->_data += n;
      this->_size -= n;
    }

    constexpr void remove_suffix(size_type n) noexcept {
      this->_size -= n;
    }

    constexpr void swap(basic_string_view& other) noexcept {
      auto tmp = *this;
      *this    = other;
      other    = tmp;
    }

    __constexpr_cxx_std_20 size_type copy(pointer str, size_type n, size_type pos = 0) const {
      if (pos > this->_size) {
        __throw_exception(out_of_range("basic_string_view::copy"));
      }

      size_type len = min(n, this->_size - pos);
      traits_type::copy(str, this->_data + pos, len);
      return len;
    }

    constexpr basic_string_view substr(size_type pos = 0, size_type n = npos) const {
      if (pos > this->_size) {
        __throw_exception(out_of_range("basic_string_view::substr"));
      }

      size_type len = min(n, this->_size - pos);
      return basic_string_view(this->_data + pos, len);
    }

    constexpr int compare(basic_string_view str) const noexcept {
      size_type len = min(this->_size, str._size);
      int       ret = traits_type::compare(this->_data, str._data, len);

      if (ret == 0) {
        ret = this->_size == str._size ? 0 : (this->_size < str._size ? -1 : 1);
      }

      return ret;
    }

    constexpr int compare(size_type pos, size_type n, basic_string_view str) const {
      return this->substr(pos, n).compare(str);
    }

    constexpr int compare(size_type pos, size_type n, basic_string_view str, size_type str_pos, size_type str_n) const {
      return this->substr(pos, n).compare(str.substr(str_pos, str_n));
    }

    constexpr int compare(const_pointer str) const noexcept {
      return this->compare(basic_string_view(str));
    }

    constexpr int compare(size_type pos, size_type n, const_pointer str) const {
      return this->substr(pos, n).compare(basic_string_view(str));
    }

    constexpr int compare(size_type pos, size_type n, const_pointer str, size_type str_n) const {
      return this->substr(pos, n).compare(basic_string_view(str, str_n));
    }

    constexpr size_type find(basic_string_view str, size_type pos = 0) const noexcept {
      return this->find(str._data, pos, str._size);
    }

    constexpr size_type find(value_type ch, size_type pos = 0) const noexcept {
      if (pos > this->_size) {
        return npos;
      }

      const_pointer first = traits_type::find(this->_data + pos, this->_size - pos, ch);

      return first ? first - this->_data : npos;
    }

    constexpr size_type find(const_pointer str, size_type pos, size_type n) const noexcept {
      if (pos > this->_size) {
        return npos;
      }

      if (n == 0) {
        return pos;
      }

      const_pointer first = str + pos;
      const_pointer last  = this->_data + this->_size;
      size_type     len   = this->_size - pos;
      while (len >= n) {
        first = traits_type::find(first, len - n + 1, str[0]);
        if (!first) {
          return npos;
        }

        if (traits_type::compare(first, str, n) == 0) {
          return first - this->_data;
        }

        ++first;
        len = last - first;
      }

      return npos;
    }

    constexpr size_type find(const_pointer str, size_type pos = 0) const noexcept {
      return this->find(str, pos, traits_type::length(str));
    }

    constexpr size_type rfind(basic_string_view str, size_type pos = npos) const noexcept {
      return this->rfind(str._data, pos, str._size);
    }

    constexpr size_type rfind(value_type ch, size_type pos = npos) const noexcept {
      if (this->_size == 0) {
        return npos;
      }

      size_type n = min(pos, this->_size - 1);
      while (true) {
        if (traits_type::eq(this->_data[n], ch)) {
          return n;
        }

        if (n == 0) {
          break;
        }

        --n;
      }

      return npos;
    }

    constexpr size_type rfind(const_pointer str, size_type pos, size_type n) const noexcept {
      if (n > this->_size) {
        return npos;
      }

      pos = min(this->_size - n, pos);
      while (pos > 0) {
        if (traits_type::compare(this->_data + pos, str, n) == 0) {
          return pos;
        }
        --pos;
      }

      return npos;
    }

    constexpr size_type rfind(const_pointer str, size_type pos = npos) const noexcept {
      return this->rfind(str, pos, traits_type::length(str));
    }

    constexpr size_type find_first_of(basic_string_view str, size_type pos = 0) const noexcept {
      return this->find_first_of(str._data, pos, str._size);
    }

    constexpr size_type find_first_of(value_type ch, size_type pos = 0) const noexcept {
      return this->find(ch, pos);
    }

    constexpr size_type find_first_of(const_pointer str, size_type pos, size_type n) const noexcept {
      if (pos >= this->_size) {
        return npos;
      }

      const_pointer first = this->_data + pos;
      const_pointer last  = this->_data + this->_size;
      while (first != last && traits_type::find(str, n, *first) == nullptr) {
        ++first;
      }

      return first != last ? first - this->_data : npos;
    }

    constexpr size_type find_first_of(const_pointer str, size_type pos = 0) const noexcept {
      return this->find_first_of(str, pos, traits_type::length(str));
    }

    constexpr size_type find_last_of(basic_string_view str, size_type pos = npos) const noexcept {
      return this->find_last_of(str._data, pos, str._size);
    }

    constexpr size_type find_last_of(value_type ch, size_type pos = npos) const noexcept {
      return this->rfind(ch, pos);
    }

    constexpr size_type find_last_of(const_pointer str, size_type pos, size_type n) const noexcept {
      if (this->_size == 0) {
        return npos;
      }

      size_type last = min(pos, this->_size - 1);
      while (true) {
        if (traits_type::find(str, n, this->_data[last])) {
          return last;
        }

        if (last == 0) {
          break;
        }

        --last;
      }

      return npos;
    }

    constexpr size_type find_last_of(const_pointer str, size_type pos = npos) const noexcept {
      return this->find_last_of(str, pos, traits_type::length(str));
    }

    constexpr size_type find_first_not_of(basic_string_view str, size_type pos = 0) const noexcept {
      return this->find_first_not_of(str._data, pos, str._size);
    }

    constexpr size_type find_first_not_of(value_type ch, size_type pos = 0) const noexcept {
      if (pos >= this->_size) {
        return npos;
      }

      const_pointer first = this->_data + pos;
      const_pointer last  = this->_data + this->_size;
      while (first != last && traits_type::eq(*first, ch)) {
        ++first;
      }

      return first != last ? first - this->_data : npos;
    }

    constexpr size_type find_first_not_of(const_pointer str, size_type pos, size_type n) const noexcept {
      if (pos >= this->_size) {
        return npos;
      }

      const_pointer first = this->_data + pos;
      const_pointer last  = this->_data + this->_size;
      while (first != last && traits_type::find(str, n, *first) != nullptr) {
        ++first;
      }

      return first != last ? first - this->_data : npos;
    }

    constexpr size_type find_first_not_of(const_pointer str, size_type pos = 0) const noexcept {
      return this->find_first_not_of(str, pos, traits_type::length(str));
    }

    constexpr size_type find_last_not_of(basic_string_view str, size_type pos = npos) const noexcept {
      return this->find_last_not_of(str._data, pos, str._size);
    }

    constexpr size_type find_last_not_of(value_type ch, size_type pos = npos) const noexcept {
      if (this->_size == 0) {
        return npos;
      }

      size_type last = min(pos, this->_size - 1);
      while (true) {
        if (!traits_type::eq(this->_data[last], ch)) {
          return last;
        }

        if (last == 0) {
          break;
        }

        --last;
      }

      return npos;
    }

    constexpr size_type find_last_not_of(const_pointer str, size_type pos, size_type n) const noexcept {
      if (this->_size == 0) {
        return npos;
      }

      size_type last = min(pos, this->_size - 1);
      while (true) {
        if (traits_type::find(str, n, this->_data[last]) == nullptr) {
          return last;
        }

        if (last == 0) {
          break;
        }

        --last;
      }

      return npos;
    }

    constexpr size_type find_last_not_of(const_pointer str, size_type pos = npos) const noexcept {
      return this->find_last_not_of(str, pos, traits_type::length(str));
    }

#ifdef __CXX_STD_20__

    constexpr bool starts_with(basic_string_view str) const noexcept {
      return this->_size >= str._size && this->compare(0, str._size, str) == 0;
    }

    constexpr bool starts_with(value_type ch) const noexcept {
      return this->_size >= 1 && traits_type::eq(this->front(), ch);
    }

    constexpr bool starts_with(const_pointer str) const noexcept {
      return this->starts_with(basic_string_view(str));
    }

    constexpr bool ends_with(basic_string_view str) const noexcept {
      return this->_size >= str._size && traits_type::compare(end() - str._size, str._data, str._size) == 0;
    }

    constexpr bool ends_with(value_type ch) const noexcept {
      return this->_size >= 1 && traits_type::eq(this->back(), ch);
    }

    constexpr bool ends_with(const_pointer str) const noexcept {
      return this->ends_with(basic_string_view(str));
    }

#endif // __CXX_STD_20__

#ifdef __CXX_STD_23__

    constexpr bool contains(basic_string_view str) const noexcept {
      return this->find(str) != npos;
    }

    constexpr bool contains(value_type ch) const noexcept {
      return this->find(ch) != npos;
    }

    constexpr bool contains(const_pointer str) const noexcept {
      return this->find(str) != npos;
    }

#endif // __CXX_STD_23__
  };

  template<typename Char, typename Traits>
  constexpr bool operator==(basic_string_view<Char, Traits> lhs, basic_string_view<Char, Traits> rhs) noexcept {
    return lhs.size() == rhs.size() && lhs.compare(rhs) == 0;
  }

#if __cpp_lib_three_way_comparison

  template<typename Char, typename Traits>
  constexpr auto operator<=>(basic_string_view<Char, Traits> lhs, basic_string_view<Char, Traits> rhs) noexcept -> decltype(__char_traits_comparison_category<Traits>(0)) {
    return __char_traits_comparison_category<Traits>(lhs.compare(rhs));
  }

#else // ^^^ __cpp_lib_three_way_comparison ^^^ / vvv !__cpp_lib_three_way_comparison vvv

  template<typename Char, typename Traits>
  constexpr bool operator!=(basic_string_view<Char, Traits> lhs, basic_string_view<Char, Traits> rhs) noexcept {
    return !(lhs == rhs);
  }

  template<typename Char, typename Traits>
  constexpr bool operator<(basic_string_view<Char, Traits> lhs, basic_string_view<Char, Traits> rhs) noexcept {
    return lhs.compare(rhs) < 0;
  }

  template<typename Char, typename Traits>
  constexpr bool operator<=(basic_string_view<Char, Traits> lhs, basic_string_view<Char, Traits> rhs) noexcept {
    return lhs.compare(rhs) <= 0;
  }

  template<typename Char, typename Traits>
  constexpr bool operator>(basic_string_view<Char, Traits> lhs, basic_string_view<Char, Traits> rhs) noexcept {
    return lhs.compare(rhs) > 0;
  }

  template<typename Char, typename Traits>
  constexpr bool operator>=(basic_string_view<Char, Traits> lhs, basic_string_view<Char, Traits> rhs) noexcept {
    return lhs.compare(rhs) >= 0;
  }

#endif // !__cpp_lib_three_way_comparison
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_STRING_VIEW_BASIC_STRING_VIEW_H_
