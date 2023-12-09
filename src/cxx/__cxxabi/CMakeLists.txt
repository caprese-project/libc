cmake_minimum_required(VERSION 3.20)

add_library(caprese_libcxx_cxxabi OBJECT)

target_sources(
  caprese_libcxx_cxxabi PRIVATE
  typeinfo/__array_type_info.cpp
  typeinfo/__base_class_type_info.cpp
  typeinfo/__class_type_info.cpp
  typeinfo/__dynamic_cast.cpp
  typeinfo/__enum_type_info.cpp
  typeinfo/__function_type_info.cpp
  typeinfo/__fundamental_type_info.cpp
  typeinfo/__pbase_type_info.cpp
  typeinfo/__pointer_to_member_type_info.cpp
  typeinfo/__pointer_type_info.cpp
  typeinfo/__si_class_type_info.cpp
  typeinfo/__vmi_class_type_info.cpp
  typeinfo/eh_runtime.cpp
  typeinfo/type_info.cpp
)

target_compile_options(
  caprese_libcxx_cxxabi PRIVATE
  ${LIBC_COMPILE_OPTIONS}
)

target_include_directories(caprese_libcxx_cxxabi PUBLIC ${LIBC_INCLUDE_DIR})
