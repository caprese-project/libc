#ifndef CAPRESE_LIBC_STDINT_H_
#define CAPRESE_LIBC_STDINT_H_

#include <internal/datamodel.h>

#define SIG_ATOMIC_MIN INT_MIN
#define SIG_ATOMIC_MAX INT_MAX

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#if defined(__LP64)
  typedef signed char        int8_t;
  typedef signed short int   int16_t;
  typedef signed int         int32_t;
  typedef signed long int    int64_t;
  typedef signed long int    intptr_t;
  typedef signed long int    intmax_t;
  typedef unsigned char      uint8_t;
  typedef unsigned short int uint16_t;
  typedef unsigned int       uint32_t;
  typedef unsigned long int  uint64_t;
  typedef unsigned long int  uintptr_t;
  typedef unsigned long int  uintmax_t;
#elif defined(__ILP32)
  typedef signed char          int8_t;
  typedef signed short int     int16_t;
  typedef signed int           int32_t;
  typedef signed long long int int64_t;
  typedef signed long int      intptr_t;
  typedef signed long long int intmax_t;
  typedef unsigned char        uint8_t;
  typedef unsigned short       uint16_t;
  typedef unsigned int         uint32_t;
  typedef unsigned long long   uint64_t;
  typedef unsigned long        uintptr_t;
  typedef unsigned long long   uintmax_t;
#endif

  // TODO: Define least and fast as optimal types

  typedef int8_t   int_least8_t;
  typedef int16_t  int_least16_t;
  typedef int32_t  int_least32_t;
  typedef int64_t  int_least64_t;
  typedef uint8_t  uint_least8_t;
  typedef uint16_t uint_least16_t;
  typedef uint32_t uint_least32_t;
  typedef uint64_t uint_least64_t;
  typedef int8_t   int_fast8_t;
  typedef int16_t  int_fast16_t;
  typedef int32_t  int_fast32_t;
  typedef int64_t  int_fast64_t;
  typedef uint8_t  uint_fast8_t;
  typedef uint16_t uint_fast16_t;
  typedef uint32_t uint_fast32_t;
  typedef uint64_t uint_fast64_t;

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // CAPRESE_LIBC_STDINT_H_
