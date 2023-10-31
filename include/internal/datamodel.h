#ifndef CAPRESE_LIBC_INTERNAL_DATAMODEL_H_
#define CAPRESE_LIBC_INTERNAL_DATAMODEL_H_

#if defined(__riscv)

#if __riscv_xlen == 64
#define __LP64
#elif __riscv_xlen == 32
#define __ILP32
#else
#error "Unsupported riscv xlen"
#endif // __riscv_xlen

#else // ^^^ __riscv ^^^ / vvv !__riscv vvv

#error "Unsupported architecture"

#endif // !__riscv

#endif // CAPRESE_LIBC_INTERNAL_DATAMODEL_H_
