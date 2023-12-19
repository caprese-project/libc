#ifndef CAPRESE_LIBC_INTERNAL_CXX_STL_BASE_LAZY_H_
#define CAPRESE_LIBC_INTERNAL_CXX_STL_BASE_LAZY_H_

#include <internal/attribute.h>
#include <internal/cxx/memory/uninit.h>
#include <internal/cxx/type_traits/characteristic.h>
#include <internal/cxx/utility/fwd.h>

namespace std {
  template<typename T>
  class __lazy {
  private:
    alignas(T) char _storage[sizeof(T)];

  public:
    __constexpr __lazy() = default;

    template<typename... Args>
    __constexpr explicit __lazy(Args&&... args) {
      this->construct(forward<Args>(args)...);
    }

    __lazy(const __lazy&)            = delete;
    __lazy(__lazy&&)                 = delete;
    ~__lazy()                        = default;
    __lazy& operator=(const __lazy&) = delete;
    __lazy& operator=(__lazy&&)      = delete;

    template<typename... Args>
    __constexpr void construct(Args&&... args) {
      __construct_at(reinterpret_cast<T*>(_storage), forward<Args>(args)...);
    }

    __constexpr void destroy() {
      __destroy_at(reinterpret_cast<T*>(_storage));
    }

    template<typename U, typename __enable_if<__is_assignable_t<T&, U>::value, nullptr_t>::type = nullptr>
    __constexpr void assign(U&& value) {
      *reinterpret_cast<T*>(_storage) = forward<U>(value);
    }

    template<typename U>
    __constexpr void assign_or_construct(U&& value) {
      if constexpr (__is_assignable_t<T&, U>::value) {
        this->assign(forward<U>(value));
      } else {
        this->destroy();
        this->construct(forward<U>(value));
      }
    }

    __constexpr T& get() & {
      return *reinterpret_cast<T*>(_storage);
    }

    const __constexpr T& get() const& {
      return *reinterpret_cast<const T*>(_storage);
    }

    __constexpr T&& get() && {
      return move(*reinterpret_cast<T*>(_storage));
    }

    const __constexpr T&& get() const&& {
      return move(*reinterpret_cast<const T*>(_storage));
    }
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_STL_BASE_LAZY_H_
