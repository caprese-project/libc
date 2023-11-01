cmake_minimum_required(VERSION 3.20)

add_library(caprese_libc_string)

target_sources(
  caprese_libc_string PRIVATE
  memchr.c
  memcmp.c
  memcpy.c
  memmove.c
  memset.c
  strcat.c
  strchr.c
  strcmp.c
  strcpy.c
  strcspn.c
  strerror.c
  strlen.c
  strncat.c
  strncmp.c
  strncpy.c
  strpbrk.c
  strrchr.c
  strspn.c
  strstr.c
  strtok.c
)

target_include_directories(caprese_libc_string PUBLIC ${LIBC_INCLUDE_DIR})
