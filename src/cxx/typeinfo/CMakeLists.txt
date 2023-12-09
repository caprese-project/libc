cmake_minimum_required(VERSION 3.20)

add_library(caprese_libcxx_typeinfo OBJECT)

target_sources(
  caprese_libcxx_typeinfo PRIVATE
  exception.cpp
)

target_compile_options(
  caprese_libcxx_typeinfo PRIVATE
  ${LIBC_COMPILE_OPTIONS}
)

target_include_directories(caprese_libcxx_typeinfo PUBLIC ${LIBC_INCLUDE_DIR})
