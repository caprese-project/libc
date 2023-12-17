#ifndef CAPRESE_LIBC_INTERNAL_CXX_STL_BASE_VLA_H_
#define CAPRESE_LIBC_INTERNAL_CXX_STL_BASE_VLA_H_

#include <compare>
#include <initializer_list>
#include <internal/branch.h>
#include <internal/cxx/algorithm/minmax.h>
#include <internal/cxx/algorithm/seq.h>
#include <internal/cxx/iterator/functions.h>
#include <internal/cxx/iterator/reverse_iterator.h>
#include <internal/cxx/memory/allocator_traits.h>
#include <internal/cxx/stdexcept/logic_error.h>
#include <internal/cxx/utility/fwd.h>
#include <internal/cxx/utility/swap.h>
#include <internal/exception.h>

namespace std {
  template<typename ValueType, typename Pointer, typename Reference, typename DifferenceType>
  class __vla_iterator_base {
  public:
    using value_type        = ValueType;
    using pointer           = Pointer;
    using reference         = Reference;
    using difference_type   = DifferenceType;
    using iterator_category = random_access_iterator_tag;

  private:
    pointer _ptr;

  public:
    __constexpr_cxx_std_20 __vla_iterator_base() __noexcept: _ptr(nullptr) { }

    __constexpr_cxx_std_20 __vla_iterator_base(pointer ptr) __noexcept: _ptr(ptr) { }

    __constexpr_cxx_std_20 __vla_iterator_base(const __vla_iterator_base& other) __noexcept: _ptr(other._ptr) { }

    __constexpr_cxx_std_20 __vla_iterator_base& operator=(const __vla_iterator_base& other) __noexcept {
      if (this != &other) {
        _ptr = other._ptr;
      }
      return *this;
    }

    // Input Iterator Requirements

    __constexpr_cxx_std_20 reference operator*() const {
      return *_ptr;
    }

    // Forward Iterator Requirements

    __constexpr_cxx_std_20 __vla_iterator_base& operator++() __noexcept {
      ++_ptr;
      return *this;
    }

    __constexpr_cxx_std_20 __vla_iterator_base operator++(int) __noexcept {
      __vla_iterator_base tmp = *this;
      ++_ptr;
      return tmp;
    }

    __constexpr_cxx_std_20 bool operator==(const __vla_iterator_base& other) const __noexcept {
      return _ptr == other._ptr;
    }

#ifndef __CXX_STD_20__

    bool operator!=(const __vla_iterator_base& other) const __noexcept {
      return !(*this == other);
    }

#endif // __CXX_STD_20__

    // Bidirectional Iterator Requirements

    __constexpr_cxx_std_20 __vla_iterator_base& operator--() __noexcept {
      --_ptr;
      return *this;
    }

    __constexpr_cxx_std_20 __vla_iterator_base operator--(int) __noexcept {
      __vla_iterator_base tmp = *this;
      --_ptr;
      return tmp;
    }

    // Random Access Iterator Requirements

    __constexpr_cxx_std_20 __vla_iterator_base& operator+=(difference_type n) __noexcept {
      _ptr += n;
      return *this;
    }

    __constexpr_cxx_std_20 __vla_iterator_base& operator-=(difference_type n) __noexcept {
      _ptr -= n;
      return *this;
    }

    __constexpr_cxx_std_20 reference operator[](difference_type n) const __noexcept {
      return _ptr[n];
    }

    friend __vla_iterator_base operator+(const __vla_iterator_base& lhs, difference_type rhs) __noexcept {
      return __vla_iterator_base(lhs._ptr + rhs);
    }

    friend __vla_iterator_base operator+(difference_type lhs, const __vla_iterator_base& rhs) __noexcept {
      return __vla_iterator_base(lhs + rhs._ptr);
    }

    friend __vla_iterator_base operator-(const __vla_iterator_base& lhs, difference_type rhs) __noexcept {
      return __vla_iterator_base(lhs._ptr - rhs);
    }

    friend difference_type operator-(const __vla_iterator_base& lhs, const __vla_iterator_base& rhs) __noexcept {
      return lhs._ptr - rhs._ptr;
    }

    __constexpr_cxx_std_20 bool operator<(const __vla_iterator_base& other) const __noexcept {
      return _ptr < other._ptr;
    }

#ifndef __CXX_STD_20__

    bool operator>(const __vla_iterator_base& other) const __noexcept {
      return _ptr > other._ptr;
    }

    bool operator<=(const __vla_iterator_base& other) const __noexcept {
      return _ptr <= other._ptr;
    }

    bool operator>=(const __vla_iterator_base& other) const __noexcept {
      return _ptr >= other._ptr;
    }

#endif // __CXX_STD_20__
  };

  template<typename Storage>
  class __vla {
  public:
    using __storage_type         = Storage;
    using value_type             = typename __storage_type::value_type;
    using reference              = typename __storage_type::reference;
    using const_reference        = typename __storage_type::const_reference;
    using allocator_type         = typename __storage_type::allocator_type;
    using pointer                = typename __storage_type::pointer;
    using const_pointer          = typename __storage_type::const_pointer;
    using size_type              = typename __storage_type::size_type;
    using difference_type        = typename __storage_type::difference_type;
    using iterator               = __vla_iterator_base<value_type, pointer, reference, difference_type>;
    using const_iterator         = __vla_iterator_base<const value_type, const_pointer, const_reference, difference_type>;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  private:
    __storage_type _storage;

  public:
    __constexpr_cxx_std_20 __vla() __noexcept_if_cxx_std_17(noexcept(allocator_type())): __vla(allocator_type()) { }

    __constexpr_cxx_std_20 explicit __vla(const allocator_type& allocator) __noexcept_if_cxx_std_17(noexcept(__storage_type(allocator))): _storage(allocator) { }

    __constexpr_cxx_std_20 explicit __vla(size_type n, const allocator_type& allocator = allocator_type()): _storage(allocator) {
      _storage.grow(n);

      allocator_type alloc = _storage.get_allocator();
      pointer        begin = _storage.front_pointer();
      for (size_type i = 0; i < n; ++i) {
        allocator_traits<allocator_type>::construct(alloc, begin + i);
      }
    }

    __constexpr_cxx_std_20 __vla(size_type n, const value_type& value, const allocator_type& allocator = allocator_type()): _storage(allocator) {
      _storage.grow(n);

      allocator_type alloc = _storage.get_allocator();
      pointer        begin = _storage.front_pointer();
      for (size_type i = 0; i < n; ++i) {
        allocator_traits<allocator_type>::construct(alloc, begin + i, value);
      }
    }

    template<typename InputIterator>
    __constexpr_cxx_std_20 __vla(InputIterator first, InputIterator last, const allocator_type& allocator = allocator_type()): _storage(allocator) {
      size_type n = distance(first, last);
      _storage.grow(n);

      allocator_type alloc = _storage.get_allocator();
      pointer        begin = _storage.front_pointer();
      for (size_type i = 0; i < n; ++i) {
        allocator_traits<allocator_type>::construct(alloc, begin + i, *first++);
      }
    }

    __constexpr_cxx_std_20 __vla(const __vla& other): _storage(other._storage) { }

    __constexpr_cxx_std_20 __vla(__vla&& other) __noexcept_cxx_std_11: _storage(move(other._storage)) { }

    __constexpr_cxx_std_20 __vla(const __vla& other, const allocator_type& allocator): _storage(other._storage, allocator) { }

    __constexpr_cxx_std_20 __vla(__vla&& other, const allocator_type& allocator): _storage(move(other._storage), allocator) { }

    __constexpr_cxx_std_20 __vla(initializer_list<value_type> init_list, const allocator_type& allocator = allocator_type()): __vla(init_list.begin(), init_list.end(), allocator) { }

    __constexpr_cxx_std_20 __vla& operator=(const __vla& other) {
      if (this != &other) {
        _storage = other._storage;
      }
      return *this;
    }

    __constexpr_cxx_std_20 __vla& operator=(__vla&& other) __noexcept_cxx_std_11 {
      if (this != &other) {
        _storage = move(other._storage);
      }
      return *this;
    }

    __constexpr_cxx_std_20 __vla& operator=(initializer_list<value_type> init_list) {
      this->clear();
      this->insert(init_list.begin(), init_list.end());
      return *this;
    }

    __constexpr_cxx_std_20 iterator begin() __noexcept_cxx_std_11 {
      return iterator(_storage.front_pointer());
    }

    __constexpr_cxx_std_20 const_iterator begin() const __noexcept_cxx_std_11 {
      return const_iterator(_storage.front_pointer());
    }

    __constexpr_cxx_std_20 iterator end() __noexcept_cxx_std_11 {
      return iterator(_storage.back_pointer() + 1);
    }

    __constexpr_cxx_std_20 const_iterator end() const __noexcept_cxx_std_11 {
      return const_iterator(_storage.back_pointer() + 1);
    }

    __constexpr_cxx_std_20 const_iterator cbegin() const __noexcept_cxx_std_11 {
      return const_iterator(_storage.front_pointer());
    }

    __constexpr_cxx_std_20 const_iterator cend() const __noexcept_cxx_std_11 {
      return const_iterator(_storage.back_pointer() + 1);
    }

    __constexpr_cxx_std_20 reverse_iterator rbegin() __noexcept_cxx_std_11 {
      return reverse_iterator(this->end());
    }

    __constexpr_cxx_std_20 const_reverse_iterator rbegin() const __noexcept_cxx_std_11 {
      return const_reverse_iterator(this->end());
    }

    __constexpr_cxx_std_20 reverse_iterator rend() __noexcept_cxx_std_11 {
      return reverse_iterator(this->begin());
    }

    __constexpr_cxx_std_20 const_reverse_iterator rend() const __noexcept_cxx_std_11 {
      return const_reverse_iterator(this->begin());
    }

    __constexpr_cxx_std_20 const_reverse_iterator crbegin() const __noexcept_cxx_std_11 {
      return const_reverse_iterator(this->end());
    }

    __constexpr_cxx_std_20 const_reverse_iterator crend() const __noexcept_cxx_std_11 {
      return const_reverse_iterator(this->begin());
    }

    __constexpr_cxx_std_20 size_type size() const __noexcept_cxx_std_11 {
      return _storage.size();
    }

    __constexpr_cxx_std_20 size_type max_size() const __noexcept_cxx_std_11 {
      return _storage.max_size();
    }

    __constexpr_cxx_std_20 size_type capacity() const __noexcept_cxx_std_11 {
      return _storage.capacity();
    }

    __constexpr_cxx_std_20 bool empty() const __noexcept_cxx_std_11 {
      return this->size() == 0;
    }

    __constexpr_cxx_std_20 void reserve(size_type n) {
      size_type old_capacity = this->capacity();
      if (n > old_capacity) {
        _storage.grow(n - old_capacity);
      }
    }

    __constexpr_cxx_std_20 void resize(size_type n) {
      this->_resize(n);
    }

    __constexpr_cxx_std_20 void resize(size_type n, const value_type& value) {
      this->_resize(n, value);
    }

    __constexpr_cxx_std_20 void shrink_to_fit() {
      _storage.shrink(_storage.capacity() - this->size());
    }

    __constexpr_cxx_std_20 reference operator[](size_type n) {
      return _storage.front_pointer()[n];
    }

    __constexpr_cxx_std_20 const_reference operator[](size_type n) const {
      return _storage.front_pointer()[n];
    }

    __constexpr_cxx_std_20 reference at(size_type n) {
      __if_unlikely (n >= this->size()) {
        __throw_exception(out_of_range("vla::at"));
      }
      return _storage.front_pointer()[n];
    }

    __constexpr_cxx_std_20 const_reference at(size_type n) const {
      __if_unlikely (n >= this->size()) {
        __throw_exception(out_of_range("vla::at"));
      }
      return _storage.front_pointer()[n];
    }

    __constexpr_cxx_std_20 pointer data() __noexcept_cxx_std_11 {
      return _storage.front_pointer();
    }

    __constexpr_cxx_std_20 const_pointer data() const __noexcept_cxx_std_11 {
      return _storage.front_pointer();
    }

    __constexpr_cxx_std_20 reference front() {
      return _storage.front_pointer()[0];
    }

    __constexpr_cxx_std_20 const_reference front() const {
      return _storage.front_pointer()[0];
    }

    __constexpr_cxx_std_20 reference back() {
      return _storage.back_pointer()[0];
    }

    __constexpr_cxx_std_20 const_reference back() const {
      return _storage.back_pointer()[0];
    }

    template<typename InputIterator>
    __constexpr_cxx_std_20 void assign(InputIterator first, InputIterator last) {
      this->clear();
      this->insert(this->cbegin(), first, last);
    }

    __constexpr_cxx_std_20 void assign(size_type n, const value_type& value) {
      this->clear();
      this->insert(this->cbegin(), n, value);
    }

    __constexpr_cxx_std_20 void assign(initializer_list<value_type> init_list) {
      this->assign(this->cbegin(), init_list.begin(), init_list.end());
    }

    __constexpr_cxx_std_20 void push_back(const value_type& value) {
      this->_emplace_back(value);
    }

    __constexpr_cxx_std_20 void push_back(value_type&& value) {
      this->_emplace_back(move(value));
    }

    template<typename... Args>
    __constexpr_cxx_std_20 void emplace_back(Args&&... args) {
      this->_emplace_back(forward<Args>(args)...);
    }

    __constexpr_cxx_std_20 void pop_back() {
      allocator_type alloc = _storage.get_allocator();
      pointer        begin = _storage.front_pointer();
      allocator_traits<allocator_type>::destroy(alloc, begin + this->size() - 1);
      _storage.set_size(this->size() - 1);
    }

    __constexpr_cxx_std_20 allocator_type get_allocator() const __noexcept_cxx_std_11 {
      return _storage.get_allocator();
    }

    __constexpr_cxx_std_20 iterator insert(const_iterator pos, const value_type& value) {
      size_type index = distance(this->cbegin(), pos);
      this->_shift(index, 1);
      allocator_traits<allocator_type>::construct(_storage.get_allocator(), _storage.front_pointer() + index, value);
      return this->begin() + index;
    }

    __constexpr_cxx_std_20 iterator insert(const_iterator pos, value_type&& value) {
      size_type index = distance(this->cbegin(), pos);
      this->_shift(index, 1);
      allocator_traits<allocator_type>::construct(_storage.get_allocator(), _storage.front_pointer() + index, move(value));
      return this->begin() + index;
    }

    __constexpr_cxx_std_20 iterator insert(const_iterator pos, size_type n, const value_type& value) {
      size_type index = distance(this->cbegin(), pos);
      this->_shift(index, n);

      pointer        ptr   = _storage.front_pointer() + index;
      allocator_type alloc = _storage.get_allocator();
      for (size_type i = 0; i < n; ++i) {
        allocator_traits<allocator_type>::construct(alloc, ptr + i, value);
      }
      return this->begin() + index;
    }

    template<typename InputIterator>
    __constexpr_cxx_std_20 iterator insert(const_iterator pos, InputIterator first, InputIterator last) {
      size_type n     = distance(first, last);
      size_type index = distance(this->cbegin(), pos);
      this->_shift(index, n);

      pointer        ptr   = _storage.front_pointer() + index;
      allocator_type alloc = _storage.get_allocator();
      for (size_type i = 0; i < n; ++i) {
        allocator_traits<allocator_type>::construct(alloc, ptr + i, *first++);
      }
      return this->begin() + index;
    }

    __constexpr_cxx_std_20 iterator insert(const_iterator pos, initializer_list<value_type> init_list) {
      return this->insert(pos, init_list.begin(), init_list.end());
    }

    template<typename... Args>
    __constexpr_cxx_std_20 iterator emplace(const_iterator pos, Args&&... args) {
      size_type index = distance(this->cbegin(), pos);
      this->_shift(index, 1);
      allocator_traits<allocator_type>::construct(_storage.get_allocator(), _storage.front_pointer() + index, forward<Args>(args)...);
      return this->begin() + index;
    }

    __constexpr_cxx_std_20 iterator erase(const_iterator pos) {
      size_type index = distance(this->cbegin(), pos);
      pointer   ptr   = _storage.front_pointer() + index;
      allocator_traits<allocator_type>::destroy(_storage.get_allocator(), ptr);
      this->_unshift(index, 1);
      return this->begin() + index;
    }

    __constexpr_cxx_std_20 iterator erase(const_iterator first, const_iterator last) {
      size_type n     = distance(first, last);
      size_type index = distance(this->cbegin(), first);
      pointer   ptr   = _storage.front_pointer() + index;
      for (size_type i = 0; i < n; ++i) {
        allocator_traits<allocator_type>::destroy(_storage.get_allocator(), ptr + i);
      }
      this->_unshift(index, n);
      return this->begin() + index;
    }

    __constexpr_cxx_std_20 void swap(__vla& other) __noexcept_cxx_std_11 {
      using std::swap;
      swap(_storage, other._storage);
    }

    __constexpr_cxx_std_20 void clear() __noexcept_cxx_std_11 {
      allocator_type alloc = _storage.get_allocator();
      pointer        begin = _storage.front_pointer();
      for (size_type i = 0; i < this->size(); ++i) {
        allocator_traits<allocator_type>::destroy(alloc, begin + i);
      }
      _storage.set_size(0);
    }

  private:
    __constexpr_cxx_std_20 void _allocate(size_type n = 0) {
      size_type old_capacity = this->capacity();
      size_type new_capacity = old_capacity == 0 ? 1 : old_capacity * 2;
      _storage.grow(max(new_capacity, n));
    }

    template<typename... Args>
    __constexpr_cxx_std_20 void _resize(size_type n, Args&&... args) {
      allocator_type alloc    = _storage.get_allocator();
      size_type      old_size = this->size();

      if (n < old_size) {
        pointer begin = _storage.front_pointer();
        for (size_type i = n; i < old_size; ++i) {
          allocator_traits<allocator_type>::destroy(alloc, begin + i);
        }

        _storage.shrink(old_size - n);
      } else if (n > old_size) {
        _storage.grow(n - old_size);

        pointer begin = _storage.front_pointer();
        for (size_type i = old_size; i < n; ++i) {
          allocator_traits<allocator_type>::construct(alloc, begin + i, forward<Args>(args)...);
        }
      }

      _storage.set_size(n);
    }

    template<typename... Args>
    __constexpr_cxx_std_20 void _emplace_back(Args&&... args) {
      if (this->size() < this->capacity()) {
        allocator_type alloc = _storage.get_allocator();
        pointer        begin = _storage.front_pointer();
        allocator_traits<allocator_type>::construct(alloc, begin + this->size(), forward<Args>(args)...);
        _storage.set_size(this->size() + 1);
      } else {
        this->_allocate();

        allocator_type alloc = _storage.get_allocator();
        pointer        begin = _storage.front_pointer();
        allocator_traits<allocator_type>::construct(alloc, begin + this->size(), forward<Args>(args)...);

        _storage.set_size(this->size() + 1);
      }
    }

    __constexpr_cxx_std_20 void _shift(size_type pos, size_type n) {
      size_type new_size = this->size() + n;
      if (new_size > this->capacity()) {
        this->_allocate(new_size);
      }
      move_backward(this->cbegin() + pos, this->cend() - 1, this->end() - 1 + n);
      _storage.set_size(new_size);
    }

    __constexpr_cxx_std_20 void _unshift(size_type pos, size_type n) {
      size_type new_size = this->size() - min(this->size(), n);
      move(this->cbegin() + pos + n, this->cend(), this->begin() + pos);
      _storage.set_size(new_size);
    }
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_STL_BASE_VLA_H_
