#ifndef CAPRESE_LIBC_WCHAR_H_
#define CAPRESE_LIBC_WCHAR_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  struct mbstate_t {
    uint64_t _buffer;
  };

#ifndef __cplusplus
  typedef unsigned short wchar_t;
#endif // __cplusplus

  typedef wchar_t wint_t;

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // CAPRESE_LIBC_WCHAR_H_
