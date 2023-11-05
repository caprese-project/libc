#ifndef CAPRESE_LIBC_STDBOOL_H_
#define CAPRESE_LIBC_STDBOOL_H_

#include <internal/version.h>

#if !defined(__cplusplus) && !defined(__C_STD_23__)
#define bool _Bool
#define true ((_Bool)1)
#define false ((_Bool)0)
#endif // !__cplusplus && !__C_STD_23__

#ifdef __cplusplus
#define _Bool bool
#endif // __cplusplus

#endif // CAPRESE_LIBC_STDBOOL_H_
