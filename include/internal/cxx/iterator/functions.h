#ifndef CAPRESE_LIBC_INTERNAL_CXX_ITERATOR_FUNCTIONS_H_
#define CAPRESE_LIBC_INTERNAL_CXX_ITERATOR_FUNCTIONS_H_

#include <cassert>
#include <internal/cxx/iterator/reverse_iterator.h>
#include <internal/cxx/iterator/tags.h>

namespace std {
  template<typename T>
  constexpr auto begin(T& value) -> decltype(value.begin()) {
    return value.begin();
  }

  template<typename T>
  constexpr auto begin(const T& value) -> decltype(value.begin()) {
    return value.begin();
  }

  template<typename T, size_t N>
  constexpr T* begin(T (&array)[N]) noexcept {
    return array;
  }

  template<typename T>
  constexpr auto end(T& value) -> decltype(value.end()) {
    return value.end();
  }

  template<typename T>
  constexpr auto end(const T& value) -> decltype(value.end()) {
    return value.end();
  }

  template<typename T, size_t N>
  constexpr T* end(T (&array)[N]) noexcept {
    return array + N;
  }

  template<typename T>
  auto rbegin(T& value) -> decltype(value.rbegin()) {
    return value.rbegin();
  }

  template<typename T>
  auto rbegin(const T& value) -> decltype(value.rbegin()) {
    return value.rbegin();
  }

  template<typename T, size_t N>
  constexpr reverse_iterator<T*> rbegin(T (&array)[N]) {
    return reverse_iterator<T*>(array + N);
  }

  template<typename T>
  auto rend(T& value) -> decltype(value.rend()) {
    return value.rend();
  }

  template<typename T>
  auto rend(const T& value) -> decltype(value.rend()) {
    return value.rend();
  }

  template<typename T, size_t N>
  constexpr reverse_iterator<T*> rend(T (&array)[N]) {
    return reverse_iterator<T*>(array);
  }

  template<typename T>
  constexpr auto size(const T& t) -> decltype(t.size()) {
    return t.size();
  }

  template<typename T, size_t N>
  constexpr size_t size([[maybe_unused]] const T (&array)[N]) noexcept {
    return N;
  }

  template<typename InputIterator>
  constexpr typename iterator_traits<InputIterator>::difference_type __distance(InputIterator first, InputIterator last, [[maybe_unused]] input_iterator_tag) {
    typename iterator_traits<InputIterator>::difference_type n = 0;
    while (first != last) {
      ++first;
      ++n;
    }
    return n;
  }

  template<typename RandomAccessIterator>
  constexpr typename iterator_traits<RandomAccessIterator>::difference_type __distance(RandomAccessIterator first, RandomAccessIterator last, [[maybe_unused]] random_access_iterator_tag) {
    return last - first;
  }

  template<typename InputIterator>
  constexpr typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last) {
    using category = typename iterator_traits<InputIterator>::iterator_category;
    return __distance(first, last, category {});
  }

  template<typename InputIterator, typename Distance>
  constexpr void __advance(InputIterator& iter, Distance n, [[maybe_unused]] input_iterator_tag) {
    assert(n >= 0);

    while (n--) {
      ++iter;
    }
  }

  template<typename BidirectionalIterator, typename Distance>
  constexpr void __advance(BidirectionalIterator iter, Distance n, [[maybe_unused]] bidirectional_iterator_tag) {
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
  constexpr void __advance(RandomAccessIterator& iter, Distance n, [[maybe_unused]] random_access_iterator_tag) {
    iter += n;
  }

  template<typename InputIterator, typename Distance>
  constexpr void advance(InputIterator& iter, Distance n) {
    using category = typename iterator_traits<InputIterator>::iterator_category;
    __advance(iter, n, category {});
  }
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_ITERATOR_FUNCTIONS_H_
