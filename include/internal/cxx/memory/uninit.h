#ifndef CAPRESE_LIBC_INTERNAL_CXX_MEMORY_UNINIT_H_
#define CAPRESE_LIBC_INTERNAL_CXX_MEMORY_UNINIT_H_

#include <internal/cxx/memory/addressof.h>
#include <internal/cxx/new/launder.h>
#include <internal/cxx/new/operator.h>
#include <internal/cxx/type_traits/type.h>
#include <internal/cxx/utility/fwd.h>
#include <internal/version.h>

namespace std {
  template<class T, class... Args>
  constexpr T* __construct_at(T* location, Args&&... args) {
    auto ptr = ::new (const_cast<void*>(static_cast<const volatile void*>(location))) T(forward<Args>(args)...);
    if constexpr (__is_array<T>::value) {
      return launder(location);
    } else {
      return ptr;
    }
  }

  template<typename T>
  __constexpr inline void __destroy_at(T* location) {
    if constexpr (__is_array<T>::value) {
      for (auto& elem : *location) {
        destroy_at(__addressof(elem));
      }
    } else {
      location->~T();
    }
  }

#ifdef __CXX_STD_17__

  template<typename T>
  __constexpr_cxx_std_20 inline void destroy_at(T* location) {
    __destroy_at(location);
  }

#endif // __CXX_STD_17__

#ifdef __CXX_STD_20__

  template<class T, class... Args>
  constexpr T* construct_at(T* location, Args&&... args) {
    return __construct_at(location, forward<Args>(args)...);
  }

#endif // __CXX_STD_20__
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_MEMORY_UNINIT_H_
