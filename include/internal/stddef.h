#ifndef CAPRESE_LIBC_INTERNAL_STDDEF_H_
#define CAPRESE_LIBC_INTERNAL_STDDEF_H_

#include <internal/datamodel.h>

#if defined(__LP64)

#define __PTRDIFF_TYPE long
#define __SIZE_TYPE    unsigned long
#define __SSIZE_TYPE   long

#elif defined(__ILP32)

#define __PTRDIFF_TYPE int
#define __SIZE_TYPE    unsigned int
#define __SSIZE_TYPE   int

#endif

#endif // CAPRESE_LIBC_INTERNAL_STDDEF_H_
