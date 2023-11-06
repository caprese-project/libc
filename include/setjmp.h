#ifndef CAPRESE_LIBC_SETJMP_H_
#define CAPRESE_LIBC_SETJMP_H_

#include <internal/attribute.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#if defined(__riscv)

  typedef long long __jmp_buf_elem_t;
#define __JMP_BUF_SIZE 14 // ra, sp, s0-s11

#else // ^^^ __riscv ^^^ / vvv !__riscv vvv

#error "Unsupported arch"

#endif // !__riscv

  typedef struct __jmp_buf {
    __jmp_buf_elem_t _buf[__JMP_BUF_SIZE];
  } jmp_buf[1];

  int             setjmp(jmp_buf env);
  __noreturn void longjmp(jmp_buf env, int val);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // CAPRESE_LIBC_SETJMP_H_
