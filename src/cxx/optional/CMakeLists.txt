cmake_minimum_required(VERSION 3.20)

add_library(caprese_libcxx_optional OBJECT)

target_sources(
  caprese_libcxx_optional PRIVATE
  bad_optional_access.cpp
)

target_compile_options(
  caprese_libcxx_optional PRIVATE
  ${LIBC_COMPILE_OPTIONS}
)

target_include_directories(caprese_libcxx_optional PUBLIC ${LIBC_INCLUDE_DIR})
