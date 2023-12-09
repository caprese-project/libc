#include <internal/cxx/__cxxabi/typeinfo.h>

namespace __cxxabiv1 {
  __fundamental_type_info::__fundamental_type_info(const char* name): type_info(name) { }

  __fundamental_type_info::~__fundamental_type_info() { }
} // namespace __cxxabiv1
