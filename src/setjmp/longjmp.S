.section .text

.global longjmp
.type longjmp, @function

#if defined(__riscv)
.balign 4
longjmp:
  ld 0(a0), ra
  ld 8(a0), sp
  ld 16(a0), s0
  ld 24(a0), s1
  ld 32(a0), s2
  ld 40(a0), s3
  ld 48(a0), s4
  ld 56(a0), s5
  ld 64(a0), s6
  ld 72(a0), s7
  ld 80(a0), s8
  ld 88(a0), s9
  ld 96(a0), s10
  ld 104(a0), s11

  # return a1 == 0 ? 1 : a1
  seqz a0, a1
  add a0, a0, a1
  ret
#else
#error "Unsupported arch"
#endif
