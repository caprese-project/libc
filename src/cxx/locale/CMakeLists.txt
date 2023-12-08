cmake_minimum_required(VERSION 3.20)

add_library(caprese_libcxx_locale OBJECT)

target_sources(
  caprese_libcxx_locale PRIVATE
  ctype.cpp
  locale.cpp
)

target_compile_options(
  caprese_libcxx_locale PRIVATE
  ${LIBC_COMPILE_OPTIONS}
)

target_include_directories(caprese_libcxx_locale PUBLIC ${LIBC_INCLUDE_DIR})
