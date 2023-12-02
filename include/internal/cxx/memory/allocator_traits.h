#ifndef CAPRESE_LIBC_INTERNAL_CXX_MEMORY_ALLOCATOR_TRAITS_H_
#define CAPRESE_LIBC_INTERNAL_CXX_MEMORY_ALLOCATOR_TRAITS_H_

#include <internal/cxx/memory/pointer_traits.h>
#include <internal/cxx/type_traits/detection.h>
#include <internal/cxx/utility/fwd.h>

namespace std {
  template<typename Allocator>
  struct allocator_traits {
  private:
    template<typename T>
    using __pointer = typename T::pointer;

    template<typename T>
    using __const_pointer = typename T::const_pointer;

    template<typename T>
    using __void_pointer = typename T::void_pointer;

    template<typename T>
    using __const_void_pointer = typename T::const_void_pointer;

    template<typename T>
    using __difference_type = typename T::difference_type;

    template<typename T>
    using __size_type = typename T::size_type;

    template<typename T>
    using __propagate_on_container_copy_assignment = typename T::propagate_on_container_copy_assignment;

    template<typename T>
    using __propagate_on_container_move_assignment = typename T::propagate_on_container_move_assignment;

    template<typename T>
    using __propagate_on_container_swap = typename T::propagate_on_container_swap;

    template<typename T>
    using __is_always_equal = typename T::is_always_equal;

    template<typename T>
    using __rebind_alloc = typename T::template rebind_alloc<typename T::value_type>;

    template<typename T>
    using __rebind_traits = allocator_traits<__rebind_alloc<T>>;

  public:
    using allocator_type                         = Allocator;
    using value_type                             = typename Allocator::value_type;
    using pointer                                = typename __detect_type<__pointer, value_type*, allocator_type>::type;
    using const_pointer                          = typename __detect_type<__const_pointer, typename pointer_traits<pointer>::rebind<const value_type>, allocator_type>::type;
    using void_pointer                           = typename __detect_type<__void_pointer, typename pointer_traits<pointer>::rebind<void>, allocator_type>::type;
    using const_void_pointer                     = typename __detect_type<__const_void_pointer, typename pointer_traits<pointer>::rebind<const void>, allocator_type>::type;
    using difference_type                        = typename __detect_type<__difference_type, typename pointer_traits<pointer>::difference_type, allocator_type>::type;
    using size_type                              = typename __detect_type<__size_type, typename __make_unsigned<difference_type>::type, allocator_type>::type;
    using propagate_on_container_copy_assignment = typename __detect_type<__propagate_on_container_copy_assignment, __false_type, allocator_type>::type;
    using propagate_on_container_move_assignment = typename __detect_type<__propagate_on_container_move_assignment, __false_type, allocator_type>::type;
    using propagate_on_container_swap            = typename __detect_type<__propagate_on_container_swap, __false_type, allocator_type>::type;
    using is_always_equal                        = typename __detect_type<__is_always_equal, __is_empty_t<allocator_type>::type, allocator_type>::type;

  private:
    template<typename Alloc>
    static constexpr auto __allocate(Alloc& allocator, size_type n, const_void_pointer hint, int) -> decltype(allocator.allocate(n, hint)) {
      return allocator.allocate(n, hint);
    }

    template<typename Alloc>
    static constexpr pointer __allocate(Alloc& allocator, size_type n, const_void_pointer, ...) {
      return allocator.allocate(n);
    }

    template<typename Alloc>
    static constexpr auto __max_size(Alloc& allocator, int) -> decltype(allocator.max_size()) {
      return allocator.max_size();
    }

    template<typename Alloc>
    static constexpr size_type __max_size(Alloc&, ...) {
      return __numeric_limits<size_type>::max() / sizeof(value_type);
    }

    template<typename Alloc, typename T, typename... Args>
    static constexpr auto __construct(Alloc& allocator, T* ptr, Args&&... args) -> decltype(allocator.construct(ptr, forward<Args>(args)...)) {
      allocator.construct(ptr, forward<Args>(args)...);
    }

    template<typename Alloc, typename T, typename... Args>
    static constexpr void __construct(Alloc&, T* ptr, Args&&... args) {
#ifdef __CXX_STD_20__
      construct_at(ptr, forward<Args>(args)...);
#else  // ^^^ __CXX_STD_20__ ^^^ / vvv !__CXX_STD_20__ vvv
      ::new (static_cast<void*>(ptr)) T(forward<Args>(args)...);
#endif // !__CXX_STD_20__
    }

    template<typename Alloc, typename T>
    static constexpr auto __destroy(Alloc& allocator, T* ptr, int) -> decltype(allocator.destroy(ptr)) {
      allocator.destroy(ptr);
    }

    template<typename Alloc, typename T>
    static constexpr void __destroy(Alloc&, T* ptr, ...) {
#ifdef __CXX_STD_20__
      destroy_at(ptr);
#else  // ^^^ __CXX_STD_20__ ^^^ / vvv !__CXX_STD_20__ vvv
      ptr->~T();
#endif // !__CXX_STD_20__
    }

  public:
    __nodiscard_cxx_std_20 static __constexpr_cxx_std_20 pointer allocate(allocator_type& allocator, size_type n) {
      return allocator.allocate(n);
    }

    __nodiscard_cxx_std_20 static __constexpr_cxx_std_20 pointer allocate(allocator_type& allocator, size_type n, const_void_pointer hint) {
      return __allocate(allocator, n, hint, 0);
    }

    static __constexpr_cxx_std_20 void deallocate(allocator_type& allocator, pointer ptr, size_type n) {
      allocator.deallocate(ptr, n);
    }

    static __constexpr_cxx_std_20 size_type max_size(const allocator_type& allocator) __noexcept {
      return allocator.max_size();
    }

    template<typename T, typename... Args>
    static __constexpr_cxx_std_20 void construct(allocator_type& allocator, T* ptr, Args&&... args) {
      __construct(allocator, ptr, forward<Args>(args)...);
    }

    template<typename T>
    static __constexpr_cxx_std_20 void destroy(allocator_type& allocator, T* ptr) {
      __destroy(allocator, ptr, 0);
    }
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_MEMORY_ALLOCATOR_TRAITS_H_
