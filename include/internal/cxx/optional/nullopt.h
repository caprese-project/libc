#ifndef CAPRESE_LIBC_INTERNAL_CXX_OPTIONAL_NULLOPT_H_
#define CAPRESE_LIBC_INTERNAL_CXX_OPTIONAL_NULLOPT_H_

namespace std {
  struct __nullopt_constructor_argument { };

  struct nullopt_t {
    explicit constexpr nullopt_t(__nullopt_constructor_argument) noexcept { }
  };

  inline constexpr nullopt_t nullopt { __nullopt_constructor_argument {} };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_OPTIONAL_NULLOPT_H_
