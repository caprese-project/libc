cmake_minimum_required(VERSION 3.20)

add_library(caprese_libc_ctype)

target_sources(
  caprese_libc_ctype PRIVATE
  __ctype_table.c
  isalnum.c
  isalpha.c
  isblank.c
  iscntrl.c
  isdigit.c
  isgraph.c
  islower.c
  isprint.c
  ispunct.c
  isspace.c
  isupper.c
  isxdigit.c
  tolower.c
  toupper.c
)

target_include_directories(caprese_libc_ctype PUBLIC ${LIBC_INCLUDE_DIR})
