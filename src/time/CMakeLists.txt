cmake_minimum_required(VERSION 3.20)

add_library(caprese_libc_time)

target_sources(
  caprese_libc_time PRIVATE
  clock.c
)

target_include_directories(
  caprese_libc_time PUBLIC
  $<BUILD_INTERFACE:${LIBC_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:include>
)
