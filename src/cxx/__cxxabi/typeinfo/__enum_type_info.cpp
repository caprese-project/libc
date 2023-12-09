#include <internal/cxx/__cxxabi/typeinfo.h>

namespace __cxxabiv1 {
  __enum_type_info::__enum_type_info(const char* name): type_info(name) { }

  __enum_type_info::~__enum_type_info() { }
} // namespace __cxxabiv1
