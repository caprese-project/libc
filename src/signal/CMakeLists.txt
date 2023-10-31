cmake_minimum_required(VERSION 3.20)

add_library(caprese_libc_signal)

target_sources(
  caprese_libc_signal PRIVATE
  raise.c
  signal.c
)

target_include_directories(
  caprese_libc_signal PUBLIC
  $<BUILD_INTERFACE:${LIBC_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:include>
)
