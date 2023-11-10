#ifndef CAPRESE_LIBC_INTERNAL_ATTRIBUTE_H_
#define CAPRESE_LIBC_INTERNAL_ATTRIBUTE_H_

#include <internal/version.h>

#ifdef __cplusplus

// __noreturn

#ifdef __CXX_STD_11__
#define __noreturn [[noreturn]]
#else // ^^^ __CXX_STD_11__ ^^^ / vvv !__CXX_STD_11__ vvv
#ifdef __GNUC__
#define __noreturn __attribute__((__noreturn__))
#else // ^^^ __GNUC__ ^^^ / vvv !__GNUC__ vvv
#define __noreturn
#endif // !__GNUC__

#endif // !__CXX_STD_11__

// __force_inline

#ifdef __GNUC__
#define __force_inline [[__gnu__::__always_inline__]] inline
#else // ^^^ __GNUC__ ^^^ / vvv !__GNUC__ vvv
#define __force_inline inline
#endif // !__GNUC__

// __restrict

#ifdef __GNUC__
#define __restrict __restrict__
#else // ^^^ __GNUC__ ^^^ / vvv !__GNUC__ vvv
#define __restrict
#endif // !__GNUC__

// __unused

#ifdef __CXX_STD_17__
#define __unused [[maybe_unused]]
#else // ^^^ __CXX_STD_17__ ^^^ / vvv !__CXX_STD_17__ vvv
#ifdef __GNUC__
#define __unused __attribute__((unused))
#else // ^^^ __GNUC__ ^^^ / vvv !__GNUC__ vvv
#define __unused
#endif // !__GNUC__
#endif // !__CXX_STD_17__

// __noexcept

#ifdef __CXX_STD_11__
#define __noexcept noexcept
#else // ^^^ __CXX_STD_11__ ^^^ / vvv !__CXX_STD_11__ vvv
#define __noexcept throw()
#endif // !__CXX_STD_11__

// __noexcept_cxx_std_14

#ifdef __CXX_STD_14__
#define __noexcept_cxx_std_14 noexcept
#else // ^^^ __CXX_STD_14__ ^^^ / vvv !__CXX_STD_14__ vvv
#define __noexcept
#endif // !__CXX_STD_14__

// __constexpr_cxx_std_14

#ifdef __CXX_STD_14__
#define __constexpr_cxx_std_14 constexpr
#else // ^^^ __CXX_STD_14__ ^^^ / vvv !__CXX_STD_14__ vvv
#define __constexpr_cxx_std_14
#endif // !__CXX_STD_14__

// __constexpr_cxx_std_17

#ifdef __CXX_STD_17__
#define __constexpr_cxx_std_17 constexpr
#else // ^^^ __CXX_STD_17__ ^^^ / vvv !__CXX_STD_17__ vvv
#define __constexpr_cxx_std_17
#endif // !__CXX_STD_17__

// __constexpr_cxx_std_20

#ifdef __CXX_STD_20__
#define __constexpr_cxx_std_20 constexpr
#else // ^^^ __CXX_STD_20__ ^^^ / vvv !__CXX_STD_20__ vvv
#define __constexpr_cxx_std_20
#endif // !__CXX_STD_20__

#else // ^^^ __cplusplus ^^^ / vvv !__cplusplus

// __noreturn

#ifdef __C_STD_11__
#define __noreturn _Noreturn
#else // ^^^ __C_STD_11__ ^^^ / vvv !__C_STD_11__ vvv
#ifdef __GNUC__
#define __noreturn __attribute__((__noreturn__))
#else // ^^^ __GNUC__ ^^^ / vvv !__GNUC__ vvv
#define __noreturn
#endif // !__GNUC__
#endif // !__C_STD_11__

// __force_inline
#ifdef __GNUC__
#define __force_inline __attribute__((always_inline)) inline
#else // ^^^ __GNUC__ ^^^ / vvv !__GNUC__ vvv
#define __force_inline inline
#endif // !__GNUC__

// __restrict

#ifdef __C_STD_99__
#define __restrict restrict
#else // ^^^ __C_STD_99__ ^^^ / vvv !__C_STD_99__ vvv
#ifdef __GNUC__
#define __restrict __restrict__
#else // ^^^ __GNUC__ ^^^ / vvv !__GNUC__ vvv
#define __restrict
#endif // !__GNUC__
#endif // !__C_STD_99__

// __unused

#ifdef __GNUC__
#define __unused __attribute__((unused))
#else // ^^^ __GNUC__ ^^^ / vvv !__GNUC__ vvv
#define __unused
#endif // !__GNUC__

// __noexcept

#define __noexcept

// __constexpr_cxx_std_xx

#define __constexpr_cxx_std_14
#define __constexpr_cxx_std_17
#define __constexpr_cxx_std_20

#endif // !__cplusplus

// __weak

#ifdef __GNUC__
#define __weak __attribute__((weak))
#else // ^^^ __GNUC__ ^^^ / vvv !__GNUC__ vvv
#define __weak
#endif // !__GNUC__

// __naked

#ifdef __GNUC__
#define __naked __attribute__((naked))
#else // ^^^ __GNUC__ ^^^ / vvv !__GNUC__ vvv
#define __naked
#endif // !__GNUC__

#endif // CAPRESE_LIBC_INTERNAL_ATTRIBUTE_H_
