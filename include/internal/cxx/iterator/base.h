#ifndef CAPRESE_LIBC_INTERNAL_CXX_ITERATOR_BASE_H_
#define CAPRESE_LIBC_INTERNAL_CXX_ITERATOR_BASE_H_

#include <internal/attribute.h>
#include <internal/cxx/iterator/traits.h>

namespace std {
  template<typename Iterator, typename Container>
  class __iterator_base {
    Iterator cur;

    using __traits = iterator_traits<Iterator>;

  public:
    using iterator_type     = Iterator;
    using iterator_category = typename __traits::iterator_category;
    using value_type        = typename __traits::value_type;
    using difference_type   = typename __traits::difference_type;
    using pointer           = typename __traits::pointer;
    using reference         = typename __traits::reference;

    __constexpr_cxx_std_20 __iterator_base() __noexcept: cur(Iterator {}) { }

    explicit __constexpr_cxx_std_20 __iterator_base(const iterator_type& iter) __noexcept: cur(iter) { }

    __constexpr_cxx_std_20 reference operator*() const __noexcept {
      return *cur;
    }

    __constexpr_cxx_std_20 pointer operator->() const __noexcept {
      return cur;
    }

    __constexpr_cxx_std_20 __iterator_base& operator++() __noexcept {
      ++cur;
      return *this;
    }

    __constexpr_cxx_std_20 __iterator_base operator++(__unused int) __noexcept {
      __iterator_base tmp = *this;
      ++cur;
      return tmp;
    }

    __constexpr_cxx_std_20 __iterator_base& operator--() __noexcept {
      --cur;
      return *this;
    }

    __constexpr_cxx_std_20 __iterator_base operator--(__unused int) __noexcept {
      __iterator_base tmp = *this;
      --cur;
      return tmp;
    }

    __constexpr_cxx_std_20 __iterator_base& operator+=(difference_type n) __noexcept {
      cur += n;
      return *this;
    }

    __constexpr_cxx_std_20 __iterator_base operator+(difference_type n) const __noexcept {
      __iterator_base tmp = *this;
      tmp += n;
      return tmp;
    }

    __constexpr_cxx_std_20 __iterator_base& operator-=(difference_type n) __noexcept {
      cur -= n;
      return *this;
    }

    __constexpr_cxx_std_20 __iterator_base operator-(difference_type n) const __noexcept {
      __iterator_base tmp = *this;
      tmp -= n;
      return tmp;
    }

    __constexpr_cxx_std_20 reference operator[](difference_type n) const __noexcept {
      return cur[n];
    }

    __constexpr_cxx_std_20 iterator_type base() const __noexcept {
      return cur;
    }
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_ITERATOR_BASE_H_
