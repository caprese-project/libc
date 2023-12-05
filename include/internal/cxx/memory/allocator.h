#ifndef CAPRESE_LIBC_INTERNAL_CXX_MEMORY_ALLOCATOR_H_
#define CAPRESE_LIBC_INTERNAL_CXX_MEMORY_ALLOCATOR_H_

#include <internal/attribute.h>
#include <internal/branch.h>
#include <internal/cxx/stddef.h>
#include <internal/cxx/type_traits/constant.h>
#include <internal/version.h>
#include <new>

namespace std {
  template<typename T>
  class allocator {
  public:
    using value_type      = T;
    using size_type       = __size_t;
    using difference_type = __ptrdiff_t;

#ifndef __CXX_STD_20__
    using pointer         = T*;
    using const_pointer   = const T*;
    using reference       = T&;
    using const_reference = const T&;
#endif // __CXX_STD_20__

#ifdef __CXX_STD_14__
    using propagate_on_container_move_assignment = __true_type;
#endif // __CXX_STD_14__

#ifdef __CXX_STD_17__
    using is_always_equal = __true_type;
#endif // __CXX_STD_17__

    __constexpr_cxx_std_20 allocator() __noexcept { }

    __constexpr_cxx_std_20 allocator(const allocator&) __noexcept { }

    template<typename U>
    __constexpr_cxx_std_20 allocator(const allocator<U>&) __noexcept { }

    __constexpr_cxx_std_20 ~allocator() __noexcept { }

    __constexpr_cxx_std_20 allocator& operator=(const allocator&) = default;

    __nodiscard_cxx_std_20 __constexpr_cxx_std_20 T* allocate(size_type n) {
      return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    __constexpr_cxx_std_20 void deallocate(T* ptr, __unused size_type n) {
#ifdef __CXX_STD_14__
      ::operator delete(ptr, n * sizeof(T));
#else  // ^^^ __CXX_STD_14__ ^^^ / vvv !__CXX_STD_14__ vvv
      ::operator delete(ptr);
#endif // !__CXX_STD_14__
    }

    template<typename U>
    friend __constexpr_cxx_std_20 bool operator==(const allocator&, const allocator<U>&) __noexcept {
      return true;
    }

    template<typename U>
    friend __constexpr_cxx_std_20 bool operator!=(const allocator&, const allocator<U>&) __noexcept {
      return false;
    }
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_MEMORY_ALLOCATOR_H_
