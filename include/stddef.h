#ifndef CAPRESE_LIBC_STDDEF_H_
#define CAPRESE_LIBC_STDDEF_H_

#include <internal/datamodel.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef __cplusplus
#define NULL ((void*)0)
#else
#define NULL 0
#endif // __cplusplus

#ifdef __GNUC__
#define offsetof(type, member) __builtin_offsetof(type, member)
#else
#define offsetof(type, member) ((size_t) & ((type*)0)->member)
#endif // __GNUC__

#if defined(__LP64)
  typedef long          ptrdiff_t;
  typedef unsigned long size_t;
  typedef long          ssize_t;
#elif defined(__ILP32)
  typedef int          ptrdiff_t;
  typedef unsigned int size_t;
  typedef int          ssize_t;
#endif // defined(data-model)

  typedef int    errno_t;
  typedef size_t rsize_t;

  typedef struct {
    long long   __long_long;
    long double __long_double;
  } max_align_t;

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // CAPRESE_LIBC_STDDEF_H_
