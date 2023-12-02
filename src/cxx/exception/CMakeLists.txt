cmake_minimum_required(VERSION 3.20)

add_library(caprese_libcxx_exception OBJECT)

target_sources(
  caprese_libcxx_exception PRIVATE
  bad_exception.cpp
  exception.cpp
  terminate.cpp
)

target_compile_options(
  caprese_libcxx_exception PRIVATE
  ${LIBC_COMPILE_OPTIONS}
)

target_include_directories(caprese_libcxx_exception PUBLIC ${LIBC_INCLUDE_DIR})
