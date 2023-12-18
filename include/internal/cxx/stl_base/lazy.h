#ifndef CAPRESE_LIBC_INTERNAL_CXX_STL_BASE_LAZY_H_
#define CAPRESE_LIBC_INTERNAL_CXX_STL_BASE_LAZY_H_

#include <internal/attribute.h>
#include <internal/cxx/type_traits/characteristic.h>
#include <internal/cxx/utility/fwd.h>

namespace std {
  template<typename T, bool = __is_trivially_destructible<T>::value>
  class __lazy;

  template<typename T>
  class __lazy<T, true> {
    T _value;

  public:
    __constexpr __lazy() = default;

    template<typename... Args>
    __constexpr explicit __lazy(Args&&... args): _value(forward<Args>(args)...) { }

    template<typename... Args>
    __constexpr void construct(Args&&... args) {
      _value = T(forward<Args>(args)...);
    }

    __constexpr T& get() & {
      return _value;
    }

    const __constexpr T& get() const& {
      return _value;
    }

    __constexpr T&& get() && {
      return move(_value);
    }

    const __constexpr T&& get() const&& {
      return move(_value);
    }
  };

  template<typename T>
  class __lazy<T, false> {
  private:
    alignas(T) char _storage[sizeof(T)];

  public:
    __constexpr __lazy() = default;

    template<typename... Args>
    __constexpr explicit __lazy(Args&&... args) {
      this->construct(forward<Args>(args)...);
    }

    template<typename... Args>
    __constexpr void construct(Args&&... args) {
      ::operator new(_storage) T(forward<Args>(args)...);
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
