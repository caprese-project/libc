cmake_minimum_required(VERSION 3.20)

add_library(caprese_libc_stdlib OBJECT)

target_sources(
  caprese_libc_stdlib PRIVATE
  __alloc.c
  _Exit.c
  abort.c
  abs.c
  aligned_alloc.c
  at_quick_exit.c
  atexit.c
  atof.c
  atoi.c
  atol.c
  atoll.c
  calloc.c
  div.c
  exit.c
  free.c
  ldiv.c
  lldiv.c
  malloc.c
  quick_exit.c
  realloc.c
  strtod.c
  strtof.c
  strtol.c
  strtold.c
  strtoll.c
  strtoul.c
  strtoull.c
)

target_compile_options(
  caprese_libc_stdlib PRIVATE
  ${LIBC_COMPILE_OPTIONS}
)

target_include_directories(caprese_libc_stdlib PUBLIC ${LIBC_INCLUDE_DIR})
