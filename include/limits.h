#ifndef CAPRESE_LIBC_LIMITS_H_
#define CAPRESE_LIBC_LIMITS_H_

#undef CHAR_BIT
#undef SCHAR_MIN
#undef SCHAR_MAX
#undef UCHAR_MAX
#undef CHAR_MIN
#undef CHAR_MAX
#undef SHRT_MIN
#undef SHRT_MAX
#undef USHRT_MAX
#undef INT_MIN
#undef INT_MAX
#undef UINT_MAX
#undef LONG_MIN
#undef LONG_MAX
#undef ULONG_MAX
#undef LLONG_MIN
#undef LLONG_MAX
#undef ULLONG_MAX

#ifdef __GNUC__

#define CHAR_BIT  __CHAR_BIT__
#define SCHAR_MAX __SCHAR_MAX__
#define SHRT_MAX  __SHRT_MAX__
#define INT_MAX   __INT_MAX__
#define LONG_MAX  __LONG_MAX__
#define LLONG_MAX __LONG_LONG_MAX__

#ifdef __CHAR_UNSIGNED__
#define CHAR_MIN 0
#define CHAR_MAX UCHAR_MAX
#else // ^^^ __CHAR_UNSIGNED__ ^^^ / vvv !__CHAR_UNSIGNED__ vvv
#define CHAR_MIN SCHAR_MIN
#define CHAR_MAX SCHAR_MAX
#endif // !__CHAR_UNSIGNED__

#else // ^^^ __GNUC__ ^^^ / vvv !__GNUC__ vvv

#warning "Using an unrecognized compiler. Constants in limits.h will fallback to default values."

#include <internal/datamodel.h>

#define CHAR_BIT  8
#define SCHAR_MAX 0x7f
#define SHRT_MAX  0x7fff
#define INT_MAX   0x7fffffff

#if defined(__LP64)
#define LONG_MAX  0x7fffffffffffffffl
#define LLONG_MAX 0x7fffffffffffffffll
#elif defined(__ILP32)
#define LONG_MAX  0x7fffffffl
#define LLONG_MAX 0x7fffffffffffffffll
#else
#define LONG_MAX  0x7fffffffffffffffl
#define LLONG_MAX 0x7fffffffffffffffll
#endif

#endif // !__GNUC__

#define SCHAR_MIN (-SCHAR_MAX - 1)
#define UCHAR_MAX (SCHAR_MAX * 2 + 1)

#define SHRT_MIN  (-SHRT_MAX - 1)
#define USHRT_MAX (SHRT_MAX * 2 + 1)

#define INT_MIN  (-INT_MAX - 1)
#define UINT_MAX (INT_MAX * 2u + 1u)

#define LONG_MIN  (-LONG_MAX - 1l)
#define ULONG_MAX (LONG_MAX * 2ul + 1ul)

#define LLONG_MIN  (-LLONG_MAX - 1ll)
#define ULLONG_MAX (LLONG_MAX * 2ull + 1ull)

#endif // CAPRESE_LIBC_LIMITS_H_
