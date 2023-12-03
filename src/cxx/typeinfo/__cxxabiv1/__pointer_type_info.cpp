#include <internal/cxx/typeinfo/__cxxabiv1.h>

namespace __cxxabiv1 {
  __pointer_type_info::__pointer_type_info(const char* name, int flags, const type_info* type): __pbase_type_info(name, flags, type) { }

  bool __pointer_type_info::__is_pointer_p() const {
    return true;
  }

  bool __pointer_type_info::__pointer_catch(const __pbase_type_info* thrown_type, void** thr_obj, unsigned int outer) const {
    if (outer < 2 && *__pointee == typeid(void)) {
      return !thrown_type->__pointee->__is_function_p();
    }

    return __pbase_type_info::__pointer_catch(thrown_type, thr_obj, outer);
  }
} // namespace __cxxabiv1
