#ifndef CAPRESE_LIBC_INTERNAL_CXX_MEMORY_ADDRESSOF_H_
#define CAPRESE_LIBC_INTERNAL_CXX_MEMORY_ADDRESSOF_H_

namespace std {
#ifdef __GNUC__

  template<typename T>
  constexpr T* __addressof(T& arg) noexcept {
    return __builtin_addressof(arg);
  }

#else // ^^^ __GNUC__ ^^^ / vvv !__GNUC__ vvv

  template<typename T>
  constexpr T* __addressof(T& arg) noexcept {
    return reinterpret_cast<T*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(arg)));
  }

#endif // !__GNUC_
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_MEMORY_ADDRESSOF_H_
