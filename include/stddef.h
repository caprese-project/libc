#ifndef CAPRESE_LIBC_STDDEF_H_
#define CAPRESE_LIBC_STDDEF_H_

#include <internal/datamodel.h>
#include <internal/stddef.h>
#include <internal/version.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define NULL 0

#ifdef __GNUC__
#define offsetof(type, member) __builtin_offsetof(type, member)
#else
#define offsetof(type, member) ((size_t) & ((type*)0)->member)
#endif // __GNUC__

  typedef __PTRDIFF_TYPE ptrdiff_t;
  typedef __SIZE_TYPE    size_t;
  typedef __SSIZE_TYPE   ssize_t;

  typedef int errno_t;

#if defined(__C_STD_11__) || (defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ >= 1)
  typedef size_t rsize_t;
#endif // __C_STD_11__

  typedef struct {
    long long   __long_long;
    long double __long_double;
  } max_align_t;

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // CAPRESE_LIBC_STDDEF_H_
