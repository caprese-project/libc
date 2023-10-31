cmake_minimum_required(VERSION 3.20)

add_library(caprese_libc_stdlib)

target_sources(
  caprese_libc_stdlib PRIVATE
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
  exit.c
  free.c
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

target_include_directories(
  caprese_libc_stdlib PUBLIC
  $<BUILD_INTERFACE:${LIBC_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:include>
)
