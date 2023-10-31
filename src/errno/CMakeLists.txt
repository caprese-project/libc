cmake_minimum_required(VERSION 3.20)

add_library(caprese_libc_errno)

target_sources(
  caprese_libc_errno PRIVATE
  __errno.c
)

target_include_directories(
  caprese_libc_errno PUBLIC
  $<BUILD_INTERFACE:${LIBC_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:include>
)
