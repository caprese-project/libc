#ifndef CAPRESE_LIBC_INTERNAL_CXX_FUNCTIONAL_COMPARE_H_
#define CAPRESE_LIBC_INTERNAL_CXX_FUNCTIONAL_COMPARE_H_

#include <internal/attribute.h>
#include <internal/cxx/utility/fwd.h>

namespace std {
  template<typename T>
  struct __less {
    __constexpr_cxx_std_14 bool operator()(const T& lhs, const T& rhs) const {
      return lhs < rhs;
    }

#ifndef __CXX_STD_20__
    using first_argument_type  = T;
    using second_argument_type = T;
    using result_type          = bool;
#endif // !__CXX_STD_20__
  };

  template<>
  struct __less<void> {
    template<typename T, typename U>
    auto operator()(T&& t, U&& u) const -> decltype(forward<T>(t) < forward<U>(u)) {
      return forward<T>(t) < forward<U>(u);
    }

    using is_transparent = void;
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_FUNCTIONAL_COMPARE_H_
