#ifndef CAPRESE_LIBC_INTERNAL_CXX_STRING_BASIC_STRING_H_
#define CAPRESE_LIBC_INTERNAL_CXX_STRING_BASIC_STRING_H_

#include <internal/attribute.h>
#include <internal/cxx/algorithm/minmax.h>
#include <internal/cxx/iterator/functions.h>
#include <internal/cxx/memory/allocator.h>
#include <internal/cxx/memory/allocator_traits.h>
#include <internal/cxx/stdexcept/logic_error.h>
#include <internal/cxx/stl_base/str_storage.h>
#include <internal/cxx/stl_base/vla.h>
#include <internal/cxx/string/char_traits.h>
#include <internal/cxx/utility/fwd.h>
#include <internal/exception.h>

namespace std {
  template<typename Char, typename Traits = char_traits<Char>, typename Allocator = allocator<Char>>
  class __basic_string: public __vla<__string_storage<Char, Traits, Allocator>> {
    using __storage = __string_storage<Char, Traits, Allocator>;
    using __base    = __vla<__storage>;

  public:
    using traits_type            = typename __storage::traits_type;
    using value_type             = typename __base::value_type;
    using allocator_type         = typename __base::allocator_type;
    using size_type              = typename __base::size_type;
    using difference_type        = typename __base::difference_type;
    using reference              = typename __base::reference;
    using const_reference        = typename __base::const_reference;
    using pointer                = typename __base::pointer;
    using const_pointer          = typename __base::const_pointer;
    using iterator               = typename __base::iterator;
    using const_iterator         = typename __base::const_iterator;
    using reverse_iterator       = typename __base::reverse_iterator;
    using const_reverse_iterator = typename __base::const_reverse_iterator;

  public:
    static constexpr size_type npos = static_cast<size_type>(-1);

  public:
    __constexpr_cxx_std_20 __basic_string() __noexcept_if_cxx_std_17(noexcept(allocator_type())) = default;
    __constexpr_cxx_std_20 __basic_string(const __basic_string& other)                           = default;
    __constexpr_cxx_std_20 __basic_string(__basic_string&& other)                                = default;

    __constexpr_cxx_std_20 explicit __basic_string(const allocator_type& allocator) __noexcept_cxx_std_17: __base(allocator) { }

    __constexpr_cxx_std_20 __basic_string(const __basic_string& other, size_type pos, size_type n, const allocator_type& allocator = allocator_type()): __base(allocator) {
      __if_unlikely (pos > other.size()) {
        __throw_exception(out_of_range("pos > other.size()"));
      }

      this->assign(other, pos, n);
    }

    __constexpr_cxx_std_20 __basic_string(const __basic_string& other, size_type pos, const allocator_type& allocator = allocator_type()): __basic_string(other, pos, npos, allocator) { }

    __constexpr_cxx_std_20 __basic_string(const_pointer str, size_type n, const allocator_type& allocator = allocator_type()): __base(allocator) {
      this->assign(str, n);
    }

    __constexpr_cxx_std_20 __basic_string(const_pointer str, const allocator_type& allocator = allocator_type()): __base(allocator) {
      this->assign(str);
    }

#ifdef __CXX_STD_23__
    __basic_string(nullptr_t) = delete;
#endif // __CXX_STD_23__

    __constexpr_cxx_std_20 __basic_string(size_type n, value_type ch, const allocator_type& allocator = allocator_type()): __base(allocator) {
      this->assign(n, ch);
    }

    template<typename InputIterator>
    __constexpr_cxx_std_20 __basic_string(InputIterator first, InputIterator last, const allocator_type& allocator = allocator_type()): __base(allocator) {
      this->assign(first, last);
    }

    __constexpr_cxx_std_20 __basic_string(initializer_list<value_type> init_list, const allocator_type& allocator = allocator_type()): __base(allocator) {
      this->assign(init_list);
    }

    __constexpr_cxx_std_20 __basic_string(const __basic_string& other, const allocator_type& allocator): __base(other, allocator) { }

    __constexpr_cxx_std_20 __basic_string(__basic_string&& other, const allocator_type& allocator): __base(move(other), allocator) { }

    __constexpr_cxx_std_20 __basic_string& operator=(const __basic_string& other) = default;

    __constexpr_cxx_std_20 __basic_string& operator=(__basic_string&& other)
        __noexcept_if_cxx_std_17(allocator_traits<allocator_type>::propagate_on_container_move_assignment::value || allocator_traits<allocator_type>::is_always_equal::value) = default;

    __constexpr_cxx_std_20 __basic_string& operator=(const_pointer str) {
      return *this = __basic_string(str);
    }

    __constexpr_cxx_std_20 __basic_string& operator=(value_type ch) {
      return *this = __basic_string(1, ch);
    }

    __constexpr_cxx_std_20 __basic_string& operator=(initializer_list<value_type> init_list) {
      return *this = __basic_string(init_list);
    }

#ifdef __CXX_STD_23__
    __basic_string& operator=(nullptr_t) = delete;
#endif // __CXX_STD_23__

    __constexpr_cxx_std_20 size_type length() const __noexcept {
      return __base::size();
    }

    __constexpr_cxx_std_20 __basic_string& operator+=(const __basic_string& str) {
      this->append(str);
      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& operator+=(const_pointer str) {
      this->append(str);
      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& operator+=(value_type ch) {
      this->append(1, ch);
      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& operator+=(initializer_list<value_type> init_list) {
      this->append(init_list);
      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& append(const __basic_string& str) {
      return this->append(str.data(), str.size());
    }

    __constexpr_cxx_std_20 __basic_string& append(const __basic_string& str, size_type pos, size_type n = npos) {
      __if_unlikely (pos > str.size()) {
        __throw_exception(out_of_range("pos > str.size()"));
      }

      return this->append(str.data() + pos, min(str.size() - pos, n));
    }

    __constexpr_cxx_std_20 __basic_string& append(const_pointer str, size_type n) {
      this->reserve(this->size() + n);

      for (size_type i = 0; i < n; ++i) {
        __base::push_back(str[i]);
      }
      __base::push_back(value_type());

      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& append(const_pointer str) {
      return this->append(str, traits_type::length(str));
    }

    __constexpr_cxx_std_20 __basic_string& append(size_type n, value_type ch) {
      this->reserve(this->size() + n);

      for (size_type i = 0; i < n; ++i) {
        __base::push_back(ch);
      }
      __base::push_back(value_type());

      return *this;
    }

    template<typename InputIterator>
    __constexpr_cxx_std_20 __basic_string& append(InputIterator first, InputIterator last) {
      size_type length = distance(first, last);

      this->reserve(this->size() + length);

      for (auto it = first; it != last; ++it) {
        __base::push_back(*it);
      }
      __base::push_back(value_type());

      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& append(initializer_list<value_type> init_list) {
      return this->append(init_list.begin(), init_list.end());
    }

    __constexpr_cxx_std_20 __basic_string& push_back(value_type ch) {
      __base::push_back(ch);
      __base::push_back(value_type());
      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& assign(const __basic_string& str) {
      return *this = str;
    }

    __constexpr_cxx_std_20 __basic_string& assign(__basic_string&& str) {
      return *this = move(str);
    }

    __constexpr_cxx_std_20 __basic_string& assign(const __basic_string& str, size_type pos, size_type n = npos) {
      __if_unlikely (pos > str.size()) {
        __throw_exception(out_of_range("pos > str.size()"));
      }

      return this->assign(str.data() + pos, min(str.size() - pos, n));
    }

    __constexpr_cxx_std_20 __basic_string& assign(const_pointer str, size_type n) {
      __base::assign(str, str + n);
      __base::push_back(value_type());
      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& assign(const_pointer str) {
      return this->assign(str, traits_type::length(str));
    }

    __constexpr_cxx_std_20 __basic_string& insert(size_type pos, const __basic_string& str) {
      return this->insert(pos, str.data(), str.size());
    }

    __constexpr_cxx_std_20 __basic_string& insert(size_type pos1, const __basic_string& str, size_type pos2, size_type n = npos) {
      return this->insert(pos1, str.data() + pos2, min(str.size() - pos2, n));
    }

    __constexpr_cxx_std_20 __basic_string& insert(size_type pos, const_pointer str, size_type n) {
      __if_unlikely (pos > this->size()) {
        __throw_exception(out_of_range("pos > size()"));
      }

      __base::insert(this->cbegin() + pos, str, str + n);

      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& insert(size_type pos, const_pointer str) {
      return insert(pos, str, traits_type::length(str));
    }

    __constexpr_cxx_std_20 __basic_string& insert(size_type pos, size_type n, value_type ch) {
      __if_unlikely (pos > this->size()) {
        __throw_exception(out_of_range("pos > size()"));
      }

      __base::insert(this->cbegin() + pos, n, ch);

      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& erase(size_type pos = 0, size_type n = npos) {
      __if_unlikely (pos > this->size()) {
        __throw_exception(out_of_range("pos > size()"));
      }

      __base::erase(this->cbegin() + pos, this->cbegin() + pos + min(this->size() - pos, n));

      return *this;
    }

    __constexpr_cxx_std_20 void pop_back() {
      __base::pop_back();
      __base::pop_back();
      __base::push_back(value_type());
    }

    __constexpr_cxx_std_20 const_pointer c_str() const __noexcept {
      return __base::data();
    }

    __constexpr_cxx_std_20 int compare(const __basic_string& other) const __noexcept_cxx_std_11 {
      int result = traits_type::compare(this->data(), other.data(), min(this->size(), other.size()));
      if (result != 0) {
        return result;
      } else {
        if (this->size() < other.size()) {
          return -1;
        } else if (this->size() > other.size()) {
          return 1;
        } else {
          return 0;
        }
      }
    }

    __constexpr_cxx_std_20 int compare(size_type pos1, size_type n1, const __basic_string& str) const {
      return __basic_string(*this, pos1, n1).compare(str);
    }

    __constexpr_cxx_std_20 int compare(size_type pos1, size_type n1, const __basic_string& str, size_type pos2, size_type n2 = npos) const {
      return __basic_string(*this, pos1, n1).compare(__basic_string(str, pos2, n2));
    }

    __constexpr_cxx_std_20 int compare(const Char* s) const {
      return this->compare(__basic_string(s));
    }

    __constexpr_cxx_std_20 int compare(size_type pos, size_type n1, const Char* s) const {
      return __basic_string(*this, pos, n1).compare(__basic_string(s));
    }

    __constexpr_cxx_std_20 int compare(size_type pos, size_type n1, const Char* s, size_type n2) const {
      return __basic_string(*this, pos, n1).compare(__basic_string(s, n2));
    }
  };

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 typename __basic_string<Char, Traits, Allocator>::iterator operator+(typename __basic_string<Char, Traits, Allocator>::iterator::difference_type lhs,
                                                                                              typename __basic_string<Char, Traits, Allocator>::iterator                  rhs) __noexcept {
    return rhs += lhs;
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 typename __basic_string<Char, Traits, Allocator>::const_iterator operator+(typename __basic_string<Char, Traits, Allocator>::const_iterator::difference_type lhs,
                                                                                                    typename __basic_string<Char, Traits, Allocator>::const_iterator                  rhs) __noexcept {
    return rhs += lhs;
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 __basic_string<Char, Traits, Allocator> operator+(const __basic_string<Char, Traits, Allocator>& lhs, const __basic_string<Char, Traits, Allocator>& rhs) {
    __basic_string<Char, Traits, Allocator> r = lhs;
    r.append(rhs);
    return r;
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 __basic_string<Char, Traits, Allocator> operator+(__basic_string<Char, Traits, Allocator>&& lhs, const __basic_string<Char, Traits, Allocator>& rhs) {
    lhs.append(rhs);
    return std::move(lhs);
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 __basic_string<Char, Traits, Allocator> operator+(const __basic_string<Char, Traits, Allocator>& lhs, __basic_string<Char, Traits, Allocator>&& rhs) {
    rhs.insert(0, lhs);
    return std::move(rhs);
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 __basic_string<Char, Traits, Allocator> operator+(__basic_string<Char, Traits, Allocator>&& lhs, __basic_string<Char, Traits, Allocator>&& rhs) {
    lhs.append(rhs);
    return std::move(lhs);
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 __basic_string<Char, Traits, Allocator> operator+(const Char* lhs, const __basic_string<Char, Traits, Allocator>& rhs) {
    __basic_string<Char, Traits, Allocator> r = rhs;
    r.insert(0, lhs);
    return r;
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 __basic_string<Char, Traits, Allocator> operator+(const Char* lhs, __basic_string<Char, Traits, Allocator>&& rhs) {
    rhs.insert(0, lhs);
    return std::move(rhs);
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 __basic_string<Char, Traits, Allocator> operator+(Char lhs, const __basic_string<Char, Traits, Allocator>& rhs) {
    __basic_string<Char, Traits, Allocator> r = rhs;
    r.insert(0, 1, lhs);
    return r;
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 __basic_string<Char, Traits, Allocator> operator+(Char lhs, __basic_string<Char, Traits, Allocator>&& rhs) {
    rhs.insert(rhs.begin(), lhs);
    return std::move(rhs);
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 __basic_string<Char, Traits, Allocator> operator+(const __basic_string<Char, Traits, Allocator>& lhs, const Char* rhs) {
    __basic_string<Char, Traits, Allocator> r = lhs;
    r.append(rhs);
    return r;
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 __basic_string<Char, Traits, Allocator> operator+(__basic_string<Char, Traits, Allocator>&& lhs, const Char* rhs) {
    lhs.append(rhs);
    return std::move(lhs);
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 __basic_string<Char, Traits, Allocator> operator+(const __basic_string<Char, Traits, Allocator>& lhs, Char rhs) {
    __basic_string<Char, Traits, Allocator> r = lhs;
    r.push_back(rhs);
    return r;
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 __basic_string<Char, Traits, Allocator> operator+(__basic_string<Char, Traits, Allocator>&& lhs, Char rhs) {
    lhs.push_back(rhs);
    return std::move(lhs);
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 bool operator==(const __basic_string<Char, Traits, Allocator>& lhs, const __basic_string<Char, Traits, Allocator>& rhs) __noexcept_cxx_std_11 {
    return lhs.compare(rhs) == 0;
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 bool operator==(const __basic_string<Char, Traits, Allocator>& lhs, const Char* rhs) {
    return lhs.compare(rhs) == 0;
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 bool operator==(const Char* lhs, const __basic_string<Char, Traits, Allocator>& rhs) {
    return rhs == lhs;
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 bool operator!=(const __basic_string<Char, Traits, Allocator>& lhs, const __basic_string<Char, Traits, Allocator>& rhs) __noexcept_cxx_std_11 {
    return !(lhs == rhs);
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 bool operator!=(const __basic_string<Char, Traits, Allocator>& lhs, const Char* rhs) {
    return !(lhs == rhs);
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 bool operator!=(const Char* lhs, const __basic_string<Char, Traits, Allocator>& rhs) {
    return !(lhs == rhs);
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 bool operator<(const __basic_string<Char, Traits, Allocator>& lhs, const __basic_string<Char, Traits, Allocator>& rhs) __noexcept_cxx_std_11 {
    return lhs.compare(rhs) < 0;
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 bool operator<(const __basic_string<Char, Traits, Allocator>& lhs, const Char* rhs) {
    return lhs.compare(rhs) < 0;
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 bool operator<(const Char* lhs, const __basic_string<Char, Traits, Allocator>& rhs) {
    return rhs.compare(lhs) > 0;
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 bool operator<=(const __basic_string<Char, Traits, Allocator>& lhs, const __basic_string<Char, Traits, Allocator>& rhs) __noexcept_cxx_std_11 {
    return lhs.compare(rhs) <= 0;
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 bool operator<=(const __basic_string<Char, Traits, Allocator>& lhs, const Char* rhs) {
    return lhs.compare(rhs) <= 0;
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 bool operator<=(const Char* lhs, const __basic_string<Char, Traits, Allocator>& rhs) {
    return rhs.compare(lhs) >= 0;
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 bool operator>(const __basic_string<Char, Traits, Allocator>& lhs, const __basic_string<Char, Traits, Allocator>& rhs) __noexcept_cxx_std_11 {
    return lhs.compare(rhs) > 0;
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 bool operator>(const __basic_string<Char, Traits, Allocator>& lhs, const Char* rhs) {
    return lhs.compare(rhs) > 0;
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 bool operator>(const Char* lhs, const __basic_string<Char, Traits, Allocator>& rhs) {
    return rhs.compare(lhs) < 0;
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 bool operator>=(const __basic_string<Char, Traits, Allocator>& lhs, const __basic_string<Char, Traits, Allocator>& rhs) __noexcept_cxx_std_11 {
    return lhs.compare(rhs) >= 0;
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 bool operator>=(const __basic_string<Char, Traits, Allocator>& lhs, const Char* rhs) {
    return lhs.compare(rhs) >= 0;
  }

  template<typename Char, typename Traits, typename Allocator>
  __constexpr_cxx_std_20 bool operator>=(const Char* lhs, const __basic_string<Char, Traits, Allocator>& rhs) {
    return rhs.compare(lhs) <= 0;
  }
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_STRING_BASIC_STRING_H_
