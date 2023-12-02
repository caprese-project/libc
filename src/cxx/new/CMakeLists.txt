cmake_minimum_required(VERSION 3.20)

add_library(caprese_libcxx_new OBJECT)

target_sources(
  caprese_libcxx_new PRIVATE
  bad_alloc.cpp
  handler.cpp
  operator.cpp
)

target_compile_options(
  caprese_libcxx_new PRIVATE
  ${LIBC_COMPILE_OPTIONS}
)

target_include_directories(caprese_libcxx_new PUBLIC ${LIBC_INCLUDE_DIR})
