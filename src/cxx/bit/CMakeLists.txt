cmake_minimum_required(VERSION 3.20)

add_library(caprese_libcxx_bit OBJECT)

target_sources(
  caprese_libcxx_bit PRIVATE
  __bswapdi2.c
  __bswapsi2.c
  __ctzdi2.c
  __popcountdi2.c
  __popcountsi2.c
)

target_compile_options(
  caprese_libcxx_bit PRIVATE
  ${LIBC_COMPILE_OPTIONS}
)

target_include_directories(caprese_libcxx_bit PUBLIC ${LIBC_INCLUDE_DIR})
