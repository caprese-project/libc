#ifndef CAPRESE_LIBC_INTERNAL_CXX_ITERATOR_REVERSE_ITERATOR_H_
#define CAPRESE_LIBC_INTERNAL_CXX_ITERATOR_REVERSE_ITERATOR_H_

#include <internal/cxx/iterator/traits.h>

namespace std {
  template<typename I>
  class reverse_iterator: public iterator<typename iterator_traits<I>::iterator_category,
                                          typename iterator_traits<I>::value_type,
                                          typename iterator_traits<I>::difference_type,
                                          typename iterator_traits<I>::pointer,
                                          typename iterator_traits<I>::reference> {
  public:
    using difference_type   = typename iterator_traits<I>::difference_type;
    using value_type        = typename iterator_traits<I>::value_type;
    using pointer           = typename iterator_traits<I>::pointer;
    using reference         = typename iterator_traits<I>::reference;
    using iterator_type     = I;
    using iterator_category = typename iterator_traits<I>::iterator_category;

  protected:
    I current;

  public:
    constexpr reverse_iterator(): current(I {}) { }

    constexpr explicit reverse_iterator(I x): current(x) { }

    ~reverse_iterator() = default;

    constexpr reverse_iterator& operator=(const reverse_iterator& u) = default;

    constexpr I base() const {
      return current;
    }

    constexpr reference operator*() const {
      I tmp = current;
      return *--tmp;
    }

    constexpr pointer operator->() const {
      return &(operator*());
    }

    constexpr reverse_iterator& operator++() {
      --current;
      return *this;
    }

    constexpr reverse_iterator operator++([[maybe_unused]] int) {
      reverse_iterator tmp = *this;
      --current;
      return tmp;
    }

    constexpr reverse_iterator& operator--() {
      ++current;
      return *this;
    }

    constexpr reverse_iterator& operator--([[maybe_unused]] int) {
      reverse_iterator tmp = *this;
      ++current;
      return tmp;
    }

    constexpr reverse_iterator operator+(difference_type n) const {
      return reverse_iterator(current - n);
    }

    constexpr reverse_iterator& operator+=(difference_type n) {
      current -= n;
      return *this;
    }

    constexpr reverse_iterator operator-(difference_type n) const {
      return reverse_iterator(current + n);
    }

    constexpr reverse_iterator& operator-=(difference_type n) {
      current += n;
      return *this;
    }

    constexpr reference operator[](difference_type n) const {
      return current[-n - 1];
    }
  };

  template<typename L, typename R>
  constexpr bool operator==(const reverse_iterator<L>& lhs, const reverse_iterator<R>& rhs) {
    return lhs.base() == rhs.base();
  }

  template<typename L, typename R>
  constexpr bool operator!=(const reverse_iterator<L>& lhs, const reverse_iterator<R>& rhs) {
    return lhs.base() != rhs.base();
  }

  template<typename L, typename R>
  constexpr bool operator<(const reverse_iterator<L>& lhs, const reverse_iterator<R>& rhs) {
    return lhs.base() < rhs.base();
  }

  template<typename L, typename R>
  constexpr bool operator<=(const reverse_iterator<L>& lhs, const reverse_iterator<R>& rhs) {
    return lhs.base() <= rhs.base();
  }

  template<typename L, typename R>
  constexpr bool operator>(const reverse_iterator<L>& lhs, const reverse_iterator<R>& rhs) {
    return lhs.base() > rhs.base();
  }

  template<typename L, typename R>
  constexpr bool operator>=(const reverse_iterator<L>& lhs, const reverse_iterator<R>& rhs) {
    return lhs.base() >= rhs.base();
  }

  template<class L, class R>
  constexpr auto operator-(const reverse_iterator<L>& lhs, const reverse_iterator<R>& rhs) -> decltype(lhs.base() - rhs.base()) {
    return lhs.base() - rhs.base();
  }

  template<typename I>
  constexpr reverse_iterator<I> operator+(typename reverse_iterator<I>::difference_type n, const reverse_iterator<I>& it) {
    return reverse_iterator<I>(it.base() - n);
  }
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_ITERATOR_REVERSE_ITERATOR_H_
