cmake_minimum_required(VERSION 3.20)

add_library(caprese_libc_stdbool INTERFACE)

target_include_directories(
  caprese_libc_stdbool INTERFACE
  $<BUILD_INTERFACE:${LIBC_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:include>
)
