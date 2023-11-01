cmake_minimum_required(VERSION 3.20)

project(
  caprese-libc
  VERSION 0.0.1
  HOMEPAGE_URL https://github.com/caprese-project/libc
  LANGUAGES C
)

set(LIBC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/include/cxx)

add_subdirectory(src/assert)
add_subdirectory(src/complex)
add_subdirectory(src/ctype)
add_subdirectory(src/errno)
add_subdirectory(src/fenv)
add_subdirectory(src/float)
add_subdirectory(src/inttypes)
add_subdirectory(src/iso646)
add_subdirectory(src/limits)
add_subdirectory(src/locale)
add_subdirectory(src/math)
add_subdirectory(src/setjmp)
add_subdirectory(src/signal)
add_subdirectory(src/stdarg)
add_subdirectory(src/stdatomic)
add_subdirectory(src/stdbool)
add_subdirectory(src/stddef)
add_subdirectory(src/stdint)
add_subdirectory(src/stdio)
add_subdirectory(src/stdlib)
add_subdirectory(src/stdnoreturn)
add_subdirectory(src/string)
add_subdirectory(src/tgmath)
add_subdirectory(src/threads)
add_subdirectory(src/time)
add_subdirectory(src/uchar)
add_subdirectory(src/wchar)
add_subdirectory(src/wctype)

add_library(caprese_libc_freestanding INTERFACE)
target_link_libraries(
  caprese_libc_freestanding INTERFACE
  caprese_libc_float
  caprese_libc_iso646
  caprese_libc_limits
  caprese_libc_stdarg
  caprese_libc_stdbool
  caprese_libc_stddef
  caprese_libc_stdint
)

add_library(caprese_libc_hosted INTERFACE)
target_link_libraries(
  caprese_libc_hosted INTERFACE
  caprese_libc_assert
  caprese_libc_complex
  caprese_libc_ctype
  caprese_libc_errno
  caprese_libc_fenv
  caprese_libc_float
  caprese_libc_inttypes
  caprese_libc_iso646
  caprese_libc_limits
  caprese_libc_locale
  caprese_libc_math
  caprese_libc_setjmp
  caprese_libc_signal
  caprese_libc_stdarg
  caprese_libc_stdatomic
  caprese_libc_stdbool
  caprese_libc_stddef
  caprese_libc_stdint
  caprese_libc_stdio
  caprese_libc_stdlib
  caprese_libc_stdnoreturn
  caprese_libc_string
  caprese_libc_tgmath
  caprese_libc_threads
  caprese_libc_time
  caprese_libc_uchar
  caprese_libc_wchar
  caprese_libc_wctype
)

add_library(caprese_libc INTERFACE)
target_link_libraries(
  caprese_libc INTERFACE
  caprese_libc_freestanding
  caprese_libc_hosted
)

enable_testing()

install(
  TARGETS caprese_libc
  EXPORT libc-config
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
)

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION include
)
