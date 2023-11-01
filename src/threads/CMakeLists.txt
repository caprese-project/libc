cmake_minimum_required(VERSION 3.20)

add_library(caprese_libc_threads)

target_sources(
  caprese_libc_threads PRIVATE
  call_once.c
)

target_include_directories(caprese_libc_threads PUBLIC ${LIBC_INCLUDE_DIR})
