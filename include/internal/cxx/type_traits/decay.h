#include <internal/cxx/type_traits/modify.h>
#include <internal/cxx/type_traits/type.h>

namespace std {
  template<typename U, bool = __is_array<U>::value, bool = __is_function_t<U>::value>
  struct __decay_helper;

  template<typename U>
  struct __decay_helper<U, false, false> {
    using type = typename __remove_cv<U>::type;
  };

  template<typename U>
  struct __decay_helper<U, true, false> {
    using type = typename __remove_extent<U>::type*;
  };

  template<typename U>
  struct __decay_helper<U, false, true> {
    using type = typename __add_pointer<U>::type;
  };

  template<typename T>
  struct __decay {
  private:
    using U = typename __remove_reference<T>::type;

  public:
    using type = typename __decay_helper<U>::type;
  };
} // namespace std
