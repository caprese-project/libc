#ifndef CAPRESE_LIBC_INTERNAL_CXX_ALGORITHM_SEQ_H_
#define CAPRESE_LIBC_INTERNAL_CXX_ALGORITHM_SEQ_H_

#include <internal/attribute.h>

namespace std {
  template<typename InputIterator, typename Function>
  __constexpr_cxx_std_14 Function for_each(InputIterator first, InputIterator last, Function f) {
    while (first != last) {
      f(*first);
      ++first;
    }

    return f;
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

  template<typename OutputIterator, typename Size, typename T>
  __constexpr_cxx_std_20 OutputIterator fill_n(OutputIterator first, Size n, const T& value) {
    for (Size i = 0; i < n; ++i) {
      *first = value;
      ++first;
    }

    return first;
  }
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_ALGORITHM_SEQ_H_
