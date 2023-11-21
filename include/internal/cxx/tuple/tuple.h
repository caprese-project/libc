#ifndef CAPRESE_LIBC_INTERNAL_CXX_TUPLE_TUPLE_H_
#define CAPRESE_LIBC_INTERNAL_CXX_TUPLE_TUPLE_H_

#include <internal/attribute.h>
#include <internal/cxx/stddef.h>
#include <internal/cxx/type_traits/characteristic.h>
#include <internal/cxx/utility/fwd.h>

namespace std {
  template<__size_t Index, typename Head>
  class __tuple_head {
    Head _head;

  public:
    constexpr __tuple_head()                    = default;
    constexpr __tuple_head(const __tuple_head&) = default;
    constexpr __tuple_head(__tuple_head&&)      = default;

    constexpr __tuple_head(const Head& head): _head(head) { }

    template<typename U>
    constexpr __tuple_head(U&& head): _head(std::forward<U>(head)) { }

    static constexpr Head& __get_head(__tuple_head& head) noexcept {
      return head._head;
    };

    static constexpr const Head& __get_head(const __tuple_head& head) noexcept {
      return head._head;
    }
  };

  template<__size_t Index, typename... Tn>
  class __tuple_helper;

  template<__size_t Index, typename Head>
  class __tuple_helper<Index, Head>: private __tuple_head<Index, Head> {
    template<__size_t, typename...>
    friend struct __tuple_helper;

    using __head = __tuple_head<Index, Head>;

  public:
    constexpr __tuple_helper()                      = default;
    constexpr __tuple_helper(const __tuple_helper&) = default;
    constexpr __tuple_helper(__tuple_helper&&)      = default;

    explicit constexpr __tuple_helper(const Head& head): __head(head) { }

    template<typename U>
    explicit constexpr __tuple_helper(U&& head): __head(std::forward<U>(head)) { }

    static constexpr Head& __get_head(__tuple_helper& head) noexcept {
      return __head::__get_head(head);
    }

    static constexpr const Head& __get_head(const __tuple_helper& head) noexcept {
      return __head::__get_head(head);
    }
  };

  template<__size_t Index, typename Head, typename... Tn>
  class __tuple_helper<Index, Head, Tn...>: public __tuple_helper<Index + 1, Tn...>, private __tuple_head<Index, Head> {
    template<__size_t, typename...>
    friend class __tuple_helper;

    using __next = __tuple_helper<Index + 1, Tn...>;
    using __head = __tuple_head<Index, Head>;

  public:
    constexpr __tuple_helper(): __next(), __head() { }

    constexpr __tuple_helper(const __tuple_helper&)  = default;
    constexpr __tuple_helper(__tuple_helper&&)       = default;
    __tuple_helper& operator=(const __tuple_helper&) = delete;
    __tuple_helper& operator=(__tuple_helper&&)      = default;

    explicit constexpr __tuple_helper(const Head& head, const Tn&... tail): __next(tail...), __head(head) { }

    template<typename U, typename... Un>
    explicit constexpr __tuple_helper(U&& head, Un&&... tail): __next(std::forward<Un>(tail)...),
                                                               __head(std::forward<U>(head)) { }

    static constexpr Head& __get_head(__tuple_helper& head) noexcept {
      return __head::__get_head(head);
    }

    static constexpr const Head& __get_head(const __tuple_helper& head) noexcept {
      return __head::__get_head(head);
    }
  };

  template<typename... Tn>
  class __tuple: public __tuple_helper<0, Tn...> {
    using __helper = __tuple_helper<0, Tn...>;

  public:
    constexpr __tuple(): __helper() { }

    constexpr __tuple(const __tuple&) = default;
    constexpr __tuple(__tuple&&)      = default;

    constexpr __tuple(const Tn&... args): __helper(args...) { }

    template<typename... Un>
    constexpr __tuple(Un&&... args): __helper(std::forward<Un>(args)...) { }
  };

  template<>
  class __tuple<> {
  public:
    constexpr __tuple() = default;

    __constexpr_cxx_std_20 void swap(__tuple&) noexcept { }
  };

  template<typename T1, typename T2>
  class __tuple<T1, T2>: public __tuple_helper<0, T1, T2> {
    using __helper = __tuple_helper<0, T1, T2>;

  public:
    constexpr __tuple(): __helper() { }

    constexpr __tuple(const __tuple&) = default;
    constexpr __tuple(__tuple&&)      = default;

    constexpr __tuple(const T1& t1, const T2& t2): __helper(t1, t2) { }

    template<typename U1, typename U2>
    constexpr __tuple(U1&& u1, U2&& u2): __helper(std::forward<U1>(u1), std::forward<U2>(u2)) { }
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_TUPLE_TUPLE_H_
