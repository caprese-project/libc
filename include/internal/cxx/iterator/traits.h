#ifndef CAPRESE_LIBC_INTERNAL_CXX_ITERATOR_TRAITS_H_
#define CAPRESE_LIBC_INTERNAL_CXX_ITERATOR_TRAITS_H_

#include <cstddef>
#include <internal/cxx/iterator/tags.h>
#include <internal/cxx/type_traits/modify.h>

namespace std {
  template<typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T*, typename Reference = T&>
  struct iterator {
    using value_type        = T;
    using difference_type   = Distance;
    using pointer           = Pointer;
    using reference         = Reference;
    using iterator_category = Category;
  };

  template<typename I>
  struct iterator_traits {
    using difference_type   = typename I::difference_type;
    using value_type        = typename I::value_type;
    using pointer           = typename I::pointer;
    using reference         = typename I::reference;
    using iterator_category = typename I::iterator_category;
  };

  template<typename T>
  struct iterator_traits<T*> {
    using difference_type   = ptrdiff_t;
    using value_type        = typename __remove_cv<T>::type;
    using pointer           = T*;
    using reference         = T&;
    using iterator_category = random_access_iterator_tag;
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_ITERATOR_TRAITS_H_
