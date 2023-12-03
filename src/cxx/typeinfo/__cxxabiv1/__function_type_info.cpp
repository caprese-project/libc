#include <internal/cxx/typeinfo/__cxxabiv1.h>

namespace __cxxabiv1 {
  __function_type_info::__function_type_info(const char* name): type_info(name) { }

  bool __function_type_info::__is_function_p() const {
    return true;
  }
} // namespace __cxxabiv1
