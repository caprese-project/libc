#include <internal/branch.h>
#include <internal/cxx/__cxxabi/typeinfo.h>

namespace __cxxabiv1 {
  extern "C" {
    void* __dynamic_cast(const void* src_ptr, const __class_type_info* src_type, const __class_type_info* dst_type, ptrdiff_t src2dst) {
      __if_unlikely (src_ptr == nullptr) {
        return nullptr;
      }

      const void*                         vtable     = *static_cast<const void* const*>(src_ptr);
      const vtable_prefix*                prefix     = adjust_pointer<vtable_prefix>(vtable, -ptrdiff_t(offsetof(vtable_prefix, origin)));
      const void*                         whole_ptr  = adjust_pointer<void>(src_ptr, prefix->whole_object);
      const __class_type_info*            whole_type = prefix->whole_type;
      __class_type_info::__dyncast_result result;

      const void*          whole_vtable = *static_cast<const void* const*>(whole_ptr);
      const vtable_prefix* whole_prefix = adjust_pointer<vtable_prefix>(whole_vtable, -ptrdiff_t(offsetof(vtable_prefix, origin)));

      if (whole_prefix->whole_type != whole_type) {
        return nullptr;
      }

      if (src2dst >= 0 && src2dst == -prefix->whole_object && *whole_type == *dst_type) {
        return const_cast<void*>(whole_ptr);
      }

      whole_type->__do_dyncast(src2dst, __class_type_info::__contained_public, dst_type, whole_ptr, src_type, src_ptr, result);

      if (result.dst_ptr == nullptr) {
        return nullptr;
      }

      if (contained_public_p(result.dst2src)) {
        return const_cast<void*>(result.dst_ptr);
      }

      if (contained_public_p(__class_type_info::__sub_kind(result.whole2src & result.whole2dst))) {
        return const_cast<void*>(result.dst_ptr);
      }

      if (contained_nonvirtual_p(result.whole2src)) {
        return nullptr;
      }

      if (result.dst2src == __class_type_info::__unknown) {
        result.dst2src = dst_type->__find_public_src(src2dst, result.dst_ptr, src_type, src_ptr);
      }

      if (contained_public_p(result.dst2src)) {
        return const_cast<void*>(result.dst_ptr);
      }

      return nullptr;
    }
  }
} // namespace __cxxabiv1
