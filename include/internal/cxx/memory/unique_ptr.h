#ifndef CAPRESE_LIBC_INTERNAL_CXX_MEMORY_UNIQUE_PTR_H_
#define CAPRESE_LIBC_INTERNAL_CXX_MEMORY_UNIQUE_PTR_H_

#include <internal/attribute.h>
#include <internal/cxx/memory/default_delete.h>
#include <internal/cxx/stddef.h>
#include <internal/cxx/type_traits/characteristic.h>
#include <internal/cxx/type_traits/detection.h>
#include <internal/cxx/type_traits/logic.h>
#include <internal/cxx/type_traits/modify.h>
#include <internal/cxx/type_traits/type.h>
#include <internal/cxx/utility/fwd.h>

namespace std {
  template<typename T, typename D = default_delete<T>>
  class unique_ptr {
    template<typename E>
    using __pointer = typename E::pointer;

  public:
    using element_type = T;
    using deleter_type = D;
    using pointer      = typename __detect_type<__pointer, element_type*, deleter_type>::type;

  private:
    template<typename E>
    using __deleter_concept = typename __enable_if<__conjunction<__negation<__is_pointer<E>>, __is_nothrow_default_constructible<E>>::value>::type;

    template<typename U, typename E>
    using __another_type_movable_concept = typename __enable_if<
        __conjunction<__is_convertible<typename unique_ptr<U, E>::pointer, pointer>,
                      __negation<__is_array<U>>,
                      __conditional<__is_reference<deleter_type>::value, __is_same_t<E, deleter_type>, __is_convertible<E, deleter_type>>>::type::value>::type;

    template<typename U, typename E>
    using __another_type_move_assignable_concept = typename __enable_if<__conjunction<__is_assignable<pointer&, typename unique_ptr<U, E>::pointer>, __is_assignable<deleter_type&, E>>::type::value,
                                                                        unique_ptr&>::type;

  private:
    pointer      ptr;
    deleter_type deleter;

  public:
    template<typename Deleter = deleter_type, typename = typename __deleter_concept<Deleter>::type>
    __constexpr unique_ptr() __noexcept: ptr(), deleter() { }

    template<typename Deleter = deleter_type, typename = typename __deleter_concept<Deleter>::type>
    __constexpr_cxx_std_23 explicit unique_ptr(pointer ptr) __noexcept: ptr(ptr), deleter() { }

    template<typename Deleter = deleter_type, typename = typename __enable_if<__is_nothrow_copy_constructible<Deleter>::value>::type>
    __constexpr_cxx_std_23 unique_ptr(pointer ptr, const deleter_type& deleter) __noexcept: ptr(ptr), deleter(deleter) { }

    template<typename Deleter = deleter_type, typename = typename __enable_if<__is_nothrow_move_constructible<Deleter>::value>::type>
    __constexpr_cxx_std_23 unique_ptr(pointer ptr, deleter_type&& deleter) __noexcept: ptr(ptr), deleter(move(deleter)) { }

    template<typename Deleter = deleter_type, typename = typename __enable_if<__is_nothrow_move_constructible<Deleter>::value>::type>
    __constexpr_cxx_std_23 unique_ptr(unique_ptr&& other) __noexcept: ptr(other.release()), deleter(move(other.deleter)) { }

    template<typename Deleter = deleter_type, typename = typename __deleter_concept<Deleter>::type>
    __constexpr unique_ptr(__nullptr_t) __noexcept: ptr(), deleter() { }

#ifdef __CXX_STD_17__

    template<typename U, typename E, typename = typename __another_type_movable_concept<U, E>::type>
    __constexpr_cxx_std_23 unique_ptr(unique_ptr<U, E>&& other) __noexcept: ptr(other.release()), deleter(forward<E>(other.get_deleter())) { }

#endif // __CXX_STD_17__

    unique_ptr(const unique_ptr&) = delete;

    __constexpr_cxx_std_23 ~unique_ptr() {
      if (ptr != nullptr) {
        get_deleter()(std::move(ptr));
      }
      ptr = pointer();
    }

    template<typename Deleter = deleter_type, typename = typename __enable_if<__is_nothrow_move_constructible<Deleter>::value>::type>
    __constexpr_cxx_std_23 unique_ptr& operator=(unique_ptr&& other) __noexcept {
      reset(other.release());
      get_deleter() = move(other.get_deleter());
      return *this;
    }

    template<typename U, typename E>
    __constexpr_cxx_std_23 __another_type_move_assignable_concept<U, E> operator=(unique_ptr<U, E>&& other) __noexcept {
      reset(other.release());
      get_deleter() = forward<E>(other.get_deleter());
      return *this;
    }

    __constexpr_cxx_std_23 unique_ptr& operator=(__nullptr_t) __noexcept {
      reset();
      return *this;
    }

    unique_ptr& operator=(const unique_ptr&) = delete;

    __constexpr_cxx_std_23 pointer release() __noexcept {
      pointer result = ptr;
      ptr            = pointer();
      return result;
    }

    __constexpr_cxx_std_23 void reset(pointer p = pointer()) __noexcept {
      pointer old = ptr;
      ptr         = p;
      if (old != nullptr) {
        get_deleter()(std::move(old));
      }
    }

    __constexpr_cxx_std_23 void swap(unique_ptr& other) __noexcept {
      using std::swap;
      swap(ptr, other.ptr);
      swap(deleter, other.deleter);
    }

    __constexpr_cxx_std_23 pointer get() const __noexcept {
      return ptr;
    }

    __constexpr_cxx_std_23 deleter_type& get_deleter() __noexcept {
      return deleter;
    }

    const __constexpr_cxx_std_23 deleter_type& get_deleter() const __noexcept {
      return deleter;
    }

    __constexpr_cxx_std_23 explicit operator bool() const __noexcept {
      return ptr != nullptr;
    }

    __constexpr_cxx_std_23 typename __add_lvalue_reference<element_type>::type operator*() const __noexcept {
      return *ptr;
    }

    __constexpr_cxx_std_23 pointer operator->() const __noexcept {
      return ptr;
    }
  };

  template<typename T, typename D>
  class unique_ptr<T[], D> {
    template<typename E>
    using __pointer = typename E::pointer;

  public:
    using element_type = T;
    using deleter_type = D;
    using pointer      = typename __detect_type<__pointer, element_type*, deleter_type>::type;

  private:
    template<typename E>
    using __deleter_concept = typename __enable_if<__conjunction<__negation<__is_pointer<E>>, __is_nothrow_default_constructible<E>>::value>::type;

    template<typename U>
    using __pointer_concept_requires = typename __disjunction<
        __is_same_t<U, pointer>,
        __conjuction<__is_same_t<pointer, element_type*>, __is_pointer<U>, __is_convertible<typename __remove_pointer<U>::type (*)[], element_type (*)[]>>>::type;

    template<typename U>
    using __pointer_concept = typename __enable_if<__pointer_concept_requires<U>::value, U>::type;

    template<typename U>
    using __nullable_pointer_concept = typename __enable_if<__disjuction<__is_null_pointer<U>, __pointer_concept_requires<U>::value>, U>::type;

    template<typename U, typename E>
    using __another_type_movable_concept = typename __enable_if<__conjuction<__negation<__is_array<U>>,
                                                                             __is_same_t<pointer, element_type*>,
                                                                             __is_same_t<typename unique_ptr<U, E>::pointer, typename unique_ptr<U, E>::element_type*>,
                                                                             __is_convertible<typename unique_ptr<U, E>::element_type (*)[], element_type (*)[]>,
                                                                             __disjuction<__conjuction<__is_same_t<deleter_type, E>, __is_reference<deleter_type>, __is_reference<E>>,
                                                                                          __conjuction<__negation<__is_reference<E>>, __is_convertible<E, deleter_type>>>>::value>::type;

    template<typename U, typename E>
    using __another_type_move_assignable_concept = typename __enable_if<__conjuction<__is_array<U>,
                                                                                     __is_same_t<pointer, element_type*>,
                                                                                     __is_same_t<typename unique_ptr<U, E>::pointer, typename unique_ptr<U, E>::element_type*>,
                                                                                     __is_convertible<typename unique_ptr<U, deleter_type>::element_type (*)[], element_type (*)[]>,
                                                                                     __is_assignable_t<deleter_type&, E&&>>>::type;

    template<typename U>
    using __another_type_resettable_concept = typename __enable_if<
        __disjuction<__is_same_t<pointer, U>, __conjuction<__is_same_t<pointer, element_type*>, __is_pointer<U>, __is_convertible<typename __remove_pointer<U>::type (*)[], element_type (*)[]>>>,
        U>::type;

  private:
    pointer      ptr;
    deleter_type deleter;

  public:
    template<typename Deleter = deleter_type, typename = typename __deleter_concept<Deleter>::type>
    __constexpr unique_ptr() __noexcept: ptr(), deleter() { }

    template<typename U, typename Deleter = deleter_type, typename = typename __deleter_concept<Deleter>::type>
    __constexpr_cxx_std_23 explicit unique_ptr(__pointer_concept<U> ptr) __noexcept: ptr(ptr), deleter();

    template<typename U, typename Deleter = deleter_type, typename = typename __enable_if<__is_nothrow_copy_constructible<Deleter>::value>::type>
    __constexpr_cxx_std_23 unique_ptr(__nullable_pointer_concept<U> ptr, const deleter_type& deleter) __noexcept: ptr(ptr), deleter(deleter) { }

    template<typename U, typename Deleter = deleter_type, typename = typename __enable_if<__is_nothrow_move_constructible<Deleter>::value>::type>
    __constexpr_cxx_std_23 unique_ptr(__nullable_pointer_concept<U> ptr, deleter_type&& deleter) __noexcept: ptr(ptr), deleter(move(deleter)) { }

    template<typename Deleter = deleter_type, typename = typename __enable_if<__is_nothrow_move_constructible<Deleter>::value>::type>
    __constexpr_cxx_std_23 unique_ptr(unique_ptr&& other) __noexcept: ptr(other.release()), deleter(move(other.deleter)) { }

    template<typename Deleter = deleter_type, typename = typename __deleter_concept<Deleter>::type>
    __constexpr unique_ptr(__nullptr_t) __noexcept: ptr(), deleter() { }

#ifdef __CXX_STD_17__

    template<typename U, typename E, typename = typename __another_type_movable_concept<U, E>::type>
    __constexpr_cxx_std_23 unique_ptr(unique_ptr<U, E>&& other) __noexcept: ptr(other.release()), deleter(forward<E>(other.get_deleter())) { }

#endif // __CXX_STD_17__

    unique_ptr(const unique_ptr&) = delete;

    __constexpr_cxx_std_23 ~unique_ptr() {
      if (ptr != nullptr) {
        get_deleter()(std::move(ptr));
      }
      ptr = pointer();
    }

    template<typename Deleter = deleter_type, typename = typename __enable_if<__is_nothrow_move_constructible<Deleter>::value>::type>
    __constexpr_cxx_std_23 unique_ptr& operator=(unique_ptr&& other) __noexcept {
      reset(other.release());
      get_deleter() = move(other.get_deleter());
      return *this;
    }

    template<typename U, typename E>
    __constexpr_cxx_std_23 __another_type_move_assignable_concept<U, E> operator=(unique_ptr<U, E>&& other) __noexcept {
      reset(other.release());
      get_deleter() = forward<E>(other.get_deleter());
      return *this;
    }

    __constexpr_cxx_std_23 unique_ptr& operator=(__nullptr_t) __noexcept {
      reset();
      return *this;
    }

    unique_ptr& operator=(const unique_ptr&) = delete;

    __constexpr_cxx_std_23 pointer release() __noexcept {
      pointer result = ptr;
      ptr            = pointer();
      return result;
    }

    __constexpr_cxx_std_23 void reset(pointer p = pointer()) __noexcept {
      pointer old = ptr;
      ptr         = p;
      if (old != nullptr) {
        get_deleter()(std::move(old));
      }
    }

    __constexpr_cxx_std_23 void reset(nullptr_t = nullptr) __noexcept {
      reset(pointer());
    }

    template<typename U>
    __constexpr_cxx_std_23 void reset(__another_type_resettable_concept<U> p) __noexcept {
      reset(pointer(p));
    }

    __constexpr_cxx_std_23 void swap(unique_ptr& other) __noexcept {
      using std::swap;
      swap(ptr, other.ptr);
      swap(deleter, other.deleter);
    }

    __constexpr_cxx_std_23 pointer get() const __noexcept {
      return ptr;
    }

    __constexpr_cxx_std_23 deleter_type& get_deleter() __noexcept {
      return deleter;
    }

    const __constexpr_cxx_std_23 deleter_type& get_deleter() const __noexcept {
      return deleter;
    }

    __constexpr_cxx_std_23 explicit operator bool() const __noexcept {
      return ptr != nullptr;
    }

    __constexpr_cxx_std_23 element_type& operator[](__size_t idx) const {
      return get()[idx];
    }
  };

  template<typename T, typename D>
  __constexpr_cxx_std_23 void swap(unique_ptr<T, D>& lhs, unique_ptr<T, D>& rhs) __noexcept {
    lhs.swap(rhs);
  }

  template<typename T, typename... Args>
  __constexpr_cxx_std_23 typename __enable_if<!__is_array<T>::value, unique_ptr<T>>::type make_unique(Args&&... args) {
    return unique_ptr<T>(new T(forward<Args>(args)...));
  }

  template<typename T>
  __constexpr_cxx_std_23 typename __enable_if<__is_unbounded_array<T>::value, unique_ptr<T>>::type make_unique(size_t size) {
    using U = typename __remove_extent<T>::type;
    return unique_ptr<T>(new U[size]());
  }

  template<typename T, typename... Array>
  typename __enable_if<__is_bounded_array<T>::value>::type make_unique(Args&&...) = delete;
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_MEMORY_UNIQUE_PTR_H_
