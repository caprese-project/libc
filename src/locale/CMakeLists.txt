cmake_minimum_required(VERSION 3.20)

add_library(caprese_libc_locale)

target_sources(
  caprese_libc_locale PRIVATE
  localeconv.c
  setlocale.c
)

target_include_directories(
  caprese_libc_locale PUBLIC
  $<BUILD_INTERFACE:${LIBC_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:include>
)
