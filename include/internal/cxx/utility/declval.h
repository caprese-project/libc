#ifndef CAPRESE_INTERNAL_CXX_UTILITY_DECLVAL_H_
#define CAPRESE_INTERNAL_CXX_UTILITY_DECLVAL_H_

#include <internal/cxx/type_traits/modify.h>

namespace std {
  template<typename T>
  typename __add_rvalue_reference<T>::type __declval() noexcept;
}

#endif // CAPRESE_INTERNAL_CXX_UTILITY_DECLVAL_H_
