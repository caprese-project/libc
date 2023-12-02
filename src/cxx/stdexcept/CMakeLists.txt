cmake_minimum_required(VERSION 3.20)

add_library(caprese_libcxx_stdexcept OBJECT)

target_sources(
  caprese_libcxx_stdexcept PRIVATE
  logic_error.cpp
  runtime_error.cpp
)

target_compile_options(
  caprese_libcxx_stdexcept PRIVATE
  ${LIBC_COMPILE_OPTIONS}
)

target_include_directories(caprese_libcxx_stdexcept PUBLIC ${LIBC_INCLUDE_DIR})
