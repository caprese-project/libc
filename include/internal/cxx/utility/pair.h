#ifndef CAPRESE_LIBC_INTERNAL_CXX_UTILITY_PAIR_H_
#define CAPRESE_LIBC_INTERNAL_CXX_UTILITY_PAIR_H_

#include <internal/attribute.h>
#include <internal/cxx/utility/fwd.h>

namespace std {
  template<typename T, typename U>
  struct pair {
    T first;
    U second;

    explicit __constexpr_cxx_std_11 pair(): first {}, second {} { }

    pair(const pair&) = default;
    pair(pair&&)      = default;

    explicit __constexpr_cxx_std_14 pair(const T& first, const U& second): first(first), second(second) { }

    template<typename V, typename W>
    explicit __constexpr_cxx_std_14 pair(V&& first, W&& second): first(forward<V>(first)),
                                                                 second(forward<V>(second)) { }

    template<typename V, typename W>
    explicit __constexpr_cxx_std_14 pair(const pair<V, W>& other): first(other.first),
                                                                   second(other.second) { }

    template<typename V, typename W>
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
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_UTILITY_PAIR_H_
