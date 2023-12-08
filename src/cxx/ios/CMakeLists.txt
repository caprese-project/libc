cmake_minimum_required(VERSION 3.20)

add_library(caprese_libcxx_ios OBJECT)

target_sources(
  caprese_libcxx_ios PRIVATE
  ios_base.cpp
  manipulators.cpp
)

target_compile_options(
  caprese_libcxx_ios PRIVATE
  ${LIBC_COMPILE_OPTIONS}
)

target_include_directories(caprese_libcxx_ios PUBLIC ${LIBC_INCLUDE_DIR})
