cmake_minimum_required(VERSION 3.20)

add_library(caprese_libc_threads OBJECT)

target_sources(
  caprese_libc_threads PRIVATE
  call_once.c
)

target_compile_options(
  caprese_libc_threads PRIVATE
  ${LIBC_COMPILE_OPTIONS}
)

target_include_directories(caprese_libc_threads PUBLIC ${LIBC_INCLUDE_DIR})
