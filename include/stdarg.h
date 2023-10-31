#ifndef CAPRESE_LIBC_STDARG_H_
#define CAPRESE_LIBC_STDARG_H_

#include <internal/version.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef __GNUC__

  typedef __builtin_va_list va_list;

#define va_start(v, l) __builtin_va_start(v, l)
#define va_end(v)      __builtin_va_end(v)
#define va_arg(v, l)   __builtin_va_arg(v, l)

#if defined(__C_STD_99__) || defined(__CXX_STD_11__)
#define va_copy(d, s) __builtin_va_copy(d, s)
#endif // __C_STD_99__ || __CXX_STD_11__

#else // ^^^ __GNUC__ ^^^ / vvv !__GNUC__ vvv

#error "The header file 'stdarg.h' is not yet implemented in this libc version."

#endif // !__GNUC__

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // CAPRESE_LIBC_STDARG_H_
