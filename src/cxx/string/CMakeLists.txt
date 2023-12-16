cmake_minimum_required(VERSION 3.20)

add_library(caprese_libcxx_string OBJECT)

target_sources(
  caprese_libcxx_string PRIVATE
  stox.cpp
)

target_compile_options(
  caprese_libcxx_string PRIVATE
  ${LIBC_COMPILE_OPTIONS}
)

target_include_directories(caprese_libcxx_string PUBLIC ${LIBC_INCLUDE_DIR})
