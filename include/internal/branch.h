#ifndef CAPRESE_LIBC_INTERNAL_BRANCH_H_
#define CAPRESE_LIBC_INTERNAL_BRANCH_H_

#ifdef __cplusplus

#ifdef __CXX_STD_20__
#define __if_likely(x)   if (x) [[likely]]
#define __if_unlikely(x) if (x) [[unlikely]]
#else // ^^^ __CXX_STD_20__ ^^^ / vvv !__CXX_STD_20__ vvv
#if defined(__GNUC__)
#define __if_likely(x)   if (__builtin_expect(!!(x), 1))
#define __if_unlikely(x) if (__builtin_expect(!!(x), 0))
#else // ^^^ __GNUC__ ^^^ / vvv !__GNUC__ vvv
#define __if_likely(x)   if (x)
#define __if_unlikely(x) if (x)
#endif // !__GNUC__
#endif // !__CXX_STD_20__

#else // ^^^ __cplusplus ^^^ / vvv !__cplusplus vvv

#if defined(__GNUC__)
#define __if_likely(x)   if (__builtin_expect(!!(x), 1))
#define __if_unlikely(x) if (__builtin_expect(!!(x), 0))
#else // ^^^ __GNUC__ ^^^ / vvv !__GNUC__ vvv
#define __if_likely(x)   if (x)
#define __if_unlikely(x) if (x)
#endif // !__GNUC__

#endif // !__cplusplus

#endif // CAPRESE_LIBC_INTERNAL_BRANCH_H_
