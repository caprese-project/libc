#ifndef CAPRESE_LIBC_INTERNAL_CXX_ALGORITHM_SEQ_H_
#define CAPRESE_LIBC_INTERNAL_CXX_ALGORITHM_SEQ_H_

#include <internal/attribute.h>
#include <internal/cxx/utility/fwd.h>

namespace std {
  template<typename InputIterator1, typename InputIterator2>
  __constexpr_cxx_std_20 bool equal(InputIterator1 first, InputIterator1 last, InputIterator2 first2) {
    while (first != last) {
      if (!(*first == *first2)) {
        return false;
      }

      ++first;
      ++first2;
    }

    return true;
  }

  template<typename InputIterator, typename Function>
  __constexpr_cxx_std_14 Function for_each(InputIterator first, InputIterator last, Function f) {
    while (first != last) {
      f(*first);
      ++first;
    }

    return f;
  }

  template<class InputIterator, class OutputIterator>
  __constexpr_cxx_std_20 OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) {
    while (first != last) {
      *result = *first;
      ++result;
      ++first;
    }

    return result;
  }

  template<typename InputIterator, typename Size, typename OutputIterator>
  __constexpr_cxx_std_20 OutputIterator copy_n(InputIterator first, Size n, OutputIterator result) {
    if (n > 0) {
      *result = *first;
      for (Size i = 1; i < n; ++i) {
        ++result;
        ++first;
        *result = *first;
      }
    }

    return result;
  }

  template<typename InputIterator, typename OutputIterator>
  __constexpr_cxx_std_20 OutputIterator move(InputIterator first, InputIterator last, OutputIterator result) {
    while (first != last) {
      *result = move(*first);
      ++result;
      ++first;
    }

    return result;
  }

  template<typename BidirectionalIterator1, typename BidirectionalIterator2>
  __constexpr_cxx_std_20 BidirectionalIterator2 move_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result) {
    while (first != last) {
      --last;
      --result;
      *result = move(*last);
    }

    return result;
  }

  template<typename OutputIterator, typename Size, typename T>
  __constexpr_cxx_std_20 OutputIterator fill_n(OutputIterator first, Size n, const T& value) {
    for (Size i = 0; i < n; ++i) {
      *first = value;
      ++first;
    }

    return first;
  }

  template<typename ForwardIterator, typename T>
  __constexpr_cxx_std_20 ForwardIterator remove(ForwardIterator first, ForwardIterator last, const T& value) {
    ForwardIterator result = first;
    while (first != last) {
      if (!(*first == value)) {
        *result = move(*first);
        ++result;
      }

      ++first;
    }

    return result;
  }

  template<typename ForwardIterator, typename Predicate>
  __constexpr_cxx_std_20 ForwardIterator remove_if(ForwardIterator first, ForwardIterator last, Predicate pred) {
    ForwardIterator result = first;
    while (first != last) {
      if (!pred(*first)) {
        *result = move(*first);
        ++result;
      }

      ++first;
    }

    return result;
  }
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_ALGORITHM_SEQ_H_
