#ifndef CAPRESE_LIBC_INTERNAL_CXX_ITERATOR_FUNCTIONS_H_
#define CAPRESE_LIBC_INTERNAL_CXX_ITERATOR_FUNCTIONS_H_

#include <cassert>
#include <initializer_list>
#include <internal/cxx/iterator/reverse_iterator.h>
#include <internal/cxx/iterator/tags.h>
#include <internal/cxx/iterator/traits.h>
#include <internal/cxx/stddef.h>

namespace std {
  template<typename T>
  __constexpr_cxx_std_17 auto begin(T& value) -> decltype(value.begin()) {
    return value.begin();
  }

  template<typename T>
  __constexpr_cxx_std_17 auto begin(const T& value) -> decltype(value.begin()) {
    return value.begin();
  }

  template<typename T, __size_t N>
  __constexpr_cxx_std_14 T* begin(T (&array)[N]) __noexcept_cxx_std_14 {
    return array;
  }

  template<typename T>
  __constexpr_cxx_std_17 auto end(T& value) -> decltype(value.end()) {
    return value.end();
  }

  template<typename T>
  __constexpr_cxx_std_17 auto end(const T& value) -> decltype(value.end()) {
    return value.end();
  }

  template<typename T, __size_t N>
  __constexpr_cxx_std_14 T* end(T (&array)[N]) __noexcept_cxx_std_14 {
    return array + N;
  }

#ifdef __CXX_STD_14__

  template<typename T>
  constexpr auto cbegin(const T& value) __noexcept_if(noexcept(std::begin(value))) -> decltype(std::begin(value)) {
    return std::begin(value);
  }

  template<typename T>
  constexpr auto cend(const T& value) __noexcept_if(noexcept(std::end(value))) -> decltype(std::end(value)) {
    return std::end(value);
  }

  template<typename T>
  __constexpr_cxx_std_17 auto rbegin(T& value) -> decltype(value.rbegin()) {
    return value.rbegin();
  }

  template<typename T>
  __constexpr_cxx_std_17 auto rbegin(const T& value) -> decltype(value.rbegin()) {
    return value.rbegin();
  }

  template<typename T, __size_t N>
  __constexpr_cxx_std_17 reverse_iterator<T*> rbegin(T (&array)[N]) {
    return reverse_iterator<T*>(array + N);
  }

  template<typename T>
  __constexpr_cxx_std_17 reverse_iterator<const T*> rbegin(initializer_list<T> init_list) {
    return reverse_iterator<const T*>(init_list.end());
  }

  template<typename T>
  __constexpr_cxx_std_17 auto rend(T& value) -> decltype(value.rend()) {
    return value.rend();
  }

  template<typename T>
  __constexpr_cxx_std_17 auto rend(const T& value) -> decltype(value.rend()) {
    return value.rend();
  }

  template<typename T, __size_t N>
  __constexpr_cxx_std_17 reverse_iterator<T*> rend(T (&array)[N]) {
    return reverse_iterator<T*>(array);
  }

  template<typename T>
  __constexpr_cxx_std_17 reverse_iterator<const T*> rend(initializer_list<T> init_list) {
    return reverse_iterator<const T*>(init_list.begin());
  }

  template<typename T>
  constexpr auto crbegin(const T& value) -> decltype(std::rbegin(value)) {
    return std::rbegin(value);
  }

  template<typename T>
  constexpr auto crend(const T& value) -> decltype(std::rend(value)) {
    return std::rend(value);
  }

#endif // __CXX_STD_14__

#ifdef __CXX_STD_17__

  template<typename T>
  constexpr auto size(const T& t) __noexcept_if(noexcept(t.size())) -> decltype(t.size()) {
    return t.size();
  }

  template<typename T, __size_t N>
  constexpr __size_t size(const T (&)[N]) noexcept {
    return N;
  }

  template<typename T>
  __nodiscard_cxx_std_20 constexpr auto empty(const T& value) -> decltype(value.empty()) {
    return value.empty();
  }

  template<typename T, __size_t N>
  __nodiscard_cxx_std_20 constexpr bool empty(const T (&)[N]) noexcept {
    return false;
  }

  template<typename T>
  __nodiscard_cxx_std_20 constexpr bool empty(initializer_list<T> init_list) noexcept {
    return init_list.size() == 0;
  }

  template<typename T>
  constexpr auto data(T& value) -> decltype(value.data()) {
    return value.data();
  }

  template<typename T>
  constexpr auto data(const T& value) -> decltype(value.data()) {
    return value.data();
  }

  template<typename T, __size_t N>
  constexpr T* data(T (&array)[N]) noexcept {
    return array;
  }

  template<typename T>
  constexpr const T* data(initializer_list<T> init_list) noexcept {
    return init_list.begin();
  }

#endif // __CXX_STD__17__

#ifdef __CXX_STD_20__

  template<typename T, __ptrdiff_t N>
  constexpr __ptrdiff_t ssize(const T (&)[N]) noexcept {
    return N;
  }

#endif // __CXX_STD_20__

  template<typename InputIterator>
  __constexpr_cxx_std_17 typename iterator_traits<InputIterator>::difference_type __distance(InputIterator first, InputIterator last, [[maybe_unused]] input_iterator_tag) {
    typename iterator_traits<InputIterator>::difference_type n = 0;
    while (first != last) {
      ++first;
      ++n;
    }
    return n;
  }

  template<typename RandomAccessIterator>
  __constexpr_cxx_std_17 typename iterator_traits<RandomAccessIterator>::difference_type __distance(RandomAccessIterator first, RandomAccessIterator last, [[maybe_unused]] random_access_iterator_tag) {
    return last - first;
  }

  template<typename InputIterator>
  __constexpr_cxx_std_17 typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last) {
    using category = typename iterator_traits<InputIterator>::iterator_category;
    return __distance(first, last, category {});
  }

  template<typename InputIterator, typename Distance>
  __constexpr_cxx_std_17 void __advance(InputIterator& iter, Distance n, [[maybe_unused]] input_iterator_tag) {
    assert(n >= 0);

    while (n--) {
      ++iter;
    }
  }

  template<typename BidirectionalIterator, typename Distance>
  __constexpr_cxx_std_17 void __advance(BidirectionalIterator& iter, Distance n, [[maybe_unused]] bidirectional_iterator_tag) {
    if (n > 0) {
      while (n--) {
        ++iter;
      }
    } else {
      while (n++) {
        --iter;
      }
    }
  }

  template<typename RandomAccessIterator, typename Distance>
  __constexpr_cxx_std_17 void __advance(RandomAccessIterator& iter, Distance n, [[maybe_unused]] random_access_iterator_tag) {
    iter += n;
  }

  template<typename InputIterator, typename Distance>
  __constexpr_cxx_std_17 void advance(InputIterator& iter, Distance n) {
    using category = typename iterator_traits<InputIterator>::iterator_category;
    __advance(iter, n, category {});
  }
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_ITERATOR_FUNCTIONS_H_
