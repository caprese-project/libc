#ifndef CAPRESE_LIBC_SETJMP_H_
#define CAPRESE_LIBC_SETJMP_H_

#include <internal/attribute.h>

#if defined(__riscv)
typedef long long jmp_buf;
#else // ^^^ __riscv ^^^ / vvv !__riscv vvv
#error "Unsupported arch"
#endif // !__riscv

int             setjmp(jmp_buf env);
__noreturn void longjmp(jmp_buf env, int val);

#endif // CAPRESE_LIBC_SETJMP_H_
