cmake_minimum_required(VERSION 3.20)

add_library(caprese_libc_inttypes)

target_sources(
  caprese_libc_inttypes PRIVATE
  imaxabs.c
  imaxdiv.c
  strtoimax.c
  strtoumax.c
  wcstoimax.c
  wcstoumax.c
)

target_compile_options(
  caprese_libc_inttypes PRIVATE
  ${LIBC_COMPILE_OPTIONS}
)

target_include_directories(caprese_libc_inttypes PUBLIC ${LIBC_INCLUDE_DIR})
