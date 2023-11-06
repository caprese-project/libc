.section .text

.global longjmp
.type longjmp, @function

#if defined(__riscv)
.balign 4
longjmp:
  ld ra, 0(a0)
  ld sp, 8(a0)
  ld s0, 16(a0)
  ld s1, 24(a0)
  ld s2, 32(a0)
  ld s3, 40(a0)
  ld s4, 48(a0)
  ld s5, 56(a0)
  ld s6, 64(a0)
  ld s7, 72(a0)
  ld s8, 80(a0)
  ld s9, 88(a0)
  ld s10, 96(a0)
  ld s11, 104(a0)

  # return a1 == 0 ? 1 : a1
  seqz a0, a1
  add a0, a0, a1
  ret
#else
#error "Unsupported arch"
#endif
