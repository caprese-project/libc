#ifndef CAPRESE_LIBC_INTERNAL_CXX_OPTIONAL_OPTIONAL_H_
#define CAPRESE_LIBC_INTERNAL_CXX_OPTIONAL_OPTIONAL_H_

#include <initializer_list>
#include <internal/cxx/memory/addressof.h>
#include <internal/cxx/memory/uninit.h>
#include <internal/cxx/optional/bad_optional_access.h>
#include <internal/cxx/optional/nullopt.h>
#include <internal/cxx/stl_base/spec_members.h>
#include <internal/cxx/type_traits/modify.h>
#include <internal/cxx/type_traits/type.h>
#include <internal/cxx/type_traits/type_relation.h>
#include <internal/cxx/utility/fwd.h>
#include <internal/cxx/utility/in_place.h>
#include <internal/cxx/utility/swap.h>
#include <internal/exception.h>

namespace std {
  struct __optional_non_trivial_tag { };

  template<typename T>
  struct __optional_storage_base {
    template<typename U, bool = __is_trivially_destructible_t<U>::value>
    struct __storage_type;

    struct __dummy_type { };

    template<typename U>
    using __value_type = typename __remove_cv<U>::type;

    template<typename U>
    struct __storage_type<U, true> {
      union {
        __dummy_type    _dummy;
        __value_type<U> _value;
      };

      constexpr __storage_type() noexcept: _dummy {} { }

      template<typename... Args>
      constexpr __storage_type(in_place_t, Args&&... args): _value(forward<Args>(args)...) { }

      template<typename V, typename... Args>
      constexpr __storage_type(initializer_list<V> init_list, Args&&... args): _value(init_list, forward<Args>(args)...) { }
    };

    template<typename U>
    struct __storage_type<U, false> {
      union {
        __dummy_type    _dummy;
        __value_type<U> _value;
      };

      constexpr __storage_type() noexcept: _dummy {} { }

      template<typename... Args>
      constexpr __storage_type(in_place_t, Args&&... args): _value(forward<Args>(args)...) { }

      template<typename V, typename... Args>
      constexpr __storage_type(initializer_list<V> init_list, Args&&... args): _value(init_list, forward<Args>(args)...) { }

      constexpr ~__storage_type() { }
    };

    __storage_type<T> _storage;
    bool              _has_value;

    constexpr __optional_storage_base()                                          = default;
    constexpr __optional_storage_base(const __optional_storage_base&)            = default;
    constexpr __optional_storage_base(__optional_storage_base&&)                 = default;
    constexpr ~__optional_storage_base()                                         = default;
    constexpr __optional_storage_base& operator=(const __optional_storage_base&) = default;
    constexpr __optional_storage_base& operator=(__optional_storage_base&&)      = default;

    constexpr __optional_storage_base(const __optional_storage_base& other, __optional_non_trivial_tag): _has_value(other._has_value) {
      if (other._has_value) {
        this->construct(other._storage._value);
      }
    }

    constexpr __optional_storage_base(__optional_storage_base&& other, __optional_non_trivial_tag): _has_value(other._has_value) {
      if (other._has_value) {
        this->construct(move(other._storage._value));
        other._has_value = false;
      }
    }

    template<typename... Args>
    constexpr __optional_storage_base(in_place_t in_place, Args&&... args): _storage(in_place, forward<Args>(args)...),
                                                                            _has_value(true) { }

    template<typename U, typename... Args>
    constexpr __optional_storage_base(initializer_list<U> init_list, Args&&... args): _storage(init_list, forward<Args>(args)...),
                                                                                      _has_value(true) { }

    template<typename... Args>
    constexpr void construct(Args&&... args) noexcept(__is_nothrow_constructible_t<__value_type<T>, Args...>::value) {
      __construct_at(__addressof(_storage._value), forward<Args>(args)...);
      this->_has_value = true;
    }

    constexpr void destroy() noexcept {
      if (this->_has_value) {
        __destroy_at(__addressof(_storage._value));
        this->_has_value = false;
      }
    }

    constexpr void copy(const __optional_storage_base& other) {
      if (this->_has_value && other->_has_value) {
        __base::_storage._value = other->_storage._value;
      } else if (this->_has_value && !other->_has_value) {
        this->destroy();
      } else if (!this->_has_value && other->_has_value) {
        this->construct(other->_storage._value);
      }
    }

    constexpr void move(__optional_storage_base&& other) {
      if (this->_has_value && other->_has_value) {
        __base::_storage._value = move(other->_storage._value);
      } else if (this->_has_value && !other->_has_value) {
        this->destroy();
      } else if (!this->_has_value && other->_has_value) {
        this->construct(move(other->_storage._value));
      }
    }

    constexpr T& get() {
      if (!this->_has_value) {
        __throw(bad_optional_access());
      }

      return __base::_storage._value;
    }

    constexpr const T& get() const {
      if (!this->_has_value) {
        __throw(bad_optional_access());
      }

      return __base::_storage._value;
    }
  };

  template<typename T,
           bool TriviallyDestructible = __is_trivially_destructible_t<T>::value,
           bool TriviallyCopyable     = __conjunction<__is_trivially_copy_constructible<T>, __is_trivially_copy_assignable<T>>::value,
           bool TriviallyMovable      = __conjunction<__is_trivially_move_constructible<T>, __is_trivially_move_assignable<T>>::value>
  class __optional_storage;

  template<typename T>
  struct __optional_storage<T, true, true, true>: public __optional_storage_base<T> {
    using __base = __optional_storage_base<T>;
    using __base::__base;

    constexpr __optional_storage() = default;
  };

  template<typename T>
  struct __optional_storage<T, true, false, true>: public __optional_storage_base<T> {
    using __base = __optional_storage_base<T>;
    using __base::__base;

    constexpr __optional_storage()                                = default;
    constexpr __optional_storage(const __optional_storage&)       = default;
    constexpr __optional_storage(__optional_storage&&)            = default;
    constexpr ~__optional_storage()                               = default;
    constexpr __optional_storage& operator=(__optional_storage&&) = default;

    constexpr __optional_storage& operator=(const __optional_storage& other) {
      __base::copy(other);
      return *this;
    }
  };

  template<typename T>
  struct __optional_storage<T, true, true, false>: public __optional_storage_base<T> {
    using __base = __optional_storage_base<T>;
    using __base::__base;

    constexpr __optional_storage()                                     = default;
    constexpr __optional_storage(const __optional_storage&)            = default;
    constexpr __optional_storage(__optional_storage&&)                 = default;
    constexpr ~__optional_storage()                                    = default;
    constexpr __optional_storage& operator=(const __optional_storage&) = default;

    constexpr __optional_storage& operator=(__optional_storage&& other) {
      __base::move(other);
      return *this;
    }
  };

  template<typename T>
  struct __optional_storage<T, true, false, false>: public __optional_storage_base<T> {
    using __base = __optional_storage_base<T>;
    using __base::__base;

    constexpr __optional_storage()                          = default;
    constexpr __optional_storage(const __optional_storage&) = default;
    constexpr __optional_storage(__optional_storage&&)      = default;
    constexpr ~__optional_storage()                         = default;

    constexpr __optional_storage& operator=(const __optional_storage& other) {
      __base::copy(other);
      return *this;
    }

    constexpr __optional_storage& operator=(__optional_storage&& other) {
      __base::move(other);
      return *this;
    }
  };

  template<typename T, bool Copyable, bool Movable>
  struct __optional_storage<T, false, Copyable, Movable>: public __optional_storage<T, true, false, false> {
    using __base = __optional_storage<T, true, false, false>;
    using __base::__base;

    constexpr __optional_storage()                                     = default;
    constexpr __optional_storage(const __optional_storage&)            = default;
    constexpr __optional_storage(__optional_storage&&)                 = default;
    constexpr __optional_storage& operator=(const __optional_storage&) = default;
    constexpr __optional_storage& operator=(__optional_storage&&)      = default;

    constexpr ~__optional_storage() {
      __base::destroy();
    }
  };

  template<typename T, bool TriviallyCopyConstructible = __is_trivially_copy_constructible<T>::value, bool TriviallyMoveConstructible = __is_trivially_move_constructible<T>::value>
  class __optional_base;

  template<typename T>
  class __optional_base<T, true, true> {
  protected:
    using __storage = __optional_storage<T>;
    __storage _storage;

  public:
    constexpr __optional_base()                                  = default;
    constexpr __optional_base(const __optional_base&)            = default;
    constexpr __optional_base(__optional_base&&)                 = default;
    constexpr __optional_base& operator=(const __optional_base&) = default;
    constexpr __optional_base& operator=(__optional_base&&)      = default;

    template<typename... Args, typename __enable_if<__is_constructible_t<T, Args...>::value, nullptr_t>::type = nullptr>
    constexpr explicit __optional_base(in_place_t, Args&&... args): _storage(in_place, forward<Args>(args)...) { }

    template<typename U, typename... Args, typename __enable_if<__is_constructible_t<T, initializer_list<U>&, Args...>::value, nullptr_t>::type = nullptr>
    constexpr explicit __optional_base(in_place_t, initializer_list<U> init_list, Args&&... args): _storage(init_list, forward<Args>(args)...) { }
  };

  template<typename T>
  class __optional_base<T, false, true> {
  protected:
    using __storage = __optional_storage<T>;
    __storage _storage;

  public:
    constexpr __optional_base()                                  = default;
    constexpr __optional_base(__optional_base&&)                 = default;
    constexpr __optional_base& operator=(const __optional_base&) = default;
    constexpr __optional_base& operator=(__optional_base&&)      = default;

    constexpr __optional_base(const __optional_base& other): _storage(other._storage, __optional_non_trivial_tag {}) { }

    template<typename... Args, typename __enable_if<__is_constructible_t<T, Args...>::value, nullptr_t>::type = nullptr>
    constexpr explicit __optional_base(in_place_t, Args&&... args): _storage(in_place, forward<Args>(args)...) { }

    template<typename U, typename... Args, typename __enable_if<__is_constructible_t<T, initializer_list<U>&, Args...>::value, nullptr_t>::type = nullptr>
    constexpr explicit __optional_base(in_place_t, initializer_list<U> init_list, Args&&... args): _storage(init_list, forward<Args>(args)...) { }
  };

  template<typename T>
  class __optional_base<T, true, false> {
  protected:
    using __storage = __optional_storage<T>;
    __storage _storage;

  public:
    constexpr __optional_base()                                  = default;
    constexpr __optional_base(const __optional_base&)            = default;
    constexpr __optional_base& operator=(const __optional_base&) = default;
    constexpr __optional_base& operator=(__optional_base&&)      = default;

    constexpr __optional_base(__optional_base&& other) noexcept(__is_nothrow_move_constructible<T>::value): _storage(move(other._storage), __optional_non_trivial_tag {}) { }

    template<typename... Args, typename __enable_if<__is_constructible_t<T, Args...>::value, nullptr_t>::type = nullptr>
    constexpr explicit __optional_base(in_place_t, Args&&... args): _storage(in_place, forward<Args>(args)...) { }

    template<typename U, typename... Args, typename __enable_if<__is_constructible_t<T, initializer_list<U>&, Args...>::value, nullptr_t>::type = nullptr>
    constexpr explicit __optional_base(in_place_t, initializer_list<U> init_list, Args&&... args): _storage(init_list, forward<Args>(args)...) { }
  };

  template<typename T>
  class __optional_base<T, false, false> {
  protected:
    using __storage = __optional_storage<T>;
    __storage _storage;

  public:
    constexpr __optional_base()                                  = default;
    constexpr __optional_base& operator=(const __optional_base&) = default;
    constexpr __optional_base& operator=(__optional_base&&)      = default;

    constexpr __optional_base(const __optional_base& other): _storage(other._storage, __optional_non_trivial_tag {}) { }

    constexpr __optional_base(__optional_base&& other) noexcept(__is_nothrow_move_constructible<T>::value): _storage(move(other._storage), __optional_non_trivial_tag {}) { }

    template<typename... Args, typename __enable_if<__is_constructible_t<T, Args...>::value, nullptr_t>::type = nullptr>
    constexpr explicit __optional_base(in_place_t, Args&&... args): _storage(in_place, forward<Args>(args)...) { }

    template<typename U, typename... Args, typename __enable_if<__is_constructible_t<T, initializer_list<U>&, Args...>::value, nullptr_t>::type = nullptr>
    constexpr explicit __optional_base(in_place_t, initializer_list<U> init_list, Args&&... args): _storage(init_list, forward<Args>(args)...) { }
  };

  template<typename T>
  class optional: private __optional_base<T>,
                  private __spec_members<true,
                                         true,
                                         __is_copy_constructible<T>::value,
                                         __is_move_constructible<T>::value,
                                         __conjunction<__is_copy_constructible<T>, __is_copy_assignable<T>>,
                                         __conjunction<__is_move_constructible<T>, __is_move_assignable<T>>> {
    static_assert(!__is_reference<T>::value);
    static_assert(!__is_same_t<nullopt_t, __remove_cv<T>::type>::value);
    static_assert(__is_destructible_t<T>::value);

    using __base = __optional_base<T>;

  public:
    using value_type = T;

  private:
    template<typename U>
    using __converts_from_optional = __disjunction<__is_constructible_t<T, optional<U>&>,
                                                   __is_constructible_t<T, const optional<U>&>,
                                                   __is_constructible_t<T, optional<U>&&>,
                                                   __is_constructible_t<T, const optional<U>&&>,
                                                   __is_convertible_t<optional<U>&, T>,
                                                   __is_convertible_t<const optional<U>&, T>,
                                                   __is_convertible_t<optional<U>&&, T>,
                                                   __is_convertible_t<const optional<U>&&, T>>;

    template<typename U>
    using __assigns_from_optional =
        __disjunction<__is_assignable_t<T&, optional<U>&>, __is_assignable_t<T&, const optional<U>&>, __is_assignable_t<T&, optional<U>&&>, __is_assignable_t<T&, const optional<U>&&>>;

    template<typename U>
    using __non_explicit_convertible = typename __enable_if<__conjunction<__negation<__is_same_t<optional, typename __remove_cvref<U>::type>>,
                                                                          __negation<__is_same_t<in_place_t, typename __remove_cvref<U>::type>>,
                                                                          __is_constructible_t<T, U>,
                                                                          __is_convertible<U, T>>::value,
                                                            bool>::type;

    template<typename U>
    using __explicit_convertible = typename __enable_if<__conjunction<__negation<__is_same_t<optional, typename __remove_cvref<U>::type>>,
                                                                      __negation<__is_same_t<in_place_t, typename __remove_cvref<U>::type>>,
                                                                      __is_constructible_t<T, U>,
                                                                      __negation<__is_convertible<U, T>>>::value,
                                                        bool>::type;

    template<typename U>
    using __non_explicit_copy_convertible =
        typename __enable_if<__conjunction<__negation<__is_same_t<T, U>>, __is_constructible_t<T, const U&>, __is_convertible<const U&, T>, __negation<__converts_from_optional<U>>>, bool>::type;

    template<typename U>
    using __explicit_copy_convertible = typename __enable_if<
        __conjunction<__negation<__is_same_t<T, U>>, __is_constructible_t<T, const U&>, __negation<__is_convertible<const U&, T>>, __negation<__converts_from_optional<U>>>,
        bool>::type;

    template<typename U>
    using __non_explicit_move_convertible =
        typename __enable_if<__conjunction<__negation<__is_same_t<T, U>>, __is_constructible_t<T, U>, __is_convertible<U, T>, __negation<__converts_from_optional<U>>>, bool>::type;

    template<typename U>
    using __explicit_move_convertible =
        typename __enable_if<__conjunction<__negation<__is_same_t<T, U>>, __is_constructible_t<T, U>, __negation<__is_convertible<U, T>>, __negation<__converts_from_optional<U>>>, bool>::type;

    template<typename U>
    using __assignable = typename __enable_if<__conjunction<__negation<__is_same_t<T, U>>, __is_same<T, typename __decay<U>::type>, __is_constructible_t<T, U>, __is_assignable_t<T&, U>>,
                                              optional&>::type;

    template<typename U>
    using __copy_assignable = typename __enable_if<
        __conjunction<__negation<__is_same_t<T, U>>, __is_constructible_t<T, const U&>, __is_assignable_t<T, const U&>, __negation<__converts_from_optional<U>>, __negation<__assigns_from_optional<U>>>,
        optional&>::type;

    template<typename U>
    using __move_assignable = typename __enable_if<
        __conjunction<__negation<__is_same_t<T, U>>, __is_constructible_t<T, U>, __is_assignable_t<T&, U>, __negation<__converts_from_optional<U>>, __negation<__assigns_from_optional<U>>>,
        optional&>::type;

  public:
    constexpr optional() noexcept { }

    constexpr optional(nullopt_t) noexcept { }

    template<typename U = T, __non_explicit_convertible<U> = true>
    constexpr optional(U&& value) noexcept(__is_nothrow_constructible_t<T, U>::value): __base(in_place, forward<U>(value)) { }

    template<typename U = T, __explicit_convertible<U> = false>
    constexpr explicit optional(U&& value) noexcept(__is_nothrow_constructible_t<T, U>::value): __base(in_place, forward<U>(value)) { }

    template<typename U = T, __non_explicit_copy_convertible<U> = true>
    __constexpr_cxx_std_23 optional(const optional<U>& other) noexcept(__is_nothrow_constructible_t<T, const U&>::value) {
      if (other) {
        this->emplace(*other);
      }
    }

    template<typename U = T, __explicit_copy_convertible<U> = false>
    __constexpr_cxx_std_23 explicit optional(const optional<U>& other) noexcept(__is_nothrow_constructible_t<T, const U&>::value) {
      if (other) {
        this->emplace(*other);
      }
    }

    template<typename U = T, __non_explicit_move_convertible<U> = true>
    __constexpr_cxx_std_23 optional(optional<U>&& other) noexcept(__is_nothrow_constructible_t<T, U>::value) {
      if (other) {
        this->emplace(move(*other));
      }
    }

    template<typename U = T, __explicit_move_convertible<U> = false>
    __constexpr_cxx_std_23 explicit optional(optional<U>&& other) noexcept(__is_nothrow_constructible_t<T, U>::value) {
      if (other) {
        this->emplace(move(*other));
      }
    }

    template<typename... Args, typename __enable_if<__is_constructible_t<T, Args...>, nullptr_t>::type = nullptr>
    explicit constexpr optional(in_place_t, Args&&... args) noexcept(__is_nothrow_constructible_t<T, Args...>::value): __base(in_place, forward<Args>(args)...) { }

    template<typename U, typename... Args, typename __enable_if<__is_constructible_t<T, initializer_list<U>&, Args...>, nullptr_t>::type = nullptr>
    explicit constexpr optional(in_place_t, initializer_list<U> init_list, Args&&... args) noexcept(__is_nothrow_constructible_t<T, initializer_list<U>&, Args...>::value)
        : __base(in_place, init_list, forward<Args>(args)...) { }

    __constexpr_cxx_std_23 optional& operator=(nullopt_t) noexcept {
      __base::_storage.destroy();
      return *this;
    }

    template<typename U = T>
    __constexpr_cxx_std_23 __assignable<U> operator=(U&& value) noexcept(__conjunction<__is_nothrow_constructible_t<T, U>, __is_nothrow_assignable_t<T&, U>>::value) {
      if (this->has_value()) {
        __base::_storage.get() = forward<U>(value);
      } else {
        __base::_storage.construct(forward<U>(value));
      }

      return *this;
    }

    template<typename U = T>
    __constexpr_cxx_std_23 __copy_assignable<U> operator=(const optional<U>& other) noexcept(__conjunction<__is_nothrow_constructible_t<T, const U&>, __is_nothrow_assignable_t<T&, const U&>>::value) {
      if (this->has_value() && other.has_value()) {
        __base::_storage.get() = *other;
      } else if (this->has_value() && !other.has_value()) {
        __base::_storage.destroy();
      } else if (!this->has_value() && other.has_value()) {
        __base::_storage.construct(*other);
      }

      return *this;
    }

    template<typename U = T>
    __constexpr_cxx_std_23 __move_assignable<U> operator=(optional<U>&& other) noexcept(__conjunction<__is_nothrow_constructible_t<T, U>, __is_nothrow_assignable_t<T&, U>>::value) {
      if (this->has_value() && other.has_value()) {
        __base::_storage.get() = move(*other);
      } else if (this->has_value() && !other.has_value()) {
        __base::_storage.destroy();
      } else if (!this->has_value() && other.has_value()) {
        __base::_storage.construct(move(*other));
      }

      return *this;
    }

    template<typename... Args>
    __constexpr_cxx_std_23 typename __enable_if<__is_constructible_t<T, Args...>, T&>::type emplace(Args&&... args) noexcept(__is_nothrow_constructible_t<T, Args...>::value) {
      __base::_storage.destroy();
      __base::_storage.construct(forward<Args>(args)...);
      return __base::_storage.get();
    }

    template<typename U, typename... Args>
    __constexpr_cxx_std_23 typename __enable_if<__is_constructible_t<T, initializer_list<U>&, Args...>, T&>::type emplace(initializer_list<U> init_list, Args&&... args) noexcept(
        __is_nothrow_constructible_t<T, initializer_list<U>&, Args...>::value) {
      __base::_storage.destroy();
      __base::_storage.construct(init_list, forward<Args>(args)...);
      return __base::_storage.get();
    }

    __constexpr_cxx_std_23 void swap(optional& other) {
      using std::swap;

      if (this->has_value() && other.has_value()) {
        swap(__base::_storage.get(), other._storage.get());
      } else if (this->has_value() && !other.has_value()) {
        other._storage.construct(move(__base::_storage.get()));
        __base::_storage.destroy();
      } else if (!this->has_value() && other.has_value()) {
        __base::_storage.construct(move(other._storage.get()));
        other._storage.destroy();
      }
    }

    __constexpr_cxx_std_23 void reset() noexcept {
      __base::_storage.destroy();
    }

    constexpr constexpr const T* operator->() const noexcept {
      return __addressof(__base::_storage.get());
    }

    constexpr T* operator->() noexcept {
      return __addressof(__base::_storage.get());
    }

    constexpr constexpr const T& operator*() const& noexcept {
      return __base::_storage.get();
    }

    constexpr T& operator*() & noexcept {
      return __base::_storage.get();
    }

    constexpr constexpr const T&& operator*() const&& noexcept {
      return move(__base::_storage.get());
    }

    constexpr T&& operator*() && noexcept {
      return move(__base::_storage.get());
    }

    constexpr constexpr explicit operator bool() const noexcept {
      return this->has_value();
    }

    constexpr constexpr bool has_value() const noexcept {
      return __base::_storage._has_value;
    }

    constexpr constexpr const T& value() const& noexcept {
      if (!this->has_value()) {
        __throw(bad_optional_access());
      }

      return __base::_storage.get();
    }

    constexpr T& value() & noexcept {
      if (!this->has_value()) {
        __throw(bad_optional_access());
      }

      return __base::_storage.get();
    }

    constexpr constexpr const T&& value() const&& noexcept {
      if (!this->has_value()) {
        __throw(bad_optional_access());
      }

      return move(__base::_storage.get());
    }

    constexpr T&& value() && noexcept {
      if (!this->has_value()) {
        __throw(bad_optional_access());
      }

      return move(__base::_storage.get());
    }

    template<typename U>
    constexpr T value_or(U&& default_value) const& {
      static_assert(__is_copy_constructible<T>::value);
      static_assert(__is_convertible<U&&, T>::value);

      if (this->has_value()) {
        return __base::_storage.get();
      } else {
        return static_cast<T>(forward<U>(default_value));
      }
    }

    template<typename U>
    constexpr T value_or(U&& default_value) && {
      static_assert(__is_move_constructible<T>::value);
      static_assert(__is_convertible<U&&, T>::value);

      if (this->has_value()) {
        return move(__base::_storage.get());
      } else {
        return static_cast<T>(forward<U>(default_value));
      }
    }
  };

  template<typename T>
  __constexpr_cxx_std_23 inline typename __enable_if<__conjunction<__is_move_constructible<T>, __is_swappable<T>>::value>::type swap(optional<T>& lhs,
                                                                                                                                     optional<T>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
    lhs.swap(rhs);
  }

  template<typename T>
  typename __enable_if<__negation<__conjunction<__is_move_constructible<T>, __is_swappable<T>>>::value>::type swap(optional<T>&, optional<T>&) = delete;

  template<typename T>
  constexpr typename __enable_if<__is_constructible_t<typename __decay<T>::type, T>::value, optional<typename __decay<T>::type>>::type make_optional(T&& value) noexcept(
      __is_nothrow_constructible_t<optional<typename __decay<T>::type>, T>::value) {
    return optional<typename __decay<T>::type>(forward<T>(value));
  }

  template<typename T, typename... Args>
  constexpr typename __enable_if<__is_constructible_t<T, Args...>::value, optional<T>>::type make_optional(Args&&... args) noexcept(__is_nothrow_constructible_t<T, Args...>::value) {
    return optional<T>(in_place, forward<Args>(args)...);
  }

  template<typename T, typename U, typename... Args>
  constexpr typename __enable_if<__is_constructible_t<T, initializer_list<U>&, Args...>::value, optional<T>>::type make_optional(initializer_list<U> init_list, Args&&... args) noexcept(
      __is_nothrow_constructible_t<T, initializer_list<U>&, Args...>::value) {
    return optional<T>(in_place, init_list, forward<Args>(args)...);
  }

#if __cpp_deduction_guides

  template<typename T>
  optional(T) -> optional<T>;

#endif // __cpp_deduction_guides
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_OPTIONAL_OPTIONAL_H_
