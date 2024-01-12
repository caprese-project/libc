#ifndef CAPRESE_LIBC_INTERNAL_CXX_MEMORY_TO_ADDRESS_H_
#define CAPRESE_LIBC_INTERNAL_CXX_MEMORY_TO_ADDRESS_H_

#include <internal/attribute.h>
#include <internal/cxx/memory/pointer_traits.h>
#include <internal/cxx/type_traits/type.h>

namespace std {
  template<typename T>
  __constexpr auto __to_address(const T& ptr) noexcept -> decltype(pointer_traits<T>::to_address(ptr)) {
    return pointer_traits<T>::to_address(ptr);
  }

  template<typename T, typename... Unused>
  __constexpr auto __to_address(const T& ptr, Unused...) noexcept {
    return __to_address(ptr.operator->());
  }

  template<typename T>
  __constexpr T* __to_address(T* ptr) noexcept {
    static_assert(!__is_function_t<T>::value);
    return ptr;
  }
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_MEMORY_TO_ADDRESS_H_
