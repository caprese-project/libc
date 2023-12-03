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
#define __noexcept_cxx_std_14
#endif // !__CXX_STD_14__

// __noexcept_cxx_std_17

#ifdef __CXX_STD_17__
#define __noexcept_cxx_std_17 noexcept
#else // ^^^ __CXX_STD_17__ ^^^ / vvv !__CXX_STD_17__ vvv
#define __noexcept_cxx_std_17
#endif // !__CXX_STD_17__

// __throw

#ifdef __CXX_STD_17__
#define __throw(...)
#else // ^^^ __CXX_STD_17__ ^^^ / vvv !__CXX_STD_17__ vvv
#define __throw(...) throw(__VA_ARGS__)
#endif // !__CXX_STD_17__

// __throw_cxx_std_03

#ifdef __CXX_STD_11__
#define __throw_cxx_std_03(...)
#else // ^^^ __CXX_STD_11__ ^^^ / vvv !__CXX_STD_11__ vvv
#define __throw_cxx_std_03(...) throw(__VA_ARGS__)
#endif // !__CXX_STD_11__

// __exception_enabled

#ifdef __GNUC__
#ifdef __EXCEPTIONS
#define __exception_enabled 1
#else // ^^^ __EXCEPTIONS ^^^ / vvv !__EXCEPTIONS vvv
#define __exception_enabled 0
#endif // !__EXCEPTIONS
#else  // ^^^ __GNUC__ ^^^ / vvv !__GNUC__ vvv
#define __exception_enabled 0
#endif // !__GNUC__

// __throw_exception

#if __exception_enabled
#define __throw_exception(exception) throw(exception)
#else // ^^^ __exception_enabled ^^^ / vvv !__exception_enabled vvv
#define __throw_exception(exception) abort()
#endif // !__exception_enabled

// __nodiscard

#ifdef __CXX_STD_17__
#define __nodiscard [[nodiscard]]
#else // ^^^ __CXX_STD_17__ ^^^ / vvv !__CXX_STD_17__ vvv
#ifdef __GNUC__
#define __nodiscard __attribute__((warn_unused_result))
#else // ^^^ __GNUC__ ^^^ / vvv !__GNUC__ vvv
#define __nodiscard
#endif // !__GNUC__
#endif // !__CXX_STD_17

// __nodiscard_cxx_std_20

#ifdef __CXX_STD_20__
#define __nodiscard_cxx_std_20 [[nodiscard]]
#else // ^^^ __CXX_STD_20__ ^^^ / vvv !__CXX_STD_20__ vvv
#define __nodiscard_cxx_std_20
#endif // !__CXX_STD_20__

// __deprecated

#ifdef __CXX_STD_14__
#define __deprecated [[deprecated]]
#else // ^^^ __CXX_STD_14__ ^^^ / vvv !__CXX_STD_14__ vvv
#ifdef __GNUC__
#define __deprecated __attribute__((deprecated))
#else // ^^^ __GNUC__ ^^^ / vvv !__GNUC__ vvv
#define __deprecated
#endif // !__GNUC__
#endif // !__CXX_STD_14__

// __deprecated_cxx_std_17

#ifdef __CXX_STD_17__
#define __deprecated_cxx_std_17 [[deprecated]]
#else // ^^^ __CXX_STD_17__ ^^^ / vvv !__CXX_STD_17__ vvv
#define __deprecated_cxx_std_17
#endif // !__CXX_STD_17__

// __deprecated_cxx_std_20

#ifdef __CXX_STD_20__
#define __deprecated_cxx_std_20 [[deprecated]]
#else // ^^^ __CXX_STD_20__ ^^^ / vvv !__CXX_STD_20__ vvv
#define __deprecated_cxx_std_20
#endif // !__CXX_STD_20__

// __constexpr_cxx_std_11

#ifdef __CXX_STD_11__
#define __constexpr_cxx_std_11 constexpr
#else // ^^^ __CXX_STD_11__ ^^^ / vvv !__CXX_STD_11__ vvv
#define __constexpr_cxx_std_11
#endif // !__CXX_STD_11__

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

// __noexcept_cxx_std_xx

#define __noexcept_cxx_std_14
#define __noexcept_cxx_std_17

// __throw

#define __throw(...)
#define __throw_cxx_std_03(...)

// __exception_enabled

#define __exception_enabled 0

// __throw_exception

#define __throw_exception(exception) abort()

// __nodiscard

#ifdef __GNUC__
#define __nodiscard __attribute__((warn_unused_result))
#else // ^^^ __GNUC__ ^^^ / vvv !__GNUC__ vvv
#define __nodiscard
#endif // !__GNUC__

// __nodiscard_cxx_std_xx

#define __nodiscard_cxx_std_20

// __deprecated

#ifdef __GNUC__
#define __deprecated __attribute__((deprecated))
#else // ^^^ __GNUC__ ^^^ / vvv !__GNUC__ vvv
#define __deprecated
#endif // !__GNUC__

// __deprecated_cxx_std_xx

#define __deprecated_cxx_std_17
#define __deprecated_cxx_std_20

// __constexpr_cxx_std_xx

#define __constexpr_cxx_std_11
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
