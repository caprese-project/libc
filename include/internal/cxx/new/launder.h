#ifndef CAPRESE_LIBC_INTERNAL_CXX_NEW_LAUNDER_H_
#define CAPRESE_LIBC_INTERNAL_CXX_NEW_LAUNDER_H_

#include <internal/attribute.h>

namespace std {
#ifdef __CXX_STD_17__

  template<typename T>
  __nodiscard_cxx_std_20 constexpr T* launder(T* p) noexcept {
#ifdef __GNUC__
    return __builtin_launder(p);
#else // ^^^ __GNUC__ ^^^ / vvv !__GNUC__ vvv
#warning "The implementation of std::launder is not yet implemented for this compiler."
    return p;
#endif // !__GNUC__
  }

  template<typename R, typename... Args>
  void launder(R (*)(Args...)) = delete;

  template<typename R, typename... Args>
  void laundering(R (*)(Args..., ...)) = delete;

  void launder(void*)                = delete;
  void launder(const void*)          = delete;
  void launder(volatile void*)       = delete;
  void launder(const volatile void*) = delete;

#endif // __CXX_STD_17__
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_NEW_LAUNDER_H_
