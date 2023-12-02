cmake_minimum_required(VERSION 3.20)

project(
  caprese-libc
  VERSION 0.0.1
  HOMEPAGE_URL https://github.com/caprese-project/libc
  LANGUAGES CXX C ASM
)

set(
  LIBC_INCLUDE_DIR
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/cxx>
  $<INSTALL_INTERFACE:include>
)

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

add_subdirectory(src/cxx/bit)
add_subdirectory(src/cxx/exception)
add_subdirectory(src/cxx/new)
add_subdirectory(src/cxx/stdexcept)
add_subdirectory(src/cxx/typeinfo)

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
target_sources(
  caprese_libc_hosted INTERFACE
  $<TARGET_OBJECTS:caprese_libc_assert>
  $<TARGET_OBJECTS:caprese_libc_complex>
  $<TARGET_OBJECTS:caprese_libc_ctype>
  $<TARGET_OBJECTS:caprese_libc_errno>
  $<TARGET_OBJECTS:caprese_libc_fenv>
  $<TARGET_OBJECTS:caprese_libc_inttypes>
  $<TARGET_OBJECTS:caprese_libc_locale>
  $<TARGET_OBJECTS:caprese_libc_math>
  $<TARGET_OBJECTS:caprese_libc_setjmp>
  $<TARGET_OBJECTS:caprese_libc_signal>
  $<TARGET_OBJECTS:caprese_libc_stdio>
  $<TARGET_OBJECTS:caprese_libc_stdlib>
  $<TARGET_OBJECTS:caprese_libc_string>
  $<TARGET_OBJECTS:caprese_libc_threads>
  $<TARGET_OBJECTS:caprese_libc_time>
)
target_link_libraries(
  caprese_libc_hosted INTERFACE
  caprese_libc_float
  caprese_libc_iso646
  caprese_libc_limits
  caprese_libc_stdarg
  caprese_libc_stdatomic
  caprese_libc_stdbool
  caprese_libc_stddef
  caprese_libc_stdint
  caprese_libc_stdnoreturn
  caprese_libc_tgmath
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

add_library(caprese_libcxx_freestanding INTERFACE)
target_link_libraries(
  caprese_libcxx_freestanding INTERFACE
  $<TARGET_OBJECTS:caprese_libcxx_bit>
  $<TARGET_OBJECTS:caprese_libcxx_exception>
  $<TARGET_OBJECTS:caprese_libcxx_new>
  $<TARGET_OBJECTS:caprese_libcxx_typeinfo>
)

add_library(caprese_libcxx_hosted INTERFACE)
target_sources(
  caprese_libcxx_hosted INTERFACE
  $<TARGET_OBJECTS:caprese_libcxx_stdexcept>
)
target_link_libraries(
  caprese_libcxx_hosted INTERFACE
)

add_library(caprese_libcxx INTERFACE)
target_link_libraries(
  caprese_libcxx INTERFACE
  caprese_libcxx_freestanding
  caprese_libcxx_hosted
)

enable_testing()

install(
  TARGETS caprese_libc caprese_libcxx
  EXPORT libc-config
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
)

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION include
)
