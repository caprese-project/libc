cmake_minimum_required(VERSION 3.20)

add_library(caprese_libc_stdalign INTERFACE)

target_include_directories(caprese_libc_stdalign PUBLIC ${LIBC_INCLUDE_DIR})
