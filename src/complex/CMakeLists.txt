cmake_minimum_required(VERSION 3.20)

add_library(caprese_libc_complex OBJECT)

target_sources(
  caprese_libc_complex PRIVATE
  cacos.c
)

target_compile_options(
  caprese_libc_complex PRIVATE
  ${LIBC_COMPILE_OPTIONS}
)

target_include_directories(caprese_libc_complex PUBLIC ${LIBC_INCLUDE_DIR})
