#ifndef CAPRESE_LIBC_STDBOOL_H_
#define CAPRESE_LIBC_STDBOOL_H_

#include <internal/version.h>

#if !defined(__cplusplus) && !defined(__C_STD_23__)
#define bool _Bool
#define true ((_Bool)1)
#define false ((_Bool)0)
#endif // !__cplusplus && !__C_STD_23__

#endif // CAPRESE_LIBC_STDBOOL_H_
