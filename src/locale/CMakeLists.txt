cmake_minimum_required(VERSION 3.20)

add_library(caprese_libc_locale OBJECT)

target_sources(
  caprese_libc_locale PRIVATE
  localeconv.c
  setlocale.c
)

target_compile_options(
  caprese_libc_locale PRIVATE
  ${LIBC_COMPILE_OPTIONS}
)

target_include_directories(caprese_libc_locale PUBLIC ${LIBC_INCLUDE_DIR})
