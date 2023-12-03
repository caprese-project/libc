#include <internal/attribute.h>
#include <internal/cxx/new/bad_alloc.h>
#include <internal/cxx/typeinfo/__cxxabiv1.h>
#include <internal/cxx/typeinfo/exception.h>

namespace __cxxabiv1 {
  extern "C" {
    __noreturn void __cxa_bad_cast() {
      __throw_exception(::std::bad_cast());
    }

    __noreturn void __cxa_bad_typeid() {
      __throw_exception(::std::bad_typeid());
    }

    __noreturn void __cxa_throw_bad_array_new_length() {
      __throw_exception(::std::bad_array_new_length());
    }
  }
} // namespace __cxxabiv1
