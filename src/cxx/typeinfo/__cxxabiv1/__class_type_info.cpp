#include <internal/cxx/typeinfo/__cxxabiv1.h>

namespace __cxxabiv1 {
  __class_type_info::__class_type_info(const char* name): type_info(name) { }

  bool __class_type_info::__do_upcast(const __class_type_info* dst_type, void** obj_ptr) const {
    __upcast_result result(__vmi_class_type_info::__flags_unknown_mask);

    __do_upcast(dst_type, *obj_ptr, result);

    if (!contained_public_p(result.part2dst)) {
      return false;
    }

    *obj_ptr = const_cast<void*>(result.dst_ptr);

    return true;
  }

  bool __class_type_info::__do_catch(const type_info* thr_type, void** thr_obj, unsigned int outer) const {
    if (*this == *thr_type) {
      return true;
    }

    if (outer >= 4) {
      return false;
    }

    return thr_type->__do_upcast(this, thr_obj);
  }

  bool __class_type_info::__do_upcast(const __class_type_info* dst, const void* obj, __upcast_result& __restrict result) const {
    if (*this == *dst) {
      result.dst_ptr   = obj;
      result.base_type = nonvirtual_base_type;
      result.part2dst  = __contained_public;
      return true;
    }

    return false;
  }

  __class_type_info::__sub_kind __class_type_info::__find_public_src(ptrdiff_t src2dst, const void* obj_ptr, const __class_type_info* src_type, const void* src_ptr) const {
    if (src2dst >= 0) {
      return adjust_pointer<void>(obj_ptr, src2dst) == src_ptr ? __contained_public : __not_contained;
    }
    if (src2dst == -2) {
      return __not_contained;
    }

    return __do_find_public_src(src2dst, obj_ptr, src_type, src_ptr);
  }

  bool __class_type_info::__do_dyncast(
      ptrdiff_t, __sub_kind access_path, const __class_type_info* dst_type, const void* obj_ptr, const __class_type_info* src_type, const void* src_ptr, __dyncast_result& __restrict result) const {
    if (obj_ptr == src_ptr && *this == *src_type) {
      result.whole2src = access_path;
      return false;
    }

    if (*this == *dst_type) {
      result.dst_ptr   = obj_ptr;
      result.whole2dst = access_path;
      result.dst2src   = __not_contained;
      return false;
    }

    return true;
  }

  __class_type_info::__sub_kind __class_type_info::__do_find_public_src(ptrdiff_t, const void* obj_ptr, const __class_type_info*, const void* src_ptr) const {
    if (src_ptr == obj_ptr) {
      return __contained_public;
    }
    return __not_contained;
  }

  __class_type_info::__upcast_result::__upcast_result(int details): dst_ptr(nullptr), part2dst(__unknown), src_details(details), base_type(nullptr) { }

  __class_type_info::__dyncast_result::__dyncast_result(int details): dst_ptr(nullptr), whole2dst(__unknown), whole2src(__unknown), dst2src(__unknown), whole_details(details) { }
} // namespace __cxxabiv1
