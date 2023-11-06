cmake_minimum_required(VERSION 3.20)

add_library(caprese_libc_setjmp)

target_sources(
  caprese_libc_setjmp PRIVATE
  longjmp.S
  setjmp.S
)

target_compile_options(
  caprese_libc_setjmp PRIVATE
  ${LIBC_COMPILE_OPTIONS}
)

target_include_directories(caprese_libc_setjmp PUBLIC ${LIBC_INCLUDE_DIR})
