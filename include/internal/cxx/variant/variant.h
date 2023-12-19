#ifndef CAPRESE_LIBC_INTERNAL_CXX_VARIANT_VARIANT_H_
#define CAPRESE_LIBC_INTERNAL_CXX_VARIANT_VARIANT_H_

#include <initializer_list>
#include <internal/branch.h>
#include <internal/cxx/limits/numeric_limits.h>
#include <internal/cxx/memory/uninit.h>
#include <internal/cxx/stddef.h>
#include <internal/cxx/type_traits/characteristic.h>
#include <internal/cxx/type_traits/detection.h>
#include <internal/cxx/type_traits/logic.h>
#include <internal/cxx/type_traits/modify.h>
#include <internal/cxx/type_traits/type_relation.h>
#include <internal/cxx/utility/in_place_index.h>
#include <internal/cxx/utility/sequence.h>
#include <internal/cxx/variant/bad_variant_access.h>
#include <internal/cxx/variant/variant_alternative.h>
#include <internal/cxx/variant/variant_size.h>
#include <internal/exception.h>

namespace std {
  inline constexpr __size_t variant_npos = -1;

  template<__size_t I, typename... Types>
  constexpr variant_alternative_t<I, variant<Types...>>& get(variant<Types...>& var);

  template<__size_t I, typename... Types>
  constexpr variant_alternative_t<I, variant<Types...>>&& get(variant<Types...>&& var);

  template<__size_t I, typename... Types>
  constexpr const variant_alternative_t<I, variant<Types...>>& get(const variant<Types...>& var);

  template<__size_t I, typename... Types>
  constexpr const variant_alternative_t<I, variant<Types...>>&& get(const variant<Types...>&& var);

  template<typename T, typename... Types>
  constexpr T& get(variant<Types...>& var);

  template<typename T, typename... Types>
  constexpr T&& get(variant<Types...>&& var);

  template<typename T, typename... Types>
  constexpr const T& get(const variant<Types...>& var);

  template<typename T, typename... Types>
  constexpr const T&& get(const variant<Types...>&& var);

  template<typename... Types>
  union __variant_storage;

  template<typename T>
  union __variant_storage<T> {
    alignas(T) char _value[sizeof(T)];

    constexpr __variant_storage() = default;

    constexpr __variant_storage(const __variant_storage& other): _value(other._value.get()) { }

    constexpr __variant_storage(__variant_storage&& other): _value(move(other._value).get()) { }

    template<typename... Args>
    constexpr explicit __variant_storage(Args&&... args): _value(forward<Args>(args)...) { }
  };

  template<typename T, typename U, typename... Tn>
  union __variant_storage<T, U, Tn...> {
    using next_type = __variant_storage<U, Tn...>;

    alignas(T) char _value[sizeof(T)];
    next_type _next;

    constexpr __variant_storage() = default;

    constexpr __variant_storage(const __variant_storage& other): _value(other._value.get()) { }

    constexpr __variant_storage(__variant_storage&& other): _value(move(other._value).get()) { }

    template<typename... Args>
    constexpr explicit __variant_storage(Args&&... args): _value(forward<Args>(args)...) { }
  };

  class __variant_vtable {
    template<typename Visitor, typename Variant>
    using __visitor_result_type = decltype(__declval<Visitor>()(__declval<variant_alternative_t<0, typename __remove_cvref<Variant>::type>>()));

    template<typename Visitor, typename Variant, typename T>
    constexpr static auto __func() -> __visitor_result_type<Visitor, Variant> (*)(Visitor&&, void*) {
      return [](Visitor&& visitor, void* storage) {
        return forward<Visitor>(visitor)(*static_cast<T*>(storage));
      };
    }

    template<typename Visitor, typename Variant>
    using __visitor_func_type = __visitor_result_type<Visitor, Variant> (*)(Visitor&&, void*);

    template<typename Visitor, typename Variant, typename... Types>
    static constexpr __visitor_func_type<Visitor, Variant> __vtable[] = { __func<Visitor, Variant, Types>()... };

  public:
    template<typename Visitor, typename Variant, typename... Types>
    static auto __visit(Visitor&& visitor, Variant&& variant) -> __visitor_result_type<Visitor, Variant> {
      return __vtable<Visitor, Variant, Types...>[variant.index()](forward<Visitor>(visitor), reinterpret_cast<void*>(&variant._storage));
    }

    template<typename Visitor, typename Variant, typename... Types>
    static auto __visit_index(__size_t index, Visitor&& visitor, Variant&& variant) -> __visitor_result_type<Visitor, Variant> {
      return __vtable<Visitor, Variant, Types...>[index](forward<Visitor>(visitor), reinterpret_cast<void*>(&variant._storage));
    }
  };

  template<typename... Types>
  using __variant_index = typename __conditional<(sizeof...(Types) < static_cast<__size_t>(__numeric_limits<signed char>::max())),
                                                 signed char,
                                                 typename __conditional<(sizeof...(Types) < static_cast<__size_t>(__numeric_limits<signed short>::max())), signed short, signed int>::type>::type;

  template<typename... Types>
  class variant {
    static_assert(sizeof...(Types) > 0, "Variant must have at least one type");

    friend class __variant_vtable;

    using __storage_type = __variant_storage<Types...>;
    using __index_type   = __variant_index<Types...>;

    template<__size_t I>
    using __nth_type = typename variant_alternative<I, variant>::type;

    using __copy_constructible         = __conjunction<__is_copy_constructible<Types>...>;
    using __move_constructible         = __conjunction<__is_move_constructible<Types>...>;
    using __nothrow_move_constructible = __conjunction<__is_nothrow_move_constructible<Types>...>;
    using __move_assignable            = __conjunction<__move_constructible, __is_move_assignable<Types>...>;
    using __nothrow_move_assignable    = __conjunction<__nothrow_move_constructible, __is_nothrow_move_assignable<Types>...>;

  private:
    __index_type   _index;
    __storage_type _storage;

  private:
    template<__size_t I>
    constexpr __nth_type<I>& __unsafe_get() & {
      return *reinterpret_cast<__nth_type<I>*>(&_storage);
    }

    template<__size_t I>
    constexpr __nth_type<I>&& __unsafe_get() && {
      return move(*reinterpret_cast<__nth_type<I>*>(&_storage));
    }

    template<__size_t I>
    constexpr const __nth_type<I>& __unsafe_get() const& {
      return *reinterpret_cast<const __nth_type<I>*>(&_storage);
    }

    template<__size_t I>
    constexpr const __nth_type<I>&& __unsafe_get() const&& {
      return move(*reinterpret_cast<const __nth_type<I>*>(&_storage));
    }

    template<__size_t I>
    constexpr __nth_type<I>& __get() & {
      static_assert(I < sizeof...(Types));

      if (_index != I) {
        __throw_exception(bad_variant_access());
      }

      return this->template __unsafe_get<I>();
    }

    template<__size_t I>
    constexpr __nth_type<I>&& __get() && {
      static_assert(I < sizeof...(Types));

      if (_index != I) {
        __throw_exception(bad_variant_access());
      }

      return this->template __unsafe_get<I>();
    }

    template<__size_t I>
    constexpr const __nth_type<I>& __get() const& {
      static_assert(I < sizeof...(Types));

      if (_index != I) {
        __throw_exception(bad_variant_access());
      }

      return this->template __unsafe_get<I>();
    }

    template<__size_t I>
    constexpr const __nth_type<I>&& __get() const&& {
      static_assert(I < sizeof...(Types));

      if (_index != I) {
        __throw_exception(bad_variant_access());
      }

      return this->template __unsafe_get<I>();
    }

    template<typename Visitor>
    auto __visit(Visitor&& visitor) {
      return __variant_vtable::__visit<Visitor, variant&, Types...>(forward<Visitor>(visitor), *this);
    }

    template<typename Visitor>
    auto __visit(Visitor&& visitor) const {
      return __variant_vtable::__visit<Visitor, const variant&, Types...>(forward<Visitor>(visitor), *this);
    }

    template<typename Visitor>
    auto __visit_index(__size_t index, Visitor&& visitor) {
      return __variant_vtable::__visit_index<Visitor, variant&, Types...>(index, forward<Visitor>(visitor), *this);
    }

    template<typename Visitor>
    auto __visit_index(__size_t index, Visitor&& visitor) const {
      return __variant_vtable::__visit_index<Visitor, const variant&, Types...>(index, forward<Visitor>(visitor), *this);
    }

    template<__size_t I, typename T, typename Ti, typename = void>
    struct __find_index_helper_helper {
      void __func(); // undefined
    };

    template<typename Ti>
    struct __array {
      Ti __data[1];
    };

    template<__size_t I, typename T, typename Ti>
    struct __find_index_helper_helper<I, T, Ti, __void_t<decltype(__array<Ti> { { __declval<T>() } })>> {
      static __integral_constant<__size_t, I> __func(Ti); // undefined
    };

    template<typename Variant, typename T, typename = __make_index_sequence<variant_size_v<Variant>>>
    struct __find_index_helper;

    template<typename T, typename... Ti, __size_t... I>
    struct __find_index_helper<variant<Ti...>, T, __index_sequence<I...>>: __find_index_helper_helper<I, T, Ti>... {
      using __find_index_helper_helper<I, T, Ti>::__func...;
    };

    template<typename Variant, typename T>
    using __find_index_type = decltype(__find_index_helper<Variant, T>::__func(__declval<T>()));

    template<typename Variant, typename T, typename = void>
    struct __find_index: __integral_constant<__size_t, variant_npos> { };

    template<typename Variant, typename T>
    struct __find_index<Variant, T, __void_t<__find_index_type<Variant, T>>>: __find_index_type<Variant, T> { };

    template<typename Variant, typename T, typename = void>
    struct __find_constructible_type { };

    template<typename Variant, typename T>
    struct __find_constructible_type<Variant, T, __void_t<__find_index_type<Variant, T>>> {
      using type = typename variant_alternative<__find_index<Variant, T>::value, Variant>::type;
    };

  public:
    template<typename T = __nth_type<0>, typename __enable_if<__is_default_constructible<T>::value, nullptr_t>::type = nullptr>
    constexpr variant() noexcept(__is_nothrow_default_constructible<__nth_type<0>>::value): _index(static_cast<__index_type>(variant_npos)),
                                                                                            _storage() {
      __construct_at(&this->template __unsafe_get<0>());
      _index = 0;
    }

    template<typename Variant = variant, typename __enable_if<__is_same_t<Variant, variant>::value && __copy_constructible::value, nullptr_t>::type = nullptr>
    constexpr variant(const Variant& other): _index(static_cast<__index_type>(variant_npos)) {
      if (!other.valueless_by_exception()) {
        other.__visit_index(other.index(), [this](const auto& value) { __construct_at(reinterpret_cast<typename __remove_cvref<decltype(value)>::type*>(&_storage), value); });
        _index = other._index;
      }
    }

    template<typename Variant = variant, typename __enable_if<__is_same_t<Variant, variant>::value && __move_constructible::value, nullptr_t>::type = nullptr>
    constexpr variant(Variant&& other) noexcept(__nothrow_move_constructible::value): _index(static_cast<__index_type>(variant_npos)) {
      if (!other.valueless_by_exception()) {
        other.__visit_index(other.index(), [this](auto&& value) { __construct_at(reinterpret_cast<typename __remove_cvref<decltype(value)>::type*>(&_storage), move(value)); });
        _index = other._index;
      }
    }

    template<typename T, typename Tj = typename __find_constructible_type<variant, T>::type, typename __enable_if<__is_constructible_t<Tj, T>::value, nullptr_t>::type = nullptr>
    constexpr variant(T&& t) noexcept(__is_nothrow_constructible_t<Tj, T>::value): variant(in_place_index<__find_index<variant, Tj>::value>, forward<T>(t)) { }

    template<__size_t I, typename __enable_if<(I < sizeof...(Types)), nullptr_t>::type = nullptr, typename... Args>
    constexpr explicit variant(in_place_index_t<I>, Args&&... args): _index(variant_npos),
                                                                     _storage(__integral_constant<__size_t, I>(), forward<Args>(args)...) {
      static_assert(__is_constructible_t<__nth_type<I>, Args...>::value, "Invalid arguments for variant constructor");
      _index = I;
    }

    __constexpr_cxx_std_23 ~variant() {
      if (!valueless_by_exception()) {
        __size_t old_index = this->index();
        _index             = static_cast<__index_type>(variant_npos);
        this->__visit_index(old_index, [this](auto&& value) { __destroy_at(reinterpret_cast<typename __remove_cvref<decltype(value)>::type*>(&_storage)); });
      }
    }

    constexpr variant& operator=(const variant& other) {
      _index = static_cast<__index_type>(variant_npos);

      if (valueless_by_exception()) [[unlikely]] {
        if (!other.valueless_by_exception()) {
          other.__visit_index(other.index(), [this](const auto& value) { __construct_at(reinterpret_cast<typename __remove_cvref<decltype(value)>::type*>(&_storage), value); });
          _index = other._index;
        }
        return *this;
      }

      if (_index == other._index) {
        other.__visit_index(other.index(), [this](const auto& value) { *reinterpret_cast<typename __remove_cvref<decltype(value)>::type*>(&_storage) = value; });
      } else {
        this->~variant();
        other.__visit_index(other.index(), [this](const auto& value) { __construct_at(reinterpret_cast<typename __remove_cvref<decltype(value)>::type*>(&_storage), value); });
        _index = other._index;
      }

      return *this;
    }

    template<typename Variant, typename __enable_if<__is_same_t<Variant, variant>::value && __move_assignable::value, nullptr_t>::type = nullptr>
    constexpr variant& operator=(Variant&& other) noexcept(__nothrow_move_assignable::value) {
      if (valueless_by_exception()) [[unlikely]] {
        if (!other.valueless_by_exception()) {
          other.__visit_index(other._index, [this](auto&& value) { __construct_at(reinterpret_cast<typename __remove_cvref<decltype(value)>::type*>(&_storage), move(value)); });
          _index = other._index;
        }
        return *this;
      }

      if (_index == other._index) {
        other.__visit_index(other._index, [this](auto&& value) { *reinterpret_cast<typename __remove_cvref<decltype(value)>::type*>(&_storage) = move(value); });
      } else {
        this->~variant();
        other.__visit_index(other._index, [this](auto&& value) { __construct_at(reinterpret_cast<typename __remove_cvref<decltype(value)>::type*>(&_storage), move(value)); });
        _index = other._index;
      }

      return *this;
    }

    template<typename T, typename Tj = typename __find_constructible_type<variant, T>::type, typename __enable_if<__is_assignable_t<Tj&, T>::value, nullptr_t>::type = nullptr>
    constexpr variant& operator=(T&& t) noexcept(__is_nothrow_assignable_t<Tj&, T>::value) {
      constexpr __size_t index = __find_index<variant, Tj>::value;
      static_assert(index != variant_npos, "Invalid type for variant");

      if (valueless_by_exception()) [[unlikely]] {
        __construct_at(reinterpret_cast<Tj*>(&_storage), forward<T>(t));
        _index = index;
        return *this;
      }

      if (_index == index) {
        *reinterpret_cast<Tj*>(&_storage) = forward<T>(t);
      } else {
        this->~variant();
        __construct_at(reinterpret_cast<Tj*>(&_storage), forward<T>(t));
        _index = index;
      }

      return *this;
    }

    constexpr bool valueless_by_exception() const noexcept {
      return static_cast<decltype(variant_npos)>(_index) == variant_npos;
    }

    constexpr __size_t index() const noexcept {
      return static_cast<__size_t>(_index);
    }

  private:
    template<__size_t I, typename... Tn>
    friend constexpr variant_alternative_t<I, variant<Tn...>>& get(variant<Tn...>&);

    template<__size_t I, typename... Tn>
    friend constexpr variant_alternative_t<I, variant<Tn...>>&& get(variant<Tn...>&&);

    template<__size_t I, typename... Tn>
    friend constexpr const variant_alternative_t<I, variant<Tn...>>& get(const variant<Tn...>&);

    template<__size_t I, typename... Tn>
    friend constexpr const variant_alternative_t<I, variant<Tn...>>&& get(const variant<Tn...>&&);

    template<typename T, typename... Tn>
    friend constexpr T& get(variant<Tn...>&);

    template<typename T, typename... Tn>
    friend constexpr T&& get(variant<Tn...>&&);

    template<typename T, typename... Tn>
    friend constexpr const T& get(const variant<Tn...>&);

    template<typename T, typename... Tn>
    friend constexpr const T&& get(const variant<Tn...>&&);

    template<typename T, typename... Tn>
    friend constexpr bool holds_alternative(const variant<Tn...>&) noexcept;
  };

  template<__size_t I, typename... Types>
  constexpr variant_alternative_t<I, variant<Types...>>& get(variant<Types...>& var) {
    static_assert(I < sizeof...(Types), "Invalid index for variant");
    return var.template __get<I>();
  }

  template<__size_t I, typename... Types>
  constexpr variant_alternative_t<I, variant<Types...>>&& get(variant<Types...>&& var) {
    static_assert(I < sizeof...(Types), "Invalid index for variant");
    return move(var).template __get<I>();
  }

  template<__size_t I, typename... Types>
  constexpr const variant_alternative_t<I, variant<Types...>>& get(const variant<Types...>& var) {
    static_assert(I < sizeof...(Types), "Invalid index for variant");
    return var.template __get<I>();
  }

  template<__size_t I, typename... Types>
  constexpr const variant_alternative_t<I, variant<Types...>>&& get(const variant<Types...>&& var) {
    static_assert(I < sizeof...(Types), "Invalid index for variant");
    return move(var).template __get<I>();
  }

  template<typename T, typename... Types>
  constexpr T& get(variant<Types...>& var) {
    constexpr __size_t index = variant<Types...>::template __find_index<variant<Types...>, T>::value;
    static_assert(index != variant_npos, "Invalid type for variant");
    return get<index>(var);
  }

  template<typename T, typename... Types>
  constexpr T&& get(variant<Types...>&& var) {
    constexpr __size_t index = variant<Types...>::template __find_index<variant<Types...>, T>::value;
    static_assert(index != variant_npos, "Invalid type for variant");
    return move(var).template __get<index>(move(var));
  }

  template<typename T, typename... Types>
  constexpr const T& get(const variant<Types...>& var) {
    constexpr __size_t index = variant<Types...>::template __find_index<variant<Types...>, T>::value;
    static_assert(index != variant_npos, "Invalid type for variant");
    return get<index>(var);
  }

  template<typename T, typename... Types>
  constexpr const T&& get(const variant<Types...>&& var) {
    constexpr __size_t index = variant<Types...>::template __find_index<variant<Types...>, T>::value;
    static_assert(index != variant_npos, "Invalid type for variant");
    return move(var).template __get<index>(move(var));
  }

  template<typename T, typename... Types>
  constexpr bool holds_alternative(const variant<Types...>& var) noexcept {
    constexpr __size_t index = variant<Types...>::template __find_index<variant<Types...>, T>::value;
    static_assert(index != variant_npos, "Invalid type for variant");
    return !var.valueless_by_exception() && var._index == index;
  }
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_VARIANT_VARIANT_H_
