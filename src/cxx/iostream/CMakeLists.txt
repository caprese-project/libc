cmake_minimum_required(VERSION 3.20)

add_library(caprese_libcxx_iostream OBJECT)

target_sources(
  caprese_libcxx_iostream PRIVATE
  iostream.cpp
)

target_compile_options(
  caprese_libcxx_iostream PRIVATE
  ${LIBC_COMPILE_OPTIONS}
)

target_include_directories(caprese_libcxx_iostream PUBLIC ${LIBC_INCLUDE_DIR})
