#ifndef CAPRESE_LIBC_INTERNAL_UNREACHABLE_H_
#define CAPRESE_LIBC_INTERNAL_UNREACHABLE_H_

#include <internal/version.h>

#ifdef __cplusplus

#ifdef __CXX_STD_23__
namespace std {
  [[noreturn]] void unreachable();
} // namespace std

#define __unreachable() ::std::unreachable()
#else  // ^^^ __CXX_STD_23__ ^^^ / vvv !__CXX_STD_23__ vvv
#ifdef __GNUC__
#define __unreachable() __builtin_unreachable()
#else  // ^^^ __GNUC__ ^^^ / vvv !__GNUC__ vvv
#define __unreachable() abort()
#endif // !__GNUC__
#endif // !__CXX_STD_23__

#else  // ^^^ __cplusplus ^^^ / vvv !__cplusplus vvv

#ifdef __GNUC__
#define __unreachable() __builtin_unreachable()
#else  // ^^^ __GNUC__ ^^^ / vvv !__GNUC__ vvv
#define __unreachable() abort()
#endif // !__GNUC__

#endif // !__cplusplus

#endif // CAPRESE_LIBC_INTERNAL_UNREACHABLE_H_
