cmake_minimum_required(VERSION 3.20)

add_library(caprese_libc_assert)

target_sources(
  caprese_libc_assert PRIVATE
  __assertion_failed.c
)

target_include_directories(caprese_libc_assert PUBLIC ${LIBC_INCLUDE_DIR})
