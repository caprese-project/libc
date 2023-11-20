cmake_minimum_required(VERSION 3.20)

add_library(caprese_libc_math OBJECT)

target_sources(
  caprese_libc_math PRIVATE
  acos.c
)

target_compile_options(
  caprese_libc_math PRIVATE
  ${LIBC_COMPILE_OPTIONS}
)

target_include_directories(caprese_libc_math PUBLIC ${LIBC_INCLUDE_DIR})
