#ifndef CAPRESE_LIBC_INTERNAL_CXX_STL_BASE_VEC_STORAGE_H_
#define CAPRESE_LIBC_INTERNAL_CXX_STL_BASE_VEC_STORAGE_H_

#include <internal/attribute.h>
#include <internal/branch.h>
#include <internal/cxx/algorithm/seq.h>
#include <internal/cxx/memory/allocator_traits.h>
#include <internal/cxx/utility/fwd.h>

namespace std {
  template<typename T, typename Allocator>
  class __vector_storage {
  public:
    using value_type      = T;
    using reference       = T&;
    using const_reference = const T&;
    using allocator_type  = Allocator;
    using pointer         = typename allocator_traits<allocator_type>::pointer;
    using const_pointer   = typename allocator_traits<allocator_type>::const_pointer;
    using size_type       = typename allocator_traits<allocator_type>::size_type;
    using difference_type = typename allocator_traits<allocator_type>::difference_type;

  private:
    allocator_type _allocator;
    pointer        _begin;
    pointer        _end;
    size_type      _size;

  public:
    __constexpr_cxx_std_20 __vector_storage(const allocator_type& allocator) __noexcept_cxx_std_11: _allocator(allocator), _begin(nullptr), _end(nullptr), _size(0) { }

    __constexpr_cxx_std_20 __vector_storage(const __vector_storage& other): _allocator(other._allocator), _begin(nullptr), _end(nullptr), _size(other._size) {
      _begin = allocator_traits<allocator_type>::allocate(_allocator, _size);
      copy_n(other._begin, _size, _begin);
      _end = _begin + _size;
    }

    __constexpr_cxx_std_20 __vector_storage(__vector_storage&& other) __noexcept_cxx_std_11: _allocator(move(other._allocator)), _begin(other._begin), _end(other._end), _size(other._size) {
      other._begin = nullptr;
      other._end   = nullptr;
      other._size  = 0;
    }

    __constexpr_cxx_std_20 __vector_storage(const __vector_storage& other, const allocator_type& allocator): _allocator(allocator), _begin(nullptr), _end(nullptr), _size(other._size) {
      _begin = allocator_traits<allocator_type>::allocate(_allocator, _size);
      copy_n(other._begin, _size, _begin);
      _end = _begin + _size;
    }

    __constexpr_cxx_std_20 __vector_storage(__vector_storage&& other, const allocator_type& allocator): _allocator(allocator), _begin(other._begin), _end(other._end), _size(other._size) {
      other._begin = nullptr;
      other._end   = nullptr;
      other._size  = 0;
    }

    __constexpr_cxx_std_20 ~__vector_storage() {
      allocator_traits<allocator_type>::deallocate(_allocator, _begin, _end - _begin);
      _begin = nullptr;
      _end   = nullptr;
      _size  = 0;
    }

    __constexpr_cxx_std_20 __vector_storage& operator=(const __vector_storage& other) {
      if (this == &other) {
        return *this;
      }

      allocator_traits<allocator_type>::deallocate(_allocator, _begin, _end - _begin);
      _begin = nullptr;
      _end   = nullptr;
      _size  = 0;

      _size  = other._end - other._begin;
      _begin = allocator_traits<allocator_type>::allocate(_allocator, _size);
      copy_n(other._begin, _size, _begin);
      _end = _begin + _size;

      return *this;
    }

    __constexpr_cxx_std_20 __vector_storage& operator=(__vector_storage&& other) __noexcept_cxx_std_11 {
      if (this == &other) {
        return *this;
      }

      allocator_traits<allocator_type>::deallocate(_allocator, _begin, _end - _begin);
      _begin = nullptr;
      _end   = nullptr;
      _size  = 0;

      _allocator = move(other._allocator);
      _begin     = other._begin;
      _end       = other._end;
      _size      = other._size;

      other._begin = nullptr;
      other._end   = nullptr;
      other._size  = 0;

      return *this;
    }

    __constexpr_cxx_std_20 size_type size() const __noexcept_cxx_std_11 {
      return _size;
    }

    __constexpr_cxx_std_20 size_type max_size() const __noexcept_cxx_std_11 {
      return allocator_traits<allocator_type>::max_size();
    }

    __constexpr_cxx_std_20 size_type capacity() const __noexcept_cxx_std_11 {
      return _end - _begin;
    }

    __constexpr_cxx_std_20 void set_size(size_type n) __noexcept_cxx_std_11 {
      _size = n;
    }

    __constexpr_cxx_std_20 pointer front_pointer() __noexcept_cxx_std_11 {
      return _begin;
    }

    __constexpr_cxx_std_20 const_pointer front_pointer() const __noexcept_cxx_std_11 {
      return _begin;
    }

    __constexpr_cxx_std_20 pointer back_pointer() __noexcept_cxx_std_11 {
      return _begin + _size - 1;
    }

    __constexpr_cxx_std_20 const_pointer back_pointer() const __noexcept_cxx_std_11 {
      return _begin + _size - 1;
    }

    __constexpr_cxx_std_20 void grow(size_type n) {
      size_type capacity     = _end - _begin;
      size_type new_capacity = _size + n;
      if (new_capacity <= capacity) {
        return;
      }

      pointer new_begin = allocator_traits<allocator_type>::allocate(_allocator, new_capacity);
      move(_begin, _begin + _size, new_begin);
      allocator_traits<allocator_type>::deallocate(_allocator, _begin, capacity);

      _begin = new_begin;
      _end   = new_begin + new_capacity;
    }

    __constexpr_cxx_std_20 void shrink(size_type n) {
      __if_unlikely (_size < n) {
        _size = 0;
      } else {
        _size = _size - n;
      }
    }

    __constexpr_cxx_std_20 allocator_type get_allocator() const __noexcept_cxx_std_11 {
      return _allocator;
    }
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_STL_BASE_VEC_STORAGE_H_
