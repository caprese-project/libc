cmake_minimum_required(VERSION 3.20)

add_library(caprese_libc_setjmp)

target_sources(
  caprese_libc_setjmp PRIVATE
  longjmp.c
  setjmp.c
)

target_include_directories(
  caprese_libc_setjmp PUBLIC
  $<BUILD_INTERFACE:${LIBC_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:include>
)
