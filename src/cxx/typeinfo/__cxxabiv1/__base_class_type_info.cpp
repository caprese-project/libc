#include <internal/cxx/typeinfo/__cxxabiv1.h>

namespace __cxxabiv1 {
  bool __base_class_type_info::__is_virtual_p() const {
    return __offset_flags & __virtual_mask;
  }

  bool __base_class_type_info::__is_public_p() const {
    return __offset_flags & __public_mask;
  }

  ptrdiff_t __base_class_type_info::__offset() const {
    return static_cast<ptrdiff_t>(__offset_flags) >> __offset_shift;
  }
} // namespace __cxxabiv1
