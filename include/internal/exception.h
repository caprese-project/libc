#ifndef CAPRESE_LIBC_INTERNAL_EXCEPTION_H_
#define CAPRESE_LIBC_INTERNAL_EXCEPTION_H_

#include <internal/attribute.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
  __noreturn void abort() __noexcept;
#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

// __throw_exception

#if __exception_enabled
#define __throw_exception(exception) throw(exception)
#else // ^^^ __exception_enabled ^^^ / vvv !__exception_enabled vvv
#define __throw_exception(exception) abort()
#endif // !__exception_enabled

// __try

#if __exception_enabled
#define __try try
#else // ^^^ __exception_enabled ^^^ / vvv !__exception_enabled vvv
#define __try if (true)
#endif // !__exception_enabled

// __catch

#if __exception_enabled
#define __catch(...) catch (__VA_ARGS__)
#else // ^^^ __exception_enabled ^^^ / vvv !__exception_enabled vvv
#define __catch(...) if (false)
#endif // !__exception_enabled

#endif // CAPRESE_LIBC_INTERNAL_EXCEPTION_H_
