cmake_minimum_required(VERSION 3.20)

add_library(caprese_libc_fenv)

target_sources(
  caprese_libc_fenv PRIVATE
  feclearexcept.c
)

target_compile_options(
  caprese_libc_fenv PRIVATE
  ${LIBC_COMPILE_OPTIONS}
)

target_include_directories(caprese_libc_fenv PUBLIC ${LIBC_INCLUDE_DIR})
