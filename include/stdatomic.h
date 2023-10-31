#ifndef CAPRESE_LIBC_STDATOMIC_H_
#define CAPRESE_LIBC_STDATOMIC_H_

#include <internal/version.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __GNUC__

#ifndef __ATOMIC_RELAXED
#define __ATOMIC_RELAXED 0
#endif
#ifndef __ATOMIC_CONSUME
#define __ATOMIC_CONSUME 1
#endif
#ifndef __ATOMIC_ACQUIRE
#define __ATOMIC_ACQUIRE 2
#endif
#ifndef __ATOMIC_RELEASE
#define __ATOMIC_RELEASE 3
#endif
#ifndef __ATOMIC_ACQ_REL
#define __ATOMIC_ACQ_REL 4
#endif
#ifndef __ATOMIC_SEQ_CST
#define __ATOMIC_SEQ_CST 5
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef __CXX_STD_20__

  enum class memory_order {
    relaxed = __ATOMIC_RELAXED,
    consume = __ATOMIC_CONSUME,
    acquire = __ATOMIC_ACQUIRE,
    release = __ATOMIC_RELEASE,
    acq_rel = __ATOMIC_ACQ_REL,
    seq_cst = __ATOMIC_SEQ_CST,
  };

  inline constexpr memory_order memory_order_relaxed = memory_order::relaxed;
  inline constexpr memory_order memory_order_consume = memory_order::consume;
  inline constexpr memory_order memory_order_acquire = memory_order::acquire;
  inline constexpr memory_order memory_order_release = memory_order::release;
  inline constexpr memory_order memory_order_acq_rel = memory_order::acq_rel;
  inline constexpr memory_order memory_order_seq_cst = memory_order::seq_cst;

#else // ^^^ __CXX_STD_20__ ^^^ / vvv !__CXX_STD_20__ vvv

  typedef enum {
    memory_order_relaxed = __ATOMIC_RELAXED,
    memory_order_consume = __ATOMIC_CONSUME,
    memory_order_acquire = __ATOMIC_ACQUIRE,
    memory_order_release = __ATOMIC_RELEASE,
    memory_order_acq_rel = __ATOMIC_ACQ_REL,
    memory_order_seq_cst = __ATOMIC_SEQ_CST,
  } memory_order;

#endif // !__CXX_STD_20__

#define _Atomic(T) \
struct {           \
volatile T __val;  \
}

#define ATOMIC_VAR_INIT(value) \
{ .__val = (value) }

#define atomic_init(obj, value) \
do {                            \
(obj)->__val = (value);         \
} while (0)

#define ATOMIC_FLAG_INIT (atomic_flag) ATOMIC_VAR_INIT(0)

#ifdef __GNUC_ATOMICS

#define atomic_thread_fence(order) __atomic_thread_fence(order)
#define atomic_signal_fence(order) __atomic_signal_fence(order)
#define atomic_is_lock_free(obj)   __atomic_is_lock_free(sizeof((obj)->__val))

#define atomic_compare_exchange_strong_explicit(object, expected, desired, success, failure) __atomic_compare_exchange_n(&(object)->__val, expected, desired, 0, success, failure)
#define atomic_compare_exchange_weak_explicit(object, expected, desired, success, failure)   __atomic_compare_exchange_n(&(object)->__val, expected, desired, 1, success, failure)
#define atomic_exchange_explicit(object, desired, order)                                     __atomic_exchange_n(&(object)->__val, desired, order)
#define atomic_fetch_add_explicit(object, operand, order)                                    __atomic_fetch_add(&(object)->__val, operand, order)
#define atomic_fetch_and_explicit(object, operand, order)                                    __atomic_fetch_and(&(object)->__val, operand, order)
#define atomic_fetch_or_explicit(object, operand, order)                                     __atomic_fetch_or(&(object)->__val, operand, order)
#define atomic_fetch_sub_explicit(object, operand, order)                                    __atomic_fetch_sub(&(object)->__val, operand, order)
#define atomic_fetch_xor_explicit(object, operand, order)                                    __atomic_fetch_xor(&(object)->__val, operand, order)
#define atomic_load_explicit(object, order)                                                  __atomic_load_n(&(object)->__val, order)
#define atomic_store_explicit(object, desired, order)                                        __atomic_store_n(&(object)->__val, desired, order)

#else // ^^^ __GNUC_ATOMICS ^^^ / vvv !__GNUC_ATOMICS vvv

#define atomic_thread_fence(order) __sync_synchronize()
#define atomic_signal_fence(order) __asm volatile("" : : : "memory")
#define atomic_is_lock_free(obj)   (sizeof((obj)->__val) <= sizeof(void*))

#define atomic_compare_exchange_strong_explicit(object, expected, desired, success, failure) \
({                                                                                           \
__typeof__((object)->__val) __v;                                                               \
_Bool                       __r;                                                               \
__v         = __sync_val_compare_and_swap(&(object)->__val, *(expected), desired);             \
__r         = *(expected) == __v;                                                              \
*(expected) = __v;                                                                             \
__r;                                                                                           \
})
#define atomic_compare_exchange_weak_explicit(object, expected, desired, success, failure) atomic_compare_exchange_strong_explicit(object, expected, desired, success, failure)
#define atomic_exchange_explicit(object, desired, order) \
({                                                       \
__typeof__((object)->__val) __v;                           \
__v = __sync_lock_test_and_set(&(object)->__val, desired); \
__sync_synchronize();                                      \
__v;                                                       \
})
#define atomic_fetch_add_explicit(object, operand, order) __sync_fetch_and_add(&(object)->__val, operand)
#define atomic_fetch_and_explicit(object, operand, order) __sync_fetch_and_and(&(object)->__val, operand)
#define atomic_fetch_or_explicit(object, operand, order)  __sync_fetch_and_or(&(object)->__val, operand)
#define atomic_fetch_sub_explicit(object, operand, order) __sync_fetch_and_sub(&(object)->__val, operand)
#define atomic_fetch_xor_explicit(object, operand, order) __sync_fetch_and_xor(&(object)->__val, operand)
#define atomic_load_explicit(object, order)               __sync_fetch_and_add(&(object)->__val, 0)
#define atomic_store_explicit(object, desired, order) \
do {                                                  \
__sync_synchronize();                                 \
(object)->__val = (desired);                          \
__sync_synchronize();                                 \
} while (0)

#endif // !__GNUC_ATOMICS

#define atomic_compare_exchange_strong(object, expected, desired) atomic_compare_exchange_strong_explicit(object, expected, desired, memory_order_seq_cst, memory_order_seq_cst)
#define atomic_compare_exchange_weak(object, expected, desired)   atomic_compare_exchange_weak_explicit(object, expected, desired, memory_order_seq_cst, memory_order_seq_cst)
#define atomic_exchange(object, desired)                          atomic_exchange_explicit(object, desired, memory_order_seq_cst)
#define atomic_fetch_add(object, operand)                         atomic_fetch_add_explicit(object, operand, memory_order_seq_cst)
#define atomic_fetch_and(object, operand)                         atomic_fetch_and_explicit(object, operand, memory_order_seq_cst)
#define atomic_fetch_or(object, operand)                          atomic_fetch_or_explicit(object, operand, memory_order_seq_cst)
#define atomic_fetch_sub(object, operand)                         atomic_fetch_sub_explicit(object, operand, memory_order_seq_cst)
#define atomic_fetch_xor(object, operand)                         atomic_fetch_xor_explicit(object, operand, memory_order_seq_cst)
#define atomic_load(object)                                       atomic_load_explicit(object, memory_order_seq_cst)
#define atomic_store(object, desired)                             atomic_store_explicit(object, desired, memory_order_seq_cst)
#define atomic_flag_clear_explicit(object, order)                 atomic_store_explicit(object, 0, order)
#define atomic_flag_test_and_set_explicit(object, order)          atomic_exchange_explicit(object, 1, order)
#define atomic_flag_clear(object)                                 atomic_flag_clear_explicit(object, memory_order_seq_cst)
#define atomic_flag_test_and_set(object)                          atomic_flag_test_and_set_explicit(object, memory_order_seq_cst)

  typedef _Atomic(_Bool)              atomic_bool;
  typedef _Atomic(char)               atomic_char;
  typedef _Atomic(signed char)        atomic_schar;
  typedef _Atomic(unsigned char)      atomic_uchar;
  typedef _Atomic(short)              atomic_short;
  typedef _Atomic(unsigned short)     atomic_ushort;
  typedef _Atomic(int)                atomic_int;
  typedef _Atomic(unsigned int)       atomic_uint;
  typedef _Atomic(long)               atomic_long;
  typedef _Atomic(unsigned long)      atomic_ulong;
  typedef _Atomic(long long)          atomic_llong;
  typedef _Atomic(unsigned long long) atomic_ullong;
  typedef _Atomic(int_least8_t)       atomic_int_least8_t;
  typedef _Atomic(uint_least8_t)      atomic_uint_least8_t;
  typedef _Atomic(int_least16_t)      atomic_int_least16_t;
  typedef _Atomic(uint_least16_t)     atomic_uint_least16_t;
  typedef _Atomic(int_least32_t)      atomic_int_least32_t;
  typedef _Atomic(uint_least32_t)     atomic_uint_least32_t;
  typedef _Atomic(int_least64_t)      atomic_int_least64_t;
  typedef _Atomic(uint_least64_t)     atomic_uint_least64_t;
  typedef _Atomic(int_fast8_t)        atomic_int_fast8_t;
  typedef _Atomic(uint_fast8_t)       atomic_uint_fast8_t;
  typedef _Atomic(int_fast16_t)       atomic_int_fast16_t;
  typedef _Atomic(uint_fast16_t)      atomic_uint_fast16_t;
  typedef _Atomic(int_fast32_t)       atomic_int_fast32_t;
  typedef _Atomic(uint_fast32_t)      atomic_uint_fast32_t;
  typedef _Atomic(int_fast64_t)       atomic_int_fast64_t;
  typedef _Atomic(uint_fast64_t)      atomic_uint_fast64_t;
  typedef _Atomic(intptr_t)           atomic_intptr_t;
  typedef _Atomic(uintptr_t)          atomic_uintptr_t;
  typedef _Atomic(size_t)             atomic_size_t;
  typedef _Atomic(ptrdiff_t)          atomic_ptrdiff_t;
  typedef _Atomic(intmax_t)           atomic_intmax_t;
  typedef _Atomic(uintmax_t)          atomic_uintmax_t;
  typedef atomic_bool                 atomic_flag;

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#else // ^^^ __GNUC__ ^^^ / vvv !__GNUC__

#error "This compiler doesn't support stdatomic.h"

#endif // !__GNUC__

#endif // CAPRESE_LIBC_STDATOMIC_H_
