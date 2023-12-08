#ifndef CAPRESE_LIBC_INTERNAL_CXX_STRING_BASIC_STRING_H_
#define CAPRESE_LIBC_INTERNAL_CXX_STRING_BASIC_STRING_H_

#include <cassert>
#include <internal/attribute.h>
#include <internal/cxx/algorithm/minmax.h>
#include <internal/cxx/iterator/base.h>
#include <internal/cxx/memory/allocator.h>
#include <internal/cxx/memory/allocator_traits.h>
#include <internal/cxx/stdexcept/logic_error.h>
#include <internal/cxx/string/char_traits.h>
#include <internal/cxx/utility/fwd.h>
#include <internal/exception.h>
#include <iterator>

namespace std {
  template<typename Char, typename Traits = char_traits<Char>, typename Allocator = allocator<Char>>
  class __basic_string {
  public:
    using Traits_type     = Traits;
    using value_type      = typename Traits_type::char_type;
    using allocator_type  = Allocator;
    using size_type       = typename allocator_traits<Allocator>::size_type;
    using difference_type = typename allocator_traits<Allocator>::difference_type;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = typename allocator_traits<Allocator>::pointer;
    using const_pointer   = typename allocator_traits<Allocator>::const_pointer;

    struct iterator: public __iterator_base<pointer, __basic_string> { };

    struct const_iterator: public __iterator_base<const_pointer, __basic_string> { };

    using reverse_iterator       = ::std::reverse_iterator<iterator>;
    using const_reverse_iterator = ::std::reverse_iterator<const_iterator>;

  private:
    static constexpr size_type _threshold = sizeof(max_align_t) / sizeof(value_type);

    union {
      pointer    _data;
      value_type _short_data[_threshold];
    };

    size_type _size;
    size_type _capacity;

    allocator_type _allocator;

  public:
    static constexpr size_type npos = static_cast<size_type>(-1);

  public:
#ifdef __CXX_STD_17__
    __constexpr_cxx_std_20 __basic_string() noexcept(noexcept(allocator_type())): _short_data {}, _size(0), _capacity(_threshold), _allocator() { }
#else  // ^^^ __CXX_STD_17__ ^^^ / vvv !__CXX_STD_17__ vvv
    __basic_string(): _short_data {}, _size(0), _capacity(_threshold) { }
#endif // !__CXX_STD_17__

    __constexpr_cxx_std_20 __basic_string(const __basic_string& other): _short_data {}, _size(other._size), _capacity(other._capacity), _allocator(other._allocator) {
      if (_size >= _threshold) {
        _data = allocator_traits<allocator_type>::allocate(_allocator, other._capacity);
        for (size_type i = 0; i < _size; ++i) {
          _data[i] = other._data[i];
        }
      } else {
        for (size_type i = 0; i < _size; ++i) {
          _short_data[i] = other._short_data[i];
        }
      }
    }

    __constexpr_cxx_std_20 __basic_string(__basic_string&& other): _short_data {}, _size(other._size), _capacity(other._capacity), _allocator(move(other._allocator)) {
      if (_size >= _threshold) {
        _data       = other._data;
        other._data = nullptr;
      } else {
        for (size_type i = 0; i < _size; ++i) {
          _short_data[i] = other._short_data[i];
        }
      }

      other._size     = 0;
      other._capacity = 0;
    }

    __constexpr_cxx_std_20 explicit __basic_string(const allocator_type& allocator) __noexcept_cxx_std_17: _short_data {}, _size(0), _capacity(_threshold), _allocator(allocator) { }

    __constexpr_cxx_std_20 __basic_string(const __basic_string& other, size_type pos, size_type n, const allocator_type& allocator = allocator_type())
        : _short_data {},
          _size(n),
          _capacity(_threshold),
          _allocator(allocator) {
      assert(pos <= other._size);

      if (n == npos) {
        _size = other._size - pos;
      }

      if (_size >= _threshold) {
        _capacity = _size;
        _data     = allocator_traits<allocator_type>::allocate(_allocator, _capacity);
        for (size_type i = 0; i < _size; ++i) {
          _data[i] = other._data[pos + i];
        }
      } else {
        for (size_type i = 0; i < _size; ++i) {
          _short_data[i] = other._short_data[pos + i];
        }
      }
    }

    __constexpr_cxx_std_20 __basic_string(const __basic_string& other, size_type pos, const allocator_type& allocator = allocator_type()): __basic_string(other, pos, npos, allocator) { }

    __constexpr_cxx_std_20 __basic_string(const_pointer str, size_type n, const allocator_type& allocator = allocator_type()): _short_data {}, _size(n), _capacity(_threshold), _allocator(allocator) {
      if (_size >= _threshold) {
        _capacity = _size;
        _data     = allocator_traits<allocator_type>::allocate(_allocator, _capacity);
        for (size_type i = 0; i < _size; ++i) {
          _data[i] = str[i];
        }
      } else {
        for (size_type i = 0; i < _size; ++i) {
          _short_data[i] = str[i];
        }
      }
    }

    __constexpr_cxx_std_20 __basic_string(const_pointer str, const allocator_type& allocator = allocator_type()): _short_data {}, _size(0), _capacity(_threshold), _allocator(allocator) {
      while (str[_size] != static_cast<value_type>(0)) {
        ++_size;
      }

      if (_size >= _threshold) {
        _capacity = _size;
        _data     = allocator_traits<allocator_type>::allocate(_allocator, _capacity);
        for (size_type i = 0; i < _size; ++i) {
          _data[i] = str[i];
        }
      } else {
        for (size_type i = 0; i < _size; ++i) {
          _short_data[i] = str[i];
        }
      }
    }

#ifdef __CXX_STD_23__
    __basic_string(nullptr_t) = delete;
#endif // __CXX_STD_23__

    __constexpr_cxx_std_20 __basic_string(size_type n, value_type ch, const allocator_type& allocator = allocator_type()): _short_data {}, _size(n), _capacity(_threshold), _allocator(allocator) {
      if (_size >= _threshold) {
        _capacity = _size;
        _data     = allocator_traits<allocator_type>::allocate(_allocator, _capacity);
        for (size_type i = 0; i < _size; ++i) {
          _data[i] = ch;
        }
      } else {
        for (size_type i = 0; i < _size; ++i) {
          _short_data[i] = ch;
        }
      }
    }

    template<typename InputIterator>
    __constexpr_cxx_std_20 __basic_string(InputIterator first, InputIterator last, const allocator_type& allocator = allocator_type())
        : _short_data {},
          _size(0),
          _capacity(_threshold),
          _allocator(allocator) {
      for (auto it = first; it != last; ++it) {
        ++_size;
      }

      if (_size >= _threshold) {
        _capacity = _size;
        _data     = allocator_traits<allocator_type>::allocate(_allocator, _capacity);
        for (size_type i = 0; i < _size; ++i) {
          _data[i] = *first;
          ++first;
        }
      } else {
        for (size_type i = 0; i < _size; ++i) {
          _short_data[i] = *first;
          ++first;
        }
      }
    }

    __constexpr_cxx_std_20 __basic_string(initializer_list<value_type> init_list, const allocator_type& allocator = allocator_type())
        : _short_data {},
          _size(init_list.size()),
          _capacity(_threshold),
          _allocator(allocator) {
      if (_size >= _threshold) {
        _capacity = _size;
        _data     = allocator_traits<allocator_type>::allocate(_allocator, _capacity);
        for (size_type i = 0; i < _size; ++i) {
          _data[i] = init_list.begin()[i];
        }
      } else {
        for (size_type i = 0; i < _size; ++i) {
          _short_data[i] = init_list.begin()[i];
        }
      }
    }

    __constexpr_cxx_std_20 __basic_string(const __basic_string& other, const allocator_type& allocator): _short_data {}, _size(other._size), _capacity(other._capacity), _allocator(allocator) {
      if (_size >= _threshold) {
        _data = allocator_traits<allocator_type>::allocate(_allocator, other._capacity);
        for (size_type i = 0; i < _size; ++i) {
          _data[i] = other._data[i];
        }
      } else {
        for (size_type i = 0; i < _size; ++i) {
          _short_data[i] = other._short_data[i];
        }
      }
    }

    __constexpr_cxx_std_20 __basic_string(__basic_string&& other, const allocator_type& allocator): _short_data {}, _size(other._size), _capacity(other._capacity), _allocator(move(allocator)) {
      if (_size >= _threshold) {
        _data       = other._data;
        other._data = nullptr;
      } else {
        for (size_type i = 0; i < _size; ++i) {
          _short_data[i] = other._short_data[i];
        }
      }

      other._size     = 0;
      other._capacity = 0;
    }

    template<typename StringView>
    __constexpr_cxx_std_20 explicit __basic_string(const StringView& view, const allocator_type& allocator = allocator_type()) { }

    template<typename StringView>
    __constexpr_cxx_std_20 __basic_string(const StringView& view, size_type pos, size_type n, const allocator_type& allocator = allocator_type()) { }

    __constexpr_cxx_std_20 ~__basic_string() {
      if (_size >= _threshold) {
        allocator_traits<allocator_type>::deallocate(_allocator, _data, _capacity);
      }
    }

    __constexpr_cxx_std_20 __basic_string& operator=(const __basic_string& other) {
      if (this != &other) {
        if (_size >= _threshold) {
          allocator_traits<allocator_type>::deallocate(_allocator, _data, _capacity);
        }

        _size      = other._size;
        _capacity  = other._capacity;
        _allocator = other._allocator;

        if (_size >= _threshold) {
          _data = allocator_traits<allocator_type>::allocate(_allocator, _capacity);
          for (size_type i = 0; i < _size; ++i) {
            _data[i] = other._data[i];
          }
        } else {
          for (size_type i = 0; i < _size; ++i) {
            _short_data[i] = other._short_data[i];
          }
        }
      }

      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& operator=(__basic_string&& other) noexcept(
#ifdef __CXX_STD_17__
        allocator_traits<allocator_type>::propagate_on_container_move_assignment::value || allocator_traits<allocator_type>::is_always_equal::value
#endif // __CXX_STD_17__
    ) {
      if (this != &other) {
        if (_size >= _threshold) {
          allocator_traits<allocator_type>::deallocate(_allocator, _data, _capacity);
        }

        _size      = other._size;
        _capacity  = other._capacity;
        _allocator = move(other._allocator);

        if (_size >= _threshold) {
          _data       = other._data;
          other._data = nullptr;
        } else {
          for (size_type i = 0; i < _size; ++i) {
            _short_data[i] = other._short_data[i];
          }
        }

        other._size     = 0;
        other._capacity = 0;
      }

      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& operator=(const_pointer str) {
      size_type i = 0;
      while (str[i] != static_cast<value_type>(0)) {
        ++i;
      }

      if (_size >= _threshold) {
        allocator_traits<allocator_type>::deallocate(_allocator, _data, _capacity);
      }

      _size     = i;
      _capacity = _threshold;

      if (_size >= _threshold) {
        _capacity = _size;
        _data     = allocator_traits<allocator_type>::allocate(_allocator, _capacity);
        for (size_type i = 0; i < _size; ++i) {
          _data[i] = str[i];
        }
      } else {
        for (size_type i = 0; i < _size; ++i) {
          _short_data[i] = str[i];
        }
      }

      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& operator=(value_type ch) {
      if (_size >= _threshold) {
        allocator_traits<allocator_type>::deallocate(_allocator, _data, _capacity);
      }

      _size          = 1;
      _capacity      = _threshold;
      _short_data[0] = ch;
      _short_data[1] = static_cast<value_type>(0);

      return *this;
    }

    template<typename StringView>
    __constexpr_cxx_std_20 __basic_string& operator=(const StringView& view) { }

#ifdef __CXX_STD_23__
    __basic_string& operator=(nullptr_t) = delete;
#endif // __CXX_STD_23__

    __constexpr_cxx_std_20 iterator begin() __noexcept {
      return iterator(_data);
    }

    __constexpr_cxx_std_20 const_iterator begin() const __noexcept {
      return cbegin();
    }

    __constexpr_cxx_std_20 iterator end() __noexcept {
      return iterator(_data + _size);
    }

    __constexpr_cxx_std_20 const_iterator end() const __noexcept {
      return cend();
    }

    __constexpr_cxx_std_20 const_iterator cbegin() const __noexcept {
      return const_iterator(_data);
    }

    __constexpr_cxx_std_20 const_iterator cend() const __noexcept {
      return const_iterator(_data + _size);
    }

    __constexpr_cxx_std_20 reverse_iterator rbegin() __noexcept {
      return reverse_iterator(end());
    }

    __constexpr_cxx_std_20 const_reverse_iterator rbegin() const __noexcept {
      return crbegin();
    }

    __constexpr_cxx_std_20 reverse_iterator rend() __noexcept {
      return reverse_iterator(begin());
    }

    __constexpr_cxx_std_20 const_reverse_iterator rend() const __noexcept {
      return crend();
    }

    __constexpr_cxx_std_20 const_reverse_iterator crbegin() const __noexcept {
      return const_reverse_iterator(cend());
    }

    __constexpr_cxx_std_20 const_reverse_iterator crend() const __noexcept {
      return const_reverse_iterator(cbegin());
    }

    __constexpr_cxx_std_20 size_type size() const __noexcept {
      return _size;
    }

    __constexpr_cxx_std_20 size_type length() const __noexcept {
      return _size;
    }

    __constexpr_cxx_std_20 size_type max_size() const __noexcept {
      return allocator_traits<allocator_type>::max_size();
    }

    __constexpr_cxx_std_20 void resize(size_type n) {
      resize(n, static_cast<value_type>(0));
    }

    __constexpr_cxx_std_20 void resize(size_type n, value_type ch) {
      if (n > _size) {
        if (n > _capacity) {
          reserve(n);
        }

        for (size_type i = _size; i < n; ++i) {
          _data[i] = ch;
        }
      }

      _size = n;
    }

    __constexpr_cxx_std_20 size_type capacity() const __noexcept {
      return _capacity;
    }

    __deprecated_cxx_std_20 void reserve() {
      reserve(0);
    }

    __constexpr_cxx_std_20 void reserve(size_type n) {
      if (n > _capacity) {
        if (_size >= _threshold) {
          pointer new_data = allocator_traits<allocator_type>::allocate(_allocator, n);
          for (size_type i = 0; i < _size; ++i) {
            new_data[i] = _data[i];
          }

          allocator_traits<allocator_type>::deallocate(_allocator, _data, _capacity);
          _data     = new_data;
          _capacity = n;
        }
      }
    }

    __constexpr_cxx_std_20 void clear() __noexcept {
      erase(begin(), end());
    }

    __nodiscard_cxx_std_20 __constexpr_cxx_std_20 bool empty() const __noexcept {
      return _size == 0;
    }

    __constexpr_cxx_std_20 const_reference operator[](size_type pos) const {
      assert(pos < _size);
      return _data[pos];
    };

    __constexpr_cxx_std_20 reference operator[](size_type pos) {
      assert(pos < _size);
      return _data[pos];
    };

    __constexpr_cxx_std_20 const_reference at(size_type pos) const {
      __if_unlikely (pos >= _size) {
        __throw_exception(out_of_range("__basic_string::at"));
      }

      return _data[pos];
    };

    __constexpr_cxx_std_20 reference at(size_type pos) {
      __if_unlikely (pos >= _size) {
        __throw_exception(out_of_range("__basic_string::at"));
      }

      return _data[pos];
    };

    __constexpr_cxx_std_20 const_reference front() const {
      assert(_size > 0);
      return _data[0];
    }

    __constexpr_cxx_std_20 reference front() {
      assert(_size > 0);
      return _data[0];
    }

    __constexpr_cxx_std_20 const_reference back() const {
      assert(_size > 0);
      return _data[_size - 1];
    }

    __constexpr_cxx_std_20 reference back() {
      assert(_size > 0);
      return _data[_size - 1];
    }

    __constexpr_cxx_std_20 __basic_string& operator+=(const __basic_string& str) {
      append(str);
      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& operator+=(const_pointer str) {
      append(str);
      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& operator+=(value_type ch) {
      append(1, ch);
      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& operator+=(initializer_list<value_type> init_list) {
      append(init_list);
      return *this;
    }

    template<typename StringView>
    __constexpr_cxx_std_20 __basic_string& operator+=(const StringView& view) { }

    __constexpr_cxx_std_20 __basic_string& append(const __basic_string& str) {
      return append(str, 0, npos);
    }

    __constexpr_cxx_std_20 __basic_string& append(const __basic_string& str, size_type pos, size_type n = npos) {
      assert(pos <= str._size);

      if (n == npos) {
        n = str._size - pos;
      }

      if (_size + n > _capacity) {
        reserve(_size + n);
      }

      for (size_type i = 0; i < n; ++i) {
        _data[_size + i] = str._data[pos + i];
      }

      _size += n;

      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& append(const_pointer str, size_type n) {
      if (_size + n > _capacity) {
        reserve(_size + n);
      }

      for (size_type i = 0; i < n; ++i) {
        _data[_size + i] = str[i];
      }

      _size += n;

      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& append(const_pointer str) {
      size_type i = 0;
      while (str[i] != static_cast<value_type>(0)) {
        ++i;
      }

      if (_size + i > _capacity) {
        reserve(_size + i);
      }

      for (size_type j = 0; j < i; ++j) {
        _data[_size + j] = str[j];
      }

      _size += i;

      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& append(size_type n, value_type ch) {
      if (_size + n > _capacity) {
        reserve(_size + n);
      }

      for (size_type i = 0; i < n; ++i) {
        _data[_size + i] = ch;
      }

      _size += n;

      return *this;
    }

    template<typename InputIterator>
    __constexpr_cxx_std_20 __basic_string& append(InputIterator first, InputIterator last) {
      size_type n = 0;
      for (auto it = first; it != last; ++it) {
        ++n;
      }

      if (_size + n > _capacity) {
        reserve(_size + n);
      }

      for (size_type i = 0; i < n; ++i) {
        _data[_size + i] = *first;
        ++first;
      }

      _size += n;

      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& append(initializer_list<value_type> init_list) {
      return append(init_list.begin(), init_list.end());
    }

    template<typename StringView>
    __constexpr_cxx_std_20 __basic_string& append(const StringView& view) { }

    template<typename StringView>
    __constexpr_cxx_std_20 __basic_string& append(const StringView& view, size_type pos, size_type n = npos) { }

    __constexpr_cxx_std_20 __basic_string& push_back(value_type ch) {
      append(static_cast<size_type>(1), ch);
    }

    __constexpr_cxx_std_20 __basic_string& insert(size_type pos, const __basic_string& str) {
      return insert(pos, str.data(), str.size());
    }

    __constexpr_cxx_std_20 __basic_string& insert(size_type pos1, const __basic_string& str, size_type pos2, size_type n = npos) {
      if (n == npos || n > str.size() - pos2) {
        n = str.size() - pos2;
      }
      return insert(pos1, str.data() + pos2, n);
    }

    __constexpr_cxx_std_20 __basic_string& insert(size_type pos, const Char* s, size_type n) {
      assert(pos <= _size);

      if (_size + n > _capacity) {
        reserve(_size + n);
      }

      for (size_type i = _size; i > pos; --i) {
        _data[i + n - 1] = _data[i - 1];
      }

      for (size_type i = 0; i < n; ++i) {
        _data[pos + i] = s[i];
      }

      _size += n;

      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& insert(size_type pos, const Char* s) {
      return insert(pos, s, Traits::length(s));
    }

    __constexpr_cxx_std_20 __basic_string& insert(size_type pos, size_type n, Char c) {
      return insert(pos, __basic_string(n, c));
    }

    __constexpr_cxx_std_20 iterator insert(const_iterator p, Char c) {
      assert(p >= begin() && p < end());
      return insert(p - begin(), 1, c);
    }

    __constexpr_cxx_std_20 iterator insert(const_iterator p, size_type n, Char c) {
      assert(p >= begin() && p < end());
      return insert(p - begin(), n, c);
    }

    template<typename InputIterator>
    __constexpr_cxx_std_20 iterator insert(const_iterator p, InputIterator first, InputIterator last) {
      assert(p >= begin() && p < end());
      return insert(p - begin(), __basic_string(first, last));
    }

    __constexpr_cxx_std_20 iterator insert(const_iterator p, initializer_list<Char> init_list) {
      assert(p >= begin() && p < end());
      return insert(p, init_list.begin(), init_list.end());
    }

    __constexpr_cxx_std_20 __basic_string& erase(size_type pos = 0, size_type n = npos) {
      assert(pos <= _size);

      if (n == npos) {
        n = _size - pos;
      }

      for (size_type i = pos; i < _size - n; ++i) {
        _data[i] = _data[i + n];
      }

      _size -= n;

      return *this;
    }

    __constexpr_cxx_std_20 iterator erase(const_iterator pos) {
      assert(pos >= begin() && pos < end());
      return erase(pos - begin(), 1);
    }

    __constexpr_cxx_std_20 iterator erase(const_iterator first, const_iterator last) {
      assert(first >= begin() && first < end());
      assert(last >= begin() && last < end());
      return erase(first - begin(), last - first);
    }

    __constexpr_cxx_std_20 void pop_back() {
      assert(!empty());
      erase(_size - 1, 1);
    }

    __constexpr_cxx_std_20 const_pointer c_str() const __noexcept {
      return _data;
    }

    __constexpr_cxx_std_20 pointer data() __noexcept {
      return _data;
    }

    __constexpr_cxx_std_20 int compare(const __basic_string& other) const __noexcept_cxx_std_11 {
      int result = Traits::compare(data(), other.data(), min(size(), other.size()));
      if (result != 0) {
        return result;
      } else {
        if (size() < other.size()) {
          return -1;
        } else if (size() > other.size()) {
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
      return compare(__basic_string(s));
    }

    __constexpr_cxx_std_20 int compare(size_type pos, size_type n1, const Char* s) const {
      return __basic_string(*this, pos, n1).compare(__basic_string(s));
    }

    __constexpr_cxx_std_20 int compare(size_type pos, size_type n1, const Char* s, size_type n2) const {
      return __basic_string(*this, pos, n1).compare(__basic_string(s, n2));
    }
  };

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
