#ifndef CAPRESE_LIBC_INTERNAL_CXX_STL_BASE_SPEC_MEMBERS_H_
#define CAPRESE_LIBC_INTERNAL_CXX_STL_BASE_SPEC_MEMBERS_H_

#include <internal/attribute.h>

namespace std {
  template<bool Enable, typename = void>
  struct __default_constructible;

  template<bool Enable, typename = void>
  struct __destructible;

  template<bool Enable, typename = void>
  struct __copy_constructible;

  template<bool Enable, typename = void>
  struct __move_constructible;

  template<bool Enable, typename = void>
  struct __copy_assignable;

  template<bool Enable, typename = void>
  struct __move_assignable;

  template<>
  struct __default_constructible<true> {
    __constexpr                          __default_constructible() noexcept                               = default;
    __constexpr                          __default_constructible(const __default_constructible&) noexcept = default;
    __constexpr                          __default_constructible(__default_constructible&&) noexcept      = default;
    __constexpr __default_constructible& operator=(const __default_constructible&) noexcept               = default;
    __constexpr __default_constructible& operator=(__default_constructible&&) noexcept                    = default;
  };

  template<>
  struct __default_constructible<false> {
    __constexpr                          __default_constructible() noexcept                               = delete;
    __constexpr                          __default_constructible(const __default_constructible&) noexcept = default;
    __constexpr                          __default_constructible(__default_constructible&&) noexcept      = default;
    __constexpr __default_constructible& operator=(const __default_constructible&) noexcept               = default;
    __constexpr __default_constructible& operator=(__default_constructible&&) noexcept                    = default;
  };

  template<>
  struct __destructible<true> {
    __constexpr ~__destructible() noexcept = default;
  };

  template<>
  struct __destructible<false> {
    __constexpr ~__destructible() noexcept = delete;
  };

  template<>
  struct __copy_constructible<true> {
    __constexpr                       __copy_constructible() noexcept                            = default;
    __constexpr                       __copy_constructible(const __copy_constructible&) noexcept = default;
    __constexpr                       __copy_constructible(__copy_constructible&&) noexcept      = default;
    __constexpr __copy_constructible& operator=(const __copy_constructible&) noexcept            = default;
    __constexpr __copy_constructible& operator=(__copy_constructible&&) noexcept                 = default;
  };

  template<>
  struct __copy_constructible<false> {
    __constexpr                       __copy_constructible() noexcept                            = default;
    __constexpr                       __copy_constructible(const __copy_constructible&) noexcept = delete;
    __constexpr                       __copy_constructible(__copy_constructible&&) noexcept      = default;
    __constexpr __copy_constructible& operator=(const __copy_constructible&) noexcept            = default;
    __constexpr __copy_constructible& operator=(__copy_constructible&&) noexcept                 = default;
  };

  template<>
  struct __move_constructible<true> {
    __constexpr                       __move_constructible() noexcept                            = default;
    __constexpr                       __move_constructible(const __move_constructible&) noexcept = default;
    __constexpr                       __move_constructible(__move_constructible&&) noexcept      = default;
    __constexpr __move_constructible& operator=(const __move_constructible&) noexcept            = default;
    __constexpr __move_constructible& operator=(__move_constructible&&) noexcept                 = default;
  };

  template<>
  struct __move_constructible<false> {
    __constexpr                       __move_constructible() noexcept                            = default;
    __constexpr                       __move_constructible(const __move_constructible&) noexcept = default;
    __constexpr                       __move_constructible(__move_constructible&&) noexcept      = delete;
    __constexpr __move_constructible& operator=(const __move_constructible&) noexcept            = default;
    __constexpr __move_constructible& operator=(__move_constructible&&) noexcept                 = default;
  };

  template<>
  struct __copy_assignable<true> {
    __constexpr                    __copy_assignable() noexcept                         = default;
    __constexpr                    __copy_assignable(const __copy_assignable&) noexcept = default;
    __constexpr                    __copy_assignable(__copy_assignable&&) noexcept      = default;
    __constexpr __copy_assignable& operator=(const __copy_assignable&) noexcept         = default;
    __constexpr __copy_assignable& operator=(__copy_assignable&&) noexcept              = default;
  };

  template<>
  struct __copy_assignable<false> {
    __constexpr                    __copy_assignable() noexcept                         = default;
    __constexpr                    __copy_assignable(const __copy_assignable&) noexcept = default;
    __constexpr                    __copy_assignable(__copy_assignable&&) noexcept      = default;
    __constexpr __copy_assignable& operator=(const __copy_assignable&) noexcept         = delete;
    __constexpr __copy_assignable& operator=(__copy_assignable&&) noexcept              = default;
  };

  template<>
  struct __move_assignable<true> {
    __constexpr                    __move_assignable() noexcept                         = default;
    __constexpr                    __move_assignable(const __move_assignable&) noexcept = default;
    __constexpr                    __move_assignable(__move_assignable&&) noexcept      = default;
    __constexpr __move_assignable& operator=(const __move_assignable&) noexcept         = default;
    __constexpr __move_assignable& operator=(__move_assignable&&) noexcept              = default;
  };

  template<>
  struct __move_assignable<false> {
    __constexpr                    __move_assignable() noexcept                         = default;
    __constexpr                    __move_assignable(const __move_assignable&) noexcept = default;
    __constexpr                    __move_assignable(__move_assignable&&) noexcept      = default;
    __constexpr __move_assignable& operator=(const __move_assignable&) noexcept         = default;
    __constexpr __move_assignable& operator=(__move_assignable&&) noexcept              = delete;
  };

  template<bool DefaultConstructible, bool Destructible, bool CopyConstructible, bool MoveConstructible, bool CopyAssignable, bool MoveAssignable, typename = void>
  struct __spec_members: private __default_constructible<DefaultConstructible>,
                         private __destructible<Destructible>,
                         private __copy_constructible<CopyConstructible>,
                         private __move_constructible<MoveConstructible>,
                         private __copy_assignable<CopyAssignable>,
                         private __move_assignable<MoveAssignable> { };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_STL_BASE_SPEC_MEMBERS_H_
