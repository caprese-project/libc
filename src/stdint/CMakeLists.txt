cmake_minimum_required(VERSION 3.20)

add_library(caprese_libc_stdint INTERFACE)

target_include_directories(caprese_libc_stdint INTERFACE ${LIBC_INCLUDE_DIR})
