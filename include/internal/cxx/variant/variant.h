#ifndef CAPRESE_LIBC_INTERNAL_CXX_VARIANT_VARIANT_H_
#define CAPRESE_LIBC_INTERNAL_CXX_VARIANT_VARIANT_H_

#include <initializer_list>
#include <internal/branch.h>
#include <internal/cxx/limits/numeric_limits.h>
#include <internal/cxx/stddef.h>
#include <internal/cxx/stl_base/lazy.h>
#include <internal/cxx/type_traits/characteristic.h>
#include <internal/cxx/type_traits/detection.h>
#include <internal/cxx/type_traits/logic.h>
#include <internal/cxx/type_traits/modify.h>
#include <internal/cxx/type_traits/type_relation.h>
#include <internal/cxx/utility/in_place_index.h>
#include <internal/cxx/variant/bad_variant_access.h>
#include <internal/cxx/variant/variant_alternative.h>
#include <internal/exception.h>

namespace std {
  inline constexpr __size_t variant_npos = -1;

  template<typename T, typename... Tn>
  struct __variant_storage {
    using value_type = __lazy<typename __remove_const<T>::type>;

    union {
      __lazy<typename __remove_const<T>::type> _value;
      __variant_storage<Tn...>                 _next;
    };

    template<typename... Args>
    constexpr explicit __variant_storage(__integral_constant<__size_t, 0>, Args&&... args): _value(forward<Args>(args)...) { }

    template<__size_t I, typename... Args, typename __enable_if<(I > 0), nullptr_t> = nullptr>
    constexpr explicit __variant_storage(__integral_constant<__size_t, I>, Args&&... args): _next(__integral_constant<__size_t, I - 1>(), forward<Args>(args)...) { }

    constexpr T& __get() & noexcept {
      return _value.get();
    }

    constexpr const T& __get() const& noexcept {
      return _value.get();
    }

    constexpr T&& __get() && noexcept {
      return move(_value.get());
    }

    constexpr const T&& __get() const&& noexcept {
      return move(_value.get());
    }

    constexpr value_type& __raw() & noexcept {
      return _value;
    }

    constexpr const value_type& __raw() const& noexcept {
      return _value;
    }

    constexpr value_type&& __raw() && noexcept {
      return move(_value);
    }

    constexpr const value_type&& __raw() const&& noexcept {
      return move(_value);
    }
  };

  template<typename... Types>
  using __variant_index = typename __conditional<(sizeof...(Types) < static_cast<__size_t>(__numeric_limits<signed char>::max())),
                                                 signed char,
                                                 typename __conditional<(sizeof...(Types) < static_cast<__size_t>(__numeric_limits<signed short>::max())), signed short, signed int>::type>::type;

  template<__size_t I, __size_t Max, typename Target, typename T, typename... Tn>
  struct __variant_find_type_helper: public __conditional<__is_same_t<Target, T>::value, __variant_find_type_helper<I, Max, Target>, __variant_find_type_helper<I + 1, Max, Target, Tn...>> { };

  template<__size_t I, __size_t Max, typename Target>
  struct __variant_find_type_helper<I, Max, Target, void> {
    using type                      = Target;
    static constexpr __size_t value = I > Max ? variant_npos : I;
  };

  template<typename Target, typename... Types>
  struct __variant_find_type: public __variant_find_type_helper<0, sizeof...(Types), Target, Types...> { };

  template<typename... Types>
  class __variant_base: public __variant_storage<Types...> {
    using __storage_type = typename __variant_storage<Types...>;
    using __index_type   = typename __variant_index<Types...>;

  private:
    __index_type _index;

  public:
    constexpr __variant_base(): _index(variant_npos) { }

    template<__size_t I, typename... Args, __enable_if<__is_constructible_t<typename variant_alternative<I, variant<Types...>>::type, Args...>::value, nullptr_t> = nullptr>
    constexpr explicit __variant_base(in_place_index_t<I>, Args&&... args) noexcept(noexcept(__is_nothrow_constructible_t<typename variant_alternative<I, variant<Types...>>::type, Args...>::value))
        : __storage_type(__integral_constant<__size_t, I>(), forward<Args>(args)...),
          _index(static_cast<__index_type>(I)) { }

    constexpr bool valueless_by_exception() const noexcept {
      return _index == variant_npos;
    }
  };

  template<typename... Types>
  class variant: public __variant_base<Types...> {
    static_assert(sizeof...(Types) > 0, "Types must not be empty");
    static_assert(__is_destructible_t<Types>::value && ..., "Types must be destructible");

    using __base_type    = typename __variant_base<Types...>;
    using __first_type   = typename variant_alternative<0, variant>::type;
    using __storage_type = typename __base_type::__storage_type;
    using __index_type   = typename __base_type::__index_type;

  public:
    using __base_type::__base_type;

    template<typename T = __first_type, typename __enable_if<__is_default_constructible<T>::value, nullptr_t> = nullptr>
    constexpr variant() noexcept(noexcept(__is_nothrow_default_constructible<T>::value)): __base_type(in_place_index<0>) { }

    template<typename T, typename __enable_if<, nullptr_t> = nullptr>
    constexpr variant(T&& other) noexcept(noexcept(__is_nothrow_constructible_t<typename __variant_find_type<T, Types...>::type, T>::value))
        : __base_type(in_place_index<__variant_find_type<T, Types...>::value>, forward<T>(other)) { }

    template<typename T,
             typename __enable_if<!__is_same_t<typename __remove_cvref<T>, variant>::value && __is_constructible_t<typename __variant_find_type<T, Types...>::type, T>::value
                                      && __is_assignable_t<typename __variant_find_type<T, Types...>::type, T>::value,
                                  nullptr_t> = nullptr>
    constexpr variant& operator=(T&& other) noexcept(
        noexcept(__is_nothrow_assignable_t<typename __variant_find_type<T, Types...>::type&, T>::value&& __is_nothrow_assignable_t<typename __variant_find_type<T, Types...>::type&, T>)) {
      constexpr __size_t idx = __variant_find_type<T, Types...>::value;
      if (this->index() == idx) {
        this->__get() = forward<T>(other);
      } else {
        this->template emplace<idx>(forward<T>(other));
      }
    }

    template<typename T, typename... Args, __size_t I = __variant_find_type<T, Types...>::value, __enable_if<I != variant_npos && __is_constructible_t<T, Args...>::value, nullptr_t> = nullptr>
    constexpr T& emplace(Args&&... args) noexcept(__is_nothrow_constructible_t<T, Args...>::value) {
      this->template __emplace<I>(forward<Args>(args)...);
      return this->__get();
    }

    template<typename T, typename... Args, __size_t I = __variant_find_type<T, Types...>::value, __enable_if<I != variant_npos && __is_constructible_t<T, Args...>::value, nullptr_t> = nullptr>
    constexpr T& emplace(initializer_list<Args...> init_list) noexcept(__is_nothrow_constructible_t<T, initializer_list<Args...>>::value) {
      this->template __emplace<I>(init_list);
      return this->__get();
    }

    template<__size_t I, typename... Args, __enable_if<__is_constructible_t<typename variant_alternative<I, variant<Types...>>::type, Args...>::value, nullptr_t> = nullptr>
    constexpr typename variant_alternative<I, variant<Types...>>::type& emplace(Args&&... args) noexcept(
        __is_nothrow_constructible_t<typename variant_alternative<I, variant<Types...>>::type, Args...>::value) {
      this->template __emplace<I>(forward<Args>(args)...);
      return this->__get();
    }

    template<__size_t I, typename... Args, __enable_if<__is_constructible_t<typename variant_alternative<I, variant<Types...>>::type, initializer_list<Args...>>::value, nullptr_t> = nullptr>
    constexpr typename variant_alternative<I, variant<Types...>>::type& emplace(initializer_list<Args...> init_list) noexcept(
        __is_nothrow_constructible_t<typename variant_alternative<I, variant<Types...>>::type, initializer_list<Args...>>::value) {
      this->template __emplace<I>(init_list);
      return this->__get();
    }

    constexpr __size_t index() const noexcept {
      __if_unlikely (this->valueless_by_exception()) {
        return variant_npos;
      }
      return static_cast<__size_t>(this->_index);
    }

  private:
    template<__size_t I, typename... Args>
    constexpr void __emplace(Args&&... args) noexcept(__is_nothrow_constructible_t<typename variant_alternative<I, variant<Types...>>::type, Args...>::value) {
      this->__raw().construct(forward<Args>(args)...);
      this->_index = static_cast<__index_type>(I);
    }
  };

  template<__size_t I, typename... Types>
  constexpr typename variant_alternative<I, variant<Types...>>::type& get(variant<Types...>& v) {
    if (v.index() != I) {
      __throw_exception(bad_variant_access());
    }
    return v.__get();
  }

  template<__size_t I, typename... Types>
  constexpr const typename variant_alternative<I, variant<Types...>>::type& get(const variant<Types...>& v) {
    if (v.index() != I) {
      __throw_exception(bad_variant_access());
    }
    return v.__get();
  }

  template<__size_t I, typename... Types>
  constexpr typename variant_alternative<I, variant<Types...>>::type&& get(variant<Types...>&& v) {
    if (v.index() != I) {
      __throw_exception(bad_variant_access());
    }
    return move(v.__get());
  }

  template<__size_t I, typename... Types>
  constexpr const typename variant_alternative<I, variant<Types...>>::type&& get(const variant<Types...>&& v) {
    if (v.index() != I) {
      __throw_exception(bad_variant_access());
    }
    return move(v.__get());
  }

  template<typename T, typename... Types>
  constexpr T& get(variant<Types...>& v) {
    constexpr __size_t idx = __variant_find_type<T, Types...>::value;
    if (v.index() != idx) {
      __throw_exception(bad_variant_access());
    }
    return v.__get();
  }

  template<typename T, typename... Types>
  constexpr const T& get(const variant<Types...>& v) {
    constexpr __size_t idx = __variant_find_type<T, Types...>::value;
    if (v.index() != idx) {
      __throw_exception(bad_variant_access());
    }
    return v.__get();
  }

  template<typename T, typename... Types>
  constexpr T&& get(variant<Types...>&& v) {
    constexpr __size_t idx = __variant_find_type<T, Types...>::value;
    if (v.index() != idx) {
      __throw_exception(bad_variant_access());
    }
    return move(v.__get());
  }

  template<typename T, typename... Types>
  constexpr const T&& get(const variant<Types...>&& v) {
    constexpr __size_t idx = __variant_find_type<T, Types...>::value;
    if (v.index() != idx) {
      __throw_exception(bad_variant_access());
    }
    return move(v.__get());
  }

  template<typename T, typename... Types>
  constexpr bool holds_alternative(const variant<Types...>& v) noexcept {
    return v.index() == __variant_find_type<T, Types...>::value;
  }

  template<typename... Types>
  constexpr bool operator==(const variant<Types...>& lhs, const variant<Types...>& rhs) {
    if (lhs.index() != rhs.index()) {
      return false;
    }
    if (lhs.valueless_by_exception()) {
      return true;
    }
    return lhs.__get() == rhs.__get();
  }

  template<typename... Types>
  constexpr bool operator!=(const variant<Types...>& lhs, const variant<Types...>& rhs) {
    return !(lhs == rhs);
  }

  template<typename... Types>
  constexpr bool operator<(const variant<Types...>& lhs, const variant<Types...>& rhs) {
    if (rhs.valueless_by_exception()) {
      return false;
    }
    if (lhs.valueless_by_exception()) {
      return true;
    }
    if (lhs.index() < rhs.index()) {
      return true;
    }
    if (lhs.index() > rhs.index()) {
      return false;
    }
    return lhs.__get() < rhs.__get();
  }

  template<typename... Types>
  constexpr bool operator<=(const variant<Types...>& lhs, const variant<Types...>& rhs) {
    return !(rhs < lhs);
  }

  template<typename... Types>
  constexpr bool operator>(const variant<Types...>& lhs, const variant<Types...>& rhs) {
    return rhs < lhs;
  }

  template<typename... Types>
  constexpr bool operator>=(const variant<Types...>& lhs, const variant<Types...>& rhs) {
    return !(lhs < rhs);
  }
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_VARIANT_VARIANT_H_
