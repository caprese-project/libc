cmake_minimum_required(VERSION 3.20)

add_library(caprese_libc_errno OBJECT)

target_sources(
  caprese_libc_errno PRIVATE
  __errno.c
)

target_compile_options(
  caprese_libc_errno PRIVATE
  ${LIBC_COMPILE_OPTIONS}
)

target_include_directories(caprese_libc_errno PUBLIC ${LIBC_INCLUDE_DIR})
