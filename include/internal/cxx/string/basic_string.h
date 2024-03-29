#ifndef CAPRESE_LIBC_INTERNAL_CXX_STRING_BASIC_STRING_H_
#define CAPRESE_LIBC_INTERNAL_CXX_STRING_BASIC_STRING_H_

#include <initializer_list>
#include <internal/attribute.h>
#include <internal/cxx/algorithm/minmax.h>
#include <internal/cxx/algorithm/seq.h>
#include <internal/cxx/iterator/functions.h>
#include <internal/cxx/iterator/traits.h>
#include <internal/cxx/memory/allocator.h>
#include <internal/cxx/memory/allocator_traits.h>
#include <internal/cxx/stdexcept/logic_error.h>
#include <internal/cxx/stl_base/str_storage.h>
#include <internal/cxx/stl_base/vla.h>
#include <internal/cxx/string/char_traits.h>
#include <internal/cxx/type_traits/detection.h>
#include <internal/cxx/type_traits/logic.h>
#include <internal/cxx/type_traits/type_relation.h>
#include <internal/cxx/utility/fwd.h>
#include <internal/exception.h>

#ifdef __CXX_STD_17__

#include <internal/cxx/string_view/basic_string_view.h>

#endif // __CXX_STD_17__

namespace std {
  template<typename Char, typename Traits = char_traits<Char>, typename Allocator = allocator<Char>>
  class __basic_string: public __vla<__string_storage<Char, Traits, Allocator>> {
    using __storage = __string_storage<Char, Traits, Allocator>;
    using __base    = __vla<__storage>;

#ifdef __CXX_STD_17__

    using __view = basic_string_view<Char, Traits>;

#endif // __CXX_STD_17__

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

  private:
#ifdef __CXX_STD_17__
    template<typename T, typename U = void>
    using __if_view = typename __enable_if<
        __conjunction<__is_convertible<const T&, __view>, __negation<__is_convertible<const T*, const __basic_string*>>, __negation<__is_convertible<const T&, const_pointer>>>::value,
        U>::type;

    template<typename StringView>
    static __if_view<StringView, __view> __to_view(const StringView& view) {
      return __view(view);
    }

    struct __view_wrapper {
      __view _view;

      explicit __view_wrapper(const __view& view): _view(view) { }
    };

    __constexpr_cxx_std_20 __basic_string(__view_wrapper wrapper, const allocator_type& allocator): __basic_string(wrapper._view.data(), wrapper._view.size(), allocator) { }
#endif // __CXX_STD_17__

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

#ifdef __CXX_STD_17__

    template<typename StringView, typename = __if_view<StringView>>
    __constexpr_cxx_std_20 explicit __basic_string(const StringView& view, const allocator_type& allocator = allocator_type()): __basic_string(__view_wrapper(__to_view(view)), allocator) { }

    template<typename StringView, typename = __if_view<StringView>>
    __constexpr_cxx_std_20 __basic_string(const StringView& view, size_type pos, size_type n, const allocator_type& allocator = allocator_type())
        : __basic_string(__view_wrapper(__to_view(view).substr(pos, n)), allocator) { }

#endif // __CXX_STD_17__

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

#ifdef __CXX_STD_17__

    template<typename StringView>
    __constexpr_cxx_std_20 __if_view<StringView, __basic_string&> operator=(const StringView& view) {
      return *this = __basic_string(view);
    }

#endif // __CXX_STD_17__

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

#ifdef __CXX_STD_17__

    template<typename StringView>
    __constexpr_cxx_std_20 __if_view<StringView, __basic_string&> operator+=(const StringView& view) {
      this->append(view);
      return *this;
    }

#endif // __CXX_STD_17__

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
      __base::reserve(__base::size() + n);

      for (size_type i = 0; i < n; ++i) {
        __base::push_back(str[i]);
      }

      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& append(const_pointer str) {
      return this->append(str, traits_type::length(str));
    }

    __constexpr_cxx_std_20 __basic_string& append(size_type n, value_type ch) {
      __base::reserve(__base::size() + n);

      for (size_type i = 0; i < n; ++i) {
        __base::push_back(ch);
      }

      return *this;
    }

    template<typename InputIterator>
    __constexpr_cxx_std_20 __basic_string& append(InputIterator first, InputIterator last) {
      size_type length = distance(first, last);

      __base::reserve(__base::size() + length);

      for (auto it = first; it != last; ++it) {
        __base::push_back(*it);
      }

      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& append(initializer_list<value_type> init_list) {
      return this->append(init_list.begin(), init_list.end());
    }

#ifdef __CXX_STD_17__

    template<typename StringView>
    __constexpr_cxx_std_20 __if_view<StringView, __basic_string&> append(const StringView& view) {
      __view sv = __to_view(view);
      return this->append(sv.data(), sv.size());
    }

    template<typename StringView>
    __constexpr_cxx_std_20 __if_view<StringView, __basic_string&> append(const StringView& view, size_type pos, size_type n = npos) {
      __view sv = __to_view(view).substr(pos, n);
      return this->append(sv.data(), sv.size());
    }

#endif // __CXX_STD_17__

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
      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& assign(const_pointer str) {
      return this->assign(str, traits_type::length(str));
    }

#ifdef __CXX_STD_17__

    template<typename StringView>
    __constexpr_cxx_std_20 __if_view<StringView, __basic_string&> assign(const StringView& view) {
      __view sv = __to_view(view);
      return this->assign(sv.data(), sv.size());
    }

    template<typename StringView>
    __constexpr_cxx_std_20 __if_view<StringView, __basic_string&> assign(const StringView& view, size_type pos, size_type n = npos) {
      __view sv = __to_view(view).substr(pos, n);
      return this->assign(sv.data(), sv.size());
    }

#endif // __CXX_STD_17__

    __constexpr_cxx_std_20 __basic_string& insert(size_type pos, const __basic_string& str) {
      return this->insert(pos, str.data(), str.size());
    }

    __constexpr_cxx_std_20 __basic_string& insert(size_type pos1, const __basic_string& str, size_type pos2, size_type n = npos) {
      return this->insert(pos1, str.data() + pos2, min(str.size() - pos2, n));
    }

    __constexpr_cxx_std_20 __basic_string& insert(size_type pos, const_pointer str, size_type n) {
      __if_unlikely (pos > __base::size()) {
        __throw_exception(out_of_range("pos > size()"));
      }

      __base::insert(__base::cbegin() + pos, str, str + n);

      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& insert(size_type pos, const_pointer str) {
      return insert(pos, str, traits_type::length(str));
    }

    __constexpr_cxx_std_20 __basic_string& insert(size_type pos, size_type n, value_type ch) {
      __if_unlikely (pos > __base::size()) {
        __throw_exception(out_of_range("pos > size()"));
      }

      __base::insert(__base::cbegin() + pos, n, ch);

      return *this;
    }

#ifdef __CXX_STD_17__

    template<typename StringView>
    __constexpr_cxx_std_20 __if_view<StringView, __basic_string&> insert(size_type pos, const StringView& view) {
      __view sv = __to_view(view);
      return this->insert(pos, sv.data(), sv.size());
    }

    template<typename StringView>
    __constexpr_cxx_std_20 __if_view<StringView, __basic_string&> insert(size_type pos1, const StringView& view, size_type pos2, size_type n = npos) {
      __view sv = __to_view(view).substr(pos2, n);
      return this->insert(pos1, sv.data(), sv.size());
    }

#endif // __CXX_STD_17__

    __constexpr_cxx_std_20 __basic_string& erase(size_type pos = 0, size_type n = npos) {
      __if_unlikely (pos > __base::size()) {
        __throw_exception(out_of_range("pos > size()"));
      }

      __base::erase(__base::cbegin() + pos, __base::cbegin() + pos + min(__base::size() - pos, n));

      return *this;
    }

    __constexpr_cxx_std_20 const_pointer c_str() const __noexcept_cxx_std_11 {
      return __base::data();
    }

#ifdef __CXX_STD_17__

    __constexpr_cxx_std_20 operator __view() const noexcept {
      return __view(__base::data(), __base::size());
    }

#endif // __CXX_STD_17__

    __constexpr_cxx_std_20 size_type copy(pointer str, size_type n, size_type pos = 0) const {
      __if_unlikely (pos > __base::size()) {
        __throw_exception(out_of_range("pos > size()"));
      }

      size_type length = min(__base::size() - pos, n);

      traits_type::copy(str, __base::data() + pos, length);

      return length;
    }

    __constexpr_cxx_std_20 size_type find(const __basic_string& str, size_type pos = 0) const __noexcept_cxx_std_11 {
      if (pos >= __base::size()) {
        return npos;
      }

      auto iter = search(__base::begin() + pos, __base::end(), str.begin(), str.end(), traits_type::eq);

      if (__base::end() == iter) {
        return npos;
      } else {
        return distance(__base::begin(), iter);
      }
    }

    __constexpr_cxx_std_20 size_type find(const_pointer str, size_type pos, size_type n) const {
      if (pos >= __base::size()) {
        return npos;
      }

      auto iter = search(__base::begin() + pos, __base::end(), str, str + n, traits_type::eq);

      if (__base::end() == iter) {
        return npos;
      } else {
        return distance(__base::begin(), iter);
      }
    }

    __constexpr_cxx_std_20 size_type find(const_pointer str, size_type pos = 0) const {
      return this->find(str, pos, traits_type::length(str));
    }

    __constexpr_cxx_std_20 size_type find(value_type ch, size_type pos = 0) const {
      if (pos >= __base::size()) {
        return npos;
      }

      const_pointer ptr = traits_type::find(this->c_str() + pos, __base::size(), ch);
      if (ptr == nullptr) {
        return npos;
      } else {
        return distance(this->c_str(), ptr);
      }
    }

#ifdef __CXX_STD_17__

    template<typename StringView>
    __constexpr_cxx_std_20 __if_view<StringView, size_type> find(const StringView& view, size_type pos = 0) const {
      __view sv = __to_view(view);
      return this->find(sv.data(), pos, sv.size());
    }

#endif // __CXX_STD_17__

    __constexpr_cxx_std_20 size_type rfind(const __basic_string& str, size_type pos = npos) const __noexcept_cxx_std_11 {
      if (pos > __base::size()) {
        pos = __base::size();
      }

      auto iter = find_end(__base::begin(), __base::begin() + pos, str.begin(), str.end(), traits_type::eq);

      if (__base::begin() + pos == iter) {
        return npos;
      } else {
        return distance(__base::begin(), iter);
      }
    }

    __constexpr_cxx_std_20 size_type rfind(const_pointer str, size_type pos, size_type n) const {
      if (pos > __base::size()) {
        pos = __base::size();
      }

      auto iter = find_end(__base::begin(), __base::begin() + pos, str, str + n, traits_type::eq);

      if (__base::begin() + pos == iter) {
        return npos;
      } else {
        return distance(__base::begin(), iter);
      }
    }

    __constexpr_cxx_std_20 size_type rfind(const_pointer str, size_type pos = npos) const {
      return this->rfind(str, pos, traits_type::length(str));
    }

    __constexpr_cxx_std_20 size_type rfind(value_type ch, size_type pos = npos) const {
      return this->rfind(&ch, pos, 1);
    }

#ifdef __CXX_STD_17__

    template<typename StringView>
    __constexpr_cxx_std_20 __if_view<StringView, size_type> rfind(const StringView& view, size_type pos = 0) const {
      __view sv = __to_view(view);
      return this->rfind(sv.data(), pos, sv.size());
    }

#endif // __CXX_STD_17__

    __constexpr_cxx_std_20 __basic_string substr(size_type pos = 0, size_type n = npos) const __lvalue_ref_cxx_std_23 {
      __if_unlikely (pos > __base::size()) {
        __throw_exception(out_of_range("pos > size()"));
      }

      return __basic_string(*this, pos, n);
    }

#ifdef __CXX_STD_23__

    constexpr __basic_string substr(size_type pos = 0, size_type n = npos) && {
      __if_unlikely (pos > __base::size()) {
        __throw_exception(out_of_range("pos > size()"));
      }

      return __basic_string(move(*this), pos, n);
    }

#endif // __CXX_STD_23__

    __constexpr_cxx_std_20 int compare(const __basic_string& other) const __noexcept_cxx_std_11 {
      int result = traits_type::compare(__base::data(), other.data(), min(__base::size(), other.size()));
      if (result != 0) {
        return result;
      } else {
        if (__base::size() < other.size()) {
          return -1;
        } else if (__base::size() > other.size()) {
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

#ifdef __CXX_STD_17__

    template<typename StringView>
    __constexpr_cxx_std_20 __if_view<StringView, int> compare(const StringView& view) const {
      __view sv = __to_view(view);

      size_type len = min(__base::size(), sv.size());
      int       ret = traits_type::compare(__base::data(), sv.data(), len);

      if (ret == 0) {
        ret = __base::size() == sv.size() ? 0 : (__base::size() < sv.size() ? -1 : 1);
      }

      return ret;
    }

    template<typename StringView>
    __constexpr_cxx_std_20 __if_view<StringView, int> compare(size_type pos, size_type n, const StringView& view) const {
      __view sv = __to_view(view);
      return __view(*this).substr(pos, n).compare(sv);
    }

    template<typename StringView>
    __constexpr_cxx_std_20 __if_view<StringView, int> compare(size_type pos1, size_type n1, const StringView& view, size_type pos2, size_type n2 = npos) const {
      __view sv = __to_view(view).substr(pos2, n2);
      return __view(*this).substr(pos1, n2).compare(sv);
    }

#endif // __CXX_STD_17__

#ifdef __CXX_STD_20__

    constexpr bool starts_with(value_type ch) const noexcept {
      return __view(__base::data(), __base::size()).starts_with(ch);
    }

    constexpr bool starts_with(const_pointer str) const noexcept {
      return __view(__base::data(), __base::size()).starts_with(str);
    }

    constexpr bool starts_with(__view str) const noexcept {
      return __view(__base::data(), __base::size()).starts_with(str);
    }

    constexpr bool ends_with(value_type ch) const noexcept {
      return __view(__base::data(), __base::size()).ends_with(ch);
    }

    constexpr bool ends_with(const_pointer str) const noexcept {
      return __view(__base::data(), __base::size()).ends_with(str);
    }

    constexpr bool ends_with(__view str) const noexcept {
      return __view(__base::data(), __base::size()).ends_with(str);
    }

#endif // __CXX_STD_20__

#ifdef __CXX_STD_23__

    constexpr bool contains(value_type ch) const noexcept {
      return __view(__base::data(), __base::size()).contains(ch);
    }

    constexpr bool contains(const_pointer str) const noexcept {
      return __view(__base::data(), __base::size()).contains(str);
    }

    constexpr bool contains(__view str) const noexcept {
      return __view(__base::data(), __base::size()).contains(str);
    }

#endif // __CXX_STD_23__
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

#if __cpp_lib_three_way_comparison

  template<typename Char, typename Traits, typename Allocator>
  inline auto operator<=>(const __basic_string<Char, Traits, Allocator>& lhs, const __basic_string<Char, Traits, Allocator>& rhs) noexcept -> decltype(__char_traits_comparison_category<Traits>(0)) {
    return __char_traits_comparison_category<Traits>(lhs.compare(rhs));
  }

  template<typename Char, typename Traits, typename Allocator>
  inline auto operator<=>(const __basic_string<Char, Traits, Allocator>& lhs, const Char* rhs) noexcept -> decltype(__char_traits_comparison_category<Traits>(0)) {
    return __char_traits_comparison_category<Traits>(lhs.compare(rhs));
  }

#else // ^^^ __cpp_lib_three_way_comparison ^^^ / vvv !__cpp_lib_three_way_comparison vvv

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

#endif // !__cpp_lib_three_way_comparison

#if __cpp_deduction_guides

  template<typename InputIterator, typename Allocator = allocator<typename iterator_traits<InputIterator>::value_type>>
  __basic_string(InputIterator, InputIterator, Allocator = Allocator())
      -> __basic_string<typename iterator_traits<InputIterator>::value_type, char_traits<typename iterator_traits<InputIterator>::value_type>, Allocator>;

#ifdef __CXX_STD_20__

  template<typename Char, typename Traits, typename Allocator = allocator<Char>>
  explicit __basic_string(basic_string_view<Char, Traits>, const Allocator& = Allocator()) -> __basic_string<Char, Traits, Allocator>;

  template<typename Char, typename Traits, typename Allocator = allocator<Char>>
  __basic_string(basic_string_view<Char, Traits>,
                 typename __basic_string<Char, Traits, Allocator>::size_type,
                 typename __basic_string<Char, Traits, Allocator>::size_type,
                 const Allocator& = Allocator()) -> __basic_string<Char, Traits, Allocator>;

#endif // __CXX_STD_20__

#endif // __cpp_deduction_guides
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_STRING_BASIC_STRING_H_
