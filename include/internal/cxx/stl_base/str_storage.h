#ifndef CAPRESE_LIBC_INTERNAL_CXX_STL_BASE_STR_STORAGE_H_
#define CAPRESE_LIBC_INTERNAL_CXX_STL_BASE_STR_STORAGE_H_

#include <internal/attribute.h>
#include <internal/branch.h>
#include <internal/cxx/algorithm/seq.h>
#include <internal/cxx/memory/allocator_traits.h>
#include <internal/cxx/utility/fwd.h>

namespace std {
  template<typename Char, typename Traits, typename Allocator>
  class __string_storage {
  public:
    using traits_type     = Traits;
    using allocator_type  = Allocator;
    using value_type      = typename traits_type::char_type;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = typename allocator_traits<allocator_type>::pointer;
    using const_pointer   = typename allocator_traits<allocator_type>::const_pointer;
    using size_type       = typename allocator_traits<allocator_type>::size_type;
    using difference_type = typename allocator_traits<allocator_type>::difference_type;

  private:
    static constexpr size_type _threshold = alignof(max_align_t) / sizeof(value_type) - 1;

    // A typical allocator such as std::allocator is an empty class. Therefore, we can expect Empty Base Optimization to be applied.
    struct _ebo_type: public allocator_type {
      pointer _ptr;

      _ebo_type(pointer ptr): allocator_type(), _ptr(ptr) { }

      _ebo_type(pointer ptr, const allocator_type& alloc): allocator_type(alloc), _ptr(ptr) { }

      _ebo_type(pointer ptr, allocator_type&& alloc): allocator_type(move(alloc)), _ptr(ptr) { }
    };

    _ebo_type _ebo;
    size_type _length; // without null terminator

    union {
      size_type  _capacity; // including null terminator
      value_type _local[_threshold + 1];
    };

  public:
    __constexpr_cxx_std_20 __string_storage(const allocator_type& allocator) __noexcept_cxx_std_11: _ebo(_local, allocator), _length(0) {
      _local[0] = value_type();
    }

    __constexpr_cxx_std_20 __string_storage(const __string_storage& other): _ebo(_local, other._ebo), _length(other._length) {
      if (_length > _threshold) {
        _capacity = _length + 1;
        _ebo._ptr = allocator_traits<allocator_type>::allocate(_ebo, _capacity);
      }
      copy_n(other._ebo._ptr, _length + 1, _ebo._ptr);
    }

    __constexpr_cxx_std_20 __string_storage(__string_storage&& other) __noexcept_cxx_std_11: _ebo(_local, move(other._ebo)), _length(other._length) {
      if (_length > _threshold) {
        _capacity       = other._capacity;
        _ebo._ptr       = other._ebo._ptr;
        other._ebo._ptr = nullptr;
      } else {
        copy_n(other._ebo._ptr, _length + 1, _ebo._ptr);
      }
    }

    __constexpr_cxx_std_20 __string_storage(const __string_storage& other, const allocator_type& allocator): _ebo(_local, allocator), _length(other._length) {
      if (_length > _threshold) {
        _capacity = _length + 1;
        _ebo._ptr = allocator_traits<allocator_type>::allocate(_ebo, _capacity);
      }
      copy_n(other._ebo._ptr, _length + 1, _ebo._ptr);
    }

    __constexpr_cxx_std_20 __string_storage(__string_storage&& other, const allocator_type& allocator): _ebo(_local, allocator), _length(other._length) {
      if (_length > _threshold) {
        _capacity       = other._capacity;
        _ebo._ptr       = other._ebo._ptr;
        other._ebo._ptr = nullptr;
      } else {
        copy_n(other._ebo._ptr, _length + 1, _ebo._ptr);
      }
    }

    __constexpr_cxx_std_20 ~__string_storage() __noexcept_cxx_std_11 {
      if (_ebo._ptr != _local) {
        allocator_traits<allocator_type>::deallocate(_ebo, _ebo._ptr, _capacity);
        _ebo._ptr = _local;
      }
    }

    __constexpr_cxx_std_20 __string_storage& operator=(const __string_storage& other) {
      if (this == &other) {
        return *this;
      }

      if (_ebo._ptr != _local) {
        allocator_traits<allocator_type>::deallocate(_ebo, _ebo._ptr, _capacity);
        _ebo._ptr = _local;
      }

      _length = other._length;
      if (_length > _threshold) {
        _capacity = _length + 1;
        _ebo      = other._ebo;
        _ebo._ptr = allocator_traits<allocator_type>::allocate(_ebo, _capacity);
      } else {
        _ebo      = other._ebo;
        _ebo._ptr = _local;
      }
      copy_n(other._ebo._ptr, _length + 1, _ebo._ptr);

      return *this;
    }

    __constexpr_cxx_std_20 __string_storage& operator=(__string_storage&& other) __noexcept_cxx_std_11 {
      if (this == &other) {
        return *this;
      }

      if (_ebo._ptr != _local) {
        allocator_traits<allocator_type>::deallocate(_ebo, _ebo._ptr, _capacity);
        _ebo._ptr = _local;
      }

      _length = other._length;
      if (_length > _threshold) {
        _capacity       = other._capacity;
        _ebo            = move(other._ebo);
        other._ebo._ptr = other._local;
      } else {
        _ebo      = move(other._ebo);
        _ebo._ptr = _local;
        copy_n(other._ebo._ptr, _length + 1, _ebo._ptr);
      }

      return *this;
    }

    __constexpr_cxx_std_20 size_type size() const __noexcept_cxx_std_11 {
      return _length;
    }

    __constexpr_cxx_std_20 size_type max_size() const __noexcept_cxx_std_11 {
      return allocator_traits<allocator_type>::max_size(_ebo);
    }

    __constexpr_cxx_std_20 size_type capacity() const __noexcept_cxx_std_11 {
      if (_ebo._ptr != _local) {
        return _capacity - 1;
      } else {
        return _threshold;
      }
    }

    __constexpr_cxx_std_20 void set_size(size_type n) __noexcept_cxx_std_11 {
      __if_unlikely (_ebo._ptr == _local && n > _threshold) {
        _ebo._ptr = allocator_traits<allocator_type>::allocate(_ebo, n + 1);
        copy_n(_local, _length, _ebo._ptr);
        _capacity = n + 1;
      }
      _length            = n;
      _ebo._ptr[_length] = value_type();
    }

    __constexpr_cxx_std_20 pointer front_pointer() __noexcept_cxx_std_11 {
      return _ebo._ptr;
    }

    __constexpr_cxx_std_20 const_pointer front_pointer() const __noexcept_cxx_std_11 {
      return _ebo._ptr;
    }

    __constexpr_cxx_std_20 pointer back_pointer() __noexcept_cxx_std_11 {
      return _ebo._ptr + _length - 1;
    }

    __constexpr_cxx_std_20 const_pointer back_pointer() const __noexcept_cxx_std_11 {
      return _ebo._ptr + _length - 1;
    }

    __constexpr_cxx_std_20 void grow(size_type n) {
      __if_unlikely (_ebo._ptr == _local) {
        _ebo._ptr = allocator_traits<allocator_type>::allocate(_ebo, _threshold + n);
        copy_n(_local, _length + 1, _ebo._ptr);
        _capacity = _threshold + n;
      } else {
        pointer new_ptr = allocator_traits<allocator_type>::allocate(_ebo, _capacity + n);
        copy_n(_ebo._ptr, _length + 1, new_ptr);
        allocator_traits<allocator_type>::deallocate(_ebo, _ebo._ptr, _capacity);
        _ebo._ptr = new_ptr;
        _capacity += n;
      }
    }

    __constexpr_cxx_std_20 void shrink(size_type n) {
      __if_unlikely (_length < n) {
        _length = 0;
      } else {
        _length = _length - n;
      }
      _ebo._ptr[_length] = value_type();
    }

    __constexpr_cxx_std_20 allocator_type get_allocator() const __noexcept_cxx_std_11 {
      return _ebo;
    }
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_STL_BASE_STR_STORAGE_H_
