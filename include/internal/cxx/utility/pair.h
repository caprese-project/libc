#ifndef CAPRESE_LIBC_INTERNAL_CXX_UTILITY_PAIR_H_
#define CAPRESE_LIBC_INTERNAL_CXX_UTILITY_PAIR_H_

#include <internal/attribute.h>
#include <internal/cxx/type_traits/detection.h>
#include <internal/cxx/type_traits/type.h>
#include <internal/cxx/utility/fwd.h>
#include <internal/cxx/utility/swap.h>

namespace std {
  template<typename T, typename U>
  struct pair {
    T first;
    U second;

    template<typename V = T, typename W = U, typename = typename __enable_if<__is_default_constructible<V>::value>::type, typename = typename __enable_if<__is_default_constructible<W>::value>::type>
    explicit __constexpr_cxx_std_11 pair(): first {},
                                            second {} { }

    pair(const pair&) = default;
    pair(pair&&)      = default;

    template<typename V = T, typename W = U, typename = typename __enable_if<__is_copy_constructible<V>::value>::type, typename = typename __enable_if<__is_copy_constructible<W>::value>::type>
    explicit __constexpr_cxx_std_14 pair(const V& first, const W& second): first(first),
                                                                           second(second) { }

    template<typename V, typename W, typename = typename __enable_if<__is_constructible_t<T, V&&>::value>::type, typename = typename __enable_if<__is_constructible_t<U, W&&>::value>::type>
    explicit __constexpr_cxx_std_14 pair(V&& first, W&& second): first(forward<V>(first)),
                                                                 second(forward<W>(second)) { }

    template<typename V, typename W, typename = typename __enable_if<__is_constructible_t<T, const V&>::value>::type, typename = typename __enable_if<__is_constructible_t<U, const W&>::value>::type>
    explicit __constexpr_cxx_std_14 pair(const pair<V, W>& other): first(other.first),
                                                                   second(other.second) { }

    template<typename V, typename W, typename = typename __enable_if<__is_constructible_t<T, V&&>::value>::type, typename = typename __enable_if<__is_constructible_t<U, W&&>::value>::type>
    explicit __constexpr_cxx_std_14 pair(pair<V, W>&& other): first(move(other.first)),
                                                              second(move(other.second)) { }

    __constexpr_cxx_std_20 pair& operator=(const pair& other) {
      first  = other.first;
      second = other.second;
      return *this;
    }

    template<typename V, typename W>
    __constexpr_cxx_std_20 pair& operator=(const pair<V, W>& other) {
      first  = other.first;
      second = other.second;
      return *this;
    }

    __constexpr_cxx_std_20 pair& operator=(pair&& other) __noexcept {
      first  = move(other.first);
      second = move(other.second);
      return *this;
    }

    template<typename V, typename W>
    __constexpr_cxx_std_20 pair& operator=(pair<V, W>&& other) __noexcept {
      first  = move(other.first);
      second = move(other.second);
      return *this;
    }

    __constexpr_cxx_std_20 void swap(pair& other) __noexcept {
      using std::swap;
      swap(first, other.first);
      swap(second, other.second);
    }
  };

  template<typename T, typename U>
  __constexpr_cxx_std_14 bool operator==(const pair<T, U>& lhs, const pair<T, U>& rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
  }

  template<typename T, typename U>
  __constexpr_cxx_std_14 bool operator!=(const pair<T, U>& lhs, const pair<T, U>& rhs) {
    return !(lhs == rhs);
  }

  template<typename T, typename U>
  __constexpr_cxx_std_14 bool operator<(const pair<T, U>& lhs, const pair<T, U>& rhs) {
    return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
  }

  template<typename T, typename U>
  __constexpr_cxx_std_14 bool operator<=(const pair<T, U>& lhs, const pair<T, U>& rhs) {
    return !(rhs < lhs);
  }

  template<typename T, typename U>
  __constexpr_cxx_std_14 bool operator>(const pair<T, U>& lhs, const pair<T, U>& rhs) {
    return rhs < lhs;
  }

  template<typename T, typename U>
  __constexpr_cxx_std_14 bool operator>=(const pair<T, U>& lhs, const pair<T, U>& rhs) {
    return !(lhs < rhs);
  }

  template<typename T, typename U>
  __constexpr_cxx_std_20 void swap(pair<T, U>& lhs, pair<T, U>& rhs) __noexcept {
    lhs.swap(rhs);
  }

#if __cpp_deduction_guides
  template<typename T, typename U>
  pair(T, U) -> pair<T, U>;
#endif // __cpp_deduction_guides
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_UTILITY_PAIR_H_
