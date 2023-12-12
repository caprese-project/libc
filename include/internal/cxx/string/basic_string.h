#ifndef CAPRESE_LIBC_INTERNAL_CXX_STRING_BASIC_STRING_H_
#define CAPRESE_LIBC_INTERNAL_CXX_STRING_BASIC_STRING_H_

#include <cassert>
#include <internal/attribute.h>
#include <internal/cxx/algorithm/minmax.h>
#include <internal/cxx/iterator/tags.h>
#include <internal/cxx/memory/allocator.h>
#include <internal/cxx/memory/allocator_traits.h>
#include <internal/cxx/memory/pointer_traits.h>
#include <internal/cxx/stdexcept/logic_error.h>
#include <internal/cxx/string/char_traits.h>
#include <internal/cxx/utility/fwd.h>
#include <internal/exception.h>
#include <iterator>

namespace std {
  template<typename Char, typename Traits = char_traits<Char>, typename Allocator = allocator<Char>>
  class __basic_string {
  public:
    using traits_type     = Traits;
    using value_type      = typename traits_type::char_type;
    using allocator_type  = Allocator;
    using size_type       = typename allocator_traits<Allocator>::size_type;
    using difference_type = typename allocator_traits<Allocator>::difference_type;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = typename allocator_traits<Allocator>::pointer;
    using const_pointer   = typename allocator_traits<Allocator>::const_pointer;

    class iterator {
    public:
      using iterator_category = random_access_iterator_tag;
      using value_type        = __basic_string::value_type;
      using difference_type   = __basic_string::difference_type;
      using pointer           = __basic_string::pointer;
      using reference         = __basic_string::reference;

      friend class __basic_string::const_iterator;

    private:
      pointer _ptr;

    public:
      __constexpr_cxx_std_20 iterator() __noexcept: _ptr() { }

      __constexpr_cxx_std_20 iterator(pointer ptr) __noexcept: _ptr(ptr) { }

      __constexpr_cxx_std_20 reference operator*() const __noexcept {
        return *_ptr;
      }

      __constexpr_cxx_std_20 pointer operator->() const __noexcept {
        return pointer_traits<pointer>::pointer_to(**this);
      }

      __constexpr_cxx_std_20 iterator& operator++() __noexcept {
        ++_ptr;
        return *this;
      }

      __constexpr_cxx_std_20 iterator operator++(int) __noexcept {
        iterator tmp = *this;
        ++*this;
        return tmp;
      }

      __constexpr_cxx_std_20 iterator& operator--() __noexcept {
        --_ptr;
        return *this;
      }

      __constexpr_cxx_std_20 iterator operator--(int) __noexcept {
        iterator tmp = *this;
        --*this;
        return tmp;
      }

      __constexpr_cxx_std_20 iterator& operator+=(difference_type n) __noexcept {
        _ptr += n;
        return *this;
      }

      __constexpr_cxx_std_20 iterator operator+(difference_type n) const __noexcept {
        iterator tmp = *this;
        tmp += n;
        return tmp;
      }

      __constexpr_cxx_std_20 iterator& operator-=(difference_type n) __noexcept {
        return *this += -n;
      }

      __constexpr_cxx_std_20 iterator operator-(difference_type n) const __noexcept {
        iterator tmp = *this;
        tmp -= n;
        return tmp;
      }

      __constexpr_cxx_std_20 difference_type operator-(const iterator& other) const __noexcept {
        return _ptr - other._ptr;
      }

      __constexpr_cxx_std_20 reference operator[](difference_type n) const __noexcept {
        return *(*this + n);
      }

      __constexpr_cxx_std_20 bool operator==(const iterator& other) const __noexcept {
        return _ptr == other._ptr;
      }

#ifdef __CXX_STD_20__
      __constexpr_cxx_std_20 auto operator<=>(const iterator& other) const __noexcept {
        return _ptr <=> other._ptr;
      }
#else  // ^^^ __CXX_STD_20__ ^^^ / vvv !__CXX_STD_20__ vvv
      bool operator!=(const iterator& other) const __noexcept {
        return !(*this == other);
      }

      bool operator<(const iterator& other) const __noexcept {
        return _ptr < other._ptr;
      }

      bool operator>(const iterator& other) const __noexcept {
        return other < *this;
      }

      bool operator<=(const iterator& other) const __noexcept {
        return !(other < *this);
      }

      bool operator>=(const iterator& other) const __noexcept {
        return !(*this < other);
      }
#endif // !__CXX_STD_20__
    };

    class const_iterator {
    public:
      using iterator_category = random_access_iterator_tag;
      using value_type        = __basic_string::value_type;
      using difference_type   = __basic_string::difference_type;
      using pointer           = __basic_string::const_pointer;
      using reference         = __basic_string::const_reference;

      friend class __basic_string::iterator;

    private:
      pointer _ptr;

    public:
      __constexpr_cxx_std_20 const_iterator() __noexcept: _ptr() { }

      __constexpr_cxx_std_20 const_iterator(pointer ptr) __noexcept: _ptr(ptr) { }

      __constexpr_cxx_std_20 const_iterator(const iterator& other) __noexcept: _ptr(other._ptr) { }

      __constexpr_cxx_std_20 reference operator*() const __noexcept {
        return *_ptr;
      }

      __constexpr_cxx_std_20 pointer operator->() const __noexcept {
        return pointer_traits<pointer>::pointer_to(**this);
      }

      __constexpr_cxx_std_20 const_iterator& operator++() __noexcept {
        ++_ptr;
        return *this;
      }

      __constexpr_cxx_std_20 const_iterator operator++(int) __noexcept {
        const_iterator tmp = *this;
        ++*this;
        return tmp;
      }

      __constexpr_cxx_std_20 const_iterator& operator--() __noexcept {
        --_ptr;
        return *this;
      }

      __constexpr_cxx_std_20 const_iterator operator--(int) __noexcept {
        const_iterator tmp = *this;
        --*this;
        return tmp;
      }

      __constexpr_cxx_std_20 const_iterator& operator+=(difference_type n) __noexcept {
        _ptr += n;
        return *this;
      }

      __constexpr_cxx_std_20 const_iterator operator+(difference_type n) const __noexcept {
        const_iterator tmp = *this;
        tmp += n;
        return tmp;
      }

      __constexpr_cxx_std_20 const_iterator& operator-=(difference_type n) __noexcept {
        return *this += -n;
      }

      __constexpr_cxx_std_20 const_iterator operator-(difference_type n) const __noexcept {
        const_iterator tmp = *this;
        tmp -= n;
        return tmp;
      }

      __constexpr_cxx_std_20 difference_type operator-(const const_iterator& other) const __noexcept {
        return _ptr - other._ptr;
      }

      __constexpr_cxx_std_20 reference operator[](difference_type n) const __noexcept {
        return *(*this + n);
      }

      __constexpr_cxx_std_20 bool operator==(const const_iterator& other) const __noexcept {
        return _ptr == other._ptr;
      }

#ifdef __CXX_STD_20__
      __constexpr_cxx_std_20 auto operator<=>(const const_iterator& other) const __noexcept {
        return _ptr <=> other._ptr;
      }
#else  // ^^^ __CXX_STD_20__ ^^^ / vvv !__CXX_STD_20__ vvv
      bool operator!=(const const_iterator& other) const __noexcept {
        return !(*this == other);
      }

      bool operator<(const const_iterator& other) const __noexcept {
        return _ptr < other._ptr;
      }

      bool operator>(const const_iterator& other) const __noexcept {
        return other < *this;
      }

      bool operator<=(const const_iterator& other) const __noexcept {
        return !(other < *this);
      }

      bool operator>=(const const_iterator& other) const __noexcept {
        return !(*this < other);
      }
#endif // !__CXX_STD_20__
    };

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
      return iterator(data());
    }

    __constexpr_cxx_std_20 const_iterator begin() const __noexcept {
      return cbegin();
    }

    __constexpr_cxx_std_20 iterator end() __noexcept {
      return iterator(data() + _size);
    }

    __constexpr_cxx_std_20 const_iterator end() const __noexcept {
      return cend();
    }

    __constexpr_cxx_std_20 const_iterator cbegin() const __noexcept {
      return const_iterator(data());
    }

    __constexpr_cxx_std_20 const_iterator cend() const __noexcept {
      return const_iterator(data() + _size);
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
      return allocator_traits<allocator_type>::max_size(_allocator);
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
          data()[i] = ch;
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
      return data()[pos];
    };

    __constexpr_cxx_std_20 reference operator[](size_type pos) {
      assert(pos < _size);
      return data()[pos];
    };

    __constexpr_cxx_std_20 const_reference at(size_type pos) const {
      __if_unlikely (pos >= _size) {
        __throw_exception(out_of_range("__basic_string::at"));
      }

      return data()[pos];
    };

    __constexpr_cxx_std_20 reference at(size_type pos) {
      __if_unlikely (pos >= _size) {
        __throw_exception(out_of_range("__basic_string::at"));
      }

      return data()[pos];
    };

    __constexpr_cxx_std_20 const_reference front() const {
      assert(_size > 0);
      return data()[0];
    }

    __constexpr_cxx_std_20 reference front() {
      assert(_size > 0);
      return data()[0];
    }

    __constexpr_cxx_std_20 const_reference back() const {
      assert(_size > 0);
      return data()[_size - 1];
    }

    __constexpr_cxx_std_20 reference back() {
      assert(_size > 0);
      return data()[_size - 1];
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
        data()[_size + i] = str.data()[pos + i];
      }

      _size += n;

      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& append(const_pointer str, size_type n) {
      if (_size + n > _capacity) {
        reserve(_size + n);
      }

      for (size_type i = 0; i < n; ++i) {
        data()[_size + i] = str[i];
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
        data()[_size + j] = str[j];
      }

      _size += i;

      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& append(size_type n, value_type ch) {
      if (_size + n > _capacity) {
        reserve(_size + n);
      }

      for (size_type i = 0; i < n; ++i) {
        data()[_size + i] = ch;
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
        data()[_size + i] = *first;
        ++first;
      }

      _size += n;

      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& append(initializer_list<value_type> init_list) {
      return append(init_list.begin(), init_list.end());
    }

    template<typename StringView>
    __constexpr_cxx_std_20 __basic_string& append(const StringView& view) {
      (void)view;
      return *this;
    }

    template<typename StringView>
    __constexpr_cxx_std_20 __basic_string& append(const StringView& view, size_type pos, size_type n = npos) {
      (void)view;
      (void)pos;
      (void)n;
      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& push_back(value_type ch) {
      return append(static_cast<size_type>(1), ch);
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
        data()[i + n - 1] = data()[i - 1];
      }

      for (size_type i = 0; i < n; ++i) {
        data()[pos + i] = s[i];
      }

      _size += n;

      return *this;
    }

    __constexpr_cxx_std_20 __basic_string& insert(size_type pos, const Char* s) {
      return insert(pos, s, traits_type::length(s));
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
        data()[i] = data()[i + n];
      }

      _size -= n;

      data()[_size] = value_type();

      return *this;
    }

    __constexpr_cxx_std_20 iterator erase(const_iterator pos) {
      assert(pos >= begin() && pos < end());

      auto offset = pos - begin();
      erase(offset, 1);

      return begin() + offset;
    }

    __constexpr_cxx_std_20 iterator erase(const_iterator first, const_iterator last) {
      assert(first >= begin() && first < end());
      assert(last >= begin() && last < end());

      auto offset = first - begin();
      erase(offset, last - first);

      return begin() + offset;
    }

    __constexpr_cxx_std_20 void pop_back() {
      assert(!empty());
      erase(_size - 1, 1);
    }

    __constexpr_cxx_std_20 void swap(__basic_string& other) {
      if (this == &other) {
        return;
      }

      if (_size >= _threshold && other._size >= _threshold) {
        pointer tmp_data = _data;
        _data            = other._data;
        other._data      = tmp_data;
      } else if (_size >= _threshold && other._size < _threshold) {
        for (size_type i = 0; i < _threshold; ++i) {
          value_type tmp       = _short_data[i];
          _short_data[i]       = other._short_data[i];
          other._short_data[i] = tmp;
        }

        pointer tmp_data = _data;
        _data            = other._data;
        other._data      = tmp_data;
      } else if (_size < _threshold && other._size >= _threshold) {
        for (size_type i = 0; i < _threshold; ++i) {
          value_type tmp       = _short_data[i];
          _short_data[i]       = other._short_data[i];
          other._short_data[i] = tmp;
        }

        pointer tmp_data = _data;
        _data            = other._data;
        other._data      = tmp_data;
      } else {
        for (size_type i = 0; i < _threshold; ++i) {
          value_type tmp       = _short_data[i];
          _short_data[i]       = other._short_data[i];
          other._short_data[i] = tmp;
        }
      }

      size_type tmp_size = _size;
      _size              = other._size;
      other._size        = tmp_size;

      size_type tmp_capacity = _capacity;
      _capacity              = other._capacity;
      other._capacity        = tmp_capacity;

      allocator_type tmp_allocator = _allocator;
      _allocator                   = other._allocator;
      other._allocator             = tmp_allocator;
    }

    __constexpr_cxx_std_20 const_pointer c_str() const __noexcept {
      if (_size >= _threshold) {
        return _data;
      } else {
        return _short_data;
      }
    }

    __constexpr_cxx_std_20 const_pointer data() const __noexcept {
      if (_size >= _threshold) {
        return _data;
      } else {
        return _short_data;
      }
    }

    __constexpr_cxx_std_20 pointer data() __noexcept {
      if (_size >= _threshold) {
        return _data;
      } else {
        return _short_data;
      }
    }

    __constexpr_cxx_std_20 allocator_type get_allocator() const __noexcept_cxx_std_11 {
      return _allocator;
    }

    __constexpr_cxx_std_20 int compare(const __basic_string& other) const __noexcept_cxx_std_11 {
      int result = traits_type::compare(data(), other.data(), min(size(), other.size()));
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
