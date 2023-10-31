#ifndef CAPRESE_LIBC_SETJMP_H_
#define CAPRESE_LIBC_SETJMP_H_

#include <internal/attribute.h>

int             setjmp(jmp_buf env);
__noreturn void longjmp(jmp_buf env, int val);

#endif // CAPRESE_LIBC_SETJMP_H_
