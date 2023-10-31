#include <internal/attribute.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef __ASSERT_FUNCTION
#if defined(__GNUC__) && defined(__cplusplus)
#define __ASSERT_FUNCTION __PRETTY_FUNCTION__
#else
#define __ASSERT_FUNCTION __func__
#endif // defined(__GNUC__) && defined(__cplusplus)
#endif // __ASSERT_FUNCTION

#undef assert

#ifdef NDEBUG
#define assert(cond) ((void)0)
#else
#define assert(cond) ((cond) ? (void)0 : __assertion_failed(__FILE__, __LINE__, __ASSERT_FUNCTION, #cond))
#endif // NDEBUG

  __noreturn void __assertion_failed(const char* file, int line, const char* function, const char* condition);

#ifndef __cplusplus
#define static_assert _Static_assert
#endif // __cplusplus

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
