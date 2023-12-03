cmake_minimum_required(VERSION 3.20)

add_library(caprese_libcxx_typeinfo OBJECT)

target_sources(
  caprese_libcxx_typeinfo PRIVATE
  exception.cpp
  __cxxabiv1/__array_type_info.cpp
  __cxxabiv1/__base_class_type_info.cpp
  __cxxabiv1/__class_type_info.cpp
  __cxxabiv1/__enum_type_info.cpp
  __cxxabiv1/__function_type_info.cpp
  __cxxabiv1/__fundamental_type_info.cpp
  __cxxabiv1/__pbase_type_info.cpp
  __cxxabiv1/__pointer_to_member_type_info.cpp
  __cxxabiv1/__pointer_type_info.cpp
  __cxxabiv1/__si_class_type_info.cpp
  __cxxabiv1/__vmi_class_type_info.cpp
  __cxxabiv1/eh_runtime.cpp
  __cxxabiv1/type_info.cpp
)

target_compile_options(
  caprese_libcxx_typeinfo PRIVATE
  ${LIBC_COMPILE_OPTIONS}
)

target_include_directories(caprese_libcxx_typeinfo PUBLIC ${LIBC_INCLUDE_DIR})
