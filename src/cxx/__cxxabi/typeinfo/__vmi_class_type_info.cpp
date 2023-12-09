#include <internal/cxx/__cxxabi/typeinfo.h>

namespace __cxxabiv1 {
  __vmi_class_type_info::__vmi_class_type_info(const char* name, int flags): __class_type_info(name), __flags(flags), __base_count(0) { }

  __vmi_class_type_info::~__vmi_class_type_info() { }

  bool __vmi_class_type_info::__do_dyncast(ptrdiff_t                src2dst,
                                           __sub_kind               access_path,
                                           const __class_type_info* dst_type,
                                           const void*              obj_ptr,
                                           const __class_type_info* src_type,
                                           const void*              src_ptr,
                                           __dyncast_result& __restrict result) const {
    if (result.whole_details & __flags_unknown_mask) {
      result.whole_details = __flags;
    }

    if (obj_ptr == src_ptr && *this == *src_type) {
      result.whole2src = access_path;
      return false;
    }
    if (*this == *dst_type) {
      result.dst_ptr   = obj_ptr;
      result.whole2dst = access_path;

      if (src2dst >= 0) {
        result.dst2src = adjust_pointer<void>(obj_ptr, src2dst) == src_ptr ? __contained_public : __not_contained;
      } else if (src2dst == -2) {
        result.dst2src = __not_contained;
      }

      return false;
    }

    const void* dst_cand = nullptr;

    if (src2dst >= 0) {
      dst_cand = adjust_pointer<void>(src_ptr, -src2dst);
    }

    bool first_pass = true;
    bool skipped    = false;

    bool result_ambig = false;

    while (true) {
      for (std::size_t i = __base_count; i--;) {
        __dyncast_result result2(result.whole_details);
        const void*      base        = obj_ptr;
        __sub_kind       base_access = access_path;
        ptrdiff_t        offset      = __base_info[i].__offset();
        bool             is_virtual  = __base_info[i].__is_virtual_p();

        if (is_virtual) {
          base_access = __sub_kind(base_access | __contained_virtual_mask);
        }

        base = convert_to_base(base, is_virtual, offset);

        if (dst_cand) {
          bool skip_on_first_pass = base > dst_cand;
          if (skip_on_first_pass == first_pass) {
            skipped = true;
            continue;
          }
        }

        if (!__base_info[i].__is_public_p()) {
          if (src2dst == -2 && !(result.whole_details & (__non_diamond_repeat_mask | __diamond_shaped_mask))) {
            continue;
          }

          base_access = __sub_kind(base_access & ~__contained_public_mask);
        }

        bool result2_ambig = __base_info[i].__base_type->__do_dyncast(src2dst, base_access, dst_type, base, src_type, src_ptr, result2);
        result.whole2src   = __sub_kind(result.whole2src | result2.whole2src);

        if (result2.dst2src == __contained_public || result2.dst2src == __contained_ambig) {
          result.dst_ptr   = result2.dst_ptr;
          result.whole2dst = result2.whole2dst;
          result.dst2src   = result2.dst2src;
          return result2_ambig;
        }

        if (!result_ambig && !result.dst_ptr) {
          result.dst_ptr   = result2.dst_ptr;
          result.whole2dst = result2.whole2dst;
          result_ambig     = result2_ambig;

          if (result.dst_ptr && result.whole2src != __unknown && !(__flags & __non_diamond_repeat_mask)) {
            return result_ambig;
          }
        } else if (result.dst_ptr && result.dst_ptr == result2.dst_ptr) {
          result.whole2dst = __sub_kind(result.whole2dst | result2.whole2dst);
        } else if ((result.dst_ptr != 0 && result2.dst_ptr != 0) || (result.dst_ptr != 0 && result2_ambig) || (result2.dst_ptr != 0 && result_ambig)) {
          __sub_kind new_sub_kind = result2.dst2src;
          __sub_kind old_sub_kind = result.dst2src;

          if (contained_p(result.whole2src) && (!virtual_p(result.whole2src) || !(result.whole_details & __diamond_shaped_mask))) {
            if (old_sub_kind == __unknown) {
              old_sub_kind = __not_contained;
            }
            if (new_sub_kind == __unknown) {
              new_sub_kind = __not_contained;
            }
          } else {
            if (old_sub_kind >= __not_contained) {
            } else if (contained_p(new_sub_kind) && (!virtual_p(new_sub_kind) || !(__flags & __diamond_shaped_mask))) {
              old_sub_kind = __not_contained;
            } else {
              old_sub_kind = dst_type->__find_public_src(src2dst, result.dst_ptr, src_type, src_ptr);
            }

            if (new_sub_kind >= __not_contained) {
            } else if (contained_p(old_sub_kind) && (!virtual_p(old_sub_kind) || !(__flags & __diamond_shaped_mask))) {
              new_sub_kind = __not_contained;
            } else {
              new_sub_kind = dst_type->__find_public_src(src2dst, result2.dst_ptr, src_type, src_ptr);
            }
          }

          if (contained_p(__sub_kind(new_sub_kind ^ old_sub_kind))) {
            if (contained_p(new_sub_kind)) {
              result.dst_ptr   = result2.dst_ptr;
              result.whole2dst = result2.whole2dst;
              result_ambig     = false;
              old_sub_kind     = new_sub_kind;
            }
            result.dst2src = old_sub_kind;
            if (public_p(result.dst2src)) {
              return false;
            }
            if (!virtual_p(result.dst2src)) {
              return false;
            }
          } else if (contained_p(__sub_kind(new_sub_kind & old_sub_kind))) {
            result.dst_ptr = nullptr;
            result.dst2src = __contained_ambig;
            return true;
          } else {
            result.dst_ptr = nullptr;
            result.dst2src = __not_contained;
            result_ambig   = true;
          }
        }

        if (result.whole2src == __contained_private) {
          return result_ambig;
        }
      }

      if (skipped && first_pass) {
        first_pass = false;
      } else {
        break;
      }
    }

    return result_ambig;
  }

  __vmi_class_type_info::__sub_kind __vmi_class_type_info::__do_find_public_src(ptrdiff_t src2dst, const void* obj_ptr, const __class_type_info* src_type, const void* src_ptr) const {
    if (obj_ptr == src_ptr && *this == *src_type) {
      return __contained_public;
    }

    for (size_t i = __base_count; i--;) {
      if (!__base_info[i].__is_public_p()) {
        continue;
      }

      const void* base       = obj_ptr;
      ptrdiff_t   offset     = __base_info[i].__offset();
      bool        is_virtual = __base_info[i].__is_virtual_p();

      if (is_virtual && src2dst == -3) {
        continue;
      }

      base = convert_to_base(base, is_virtual, offset);

      __sub_kind base_kind = __base_info[i].__base_type->__do_find_public_src(src2dst, base, src_type, src_ptr);

      if (contained_p(base_kind)) {
        if (is_virtual) {
          base_kind = static_cast<__sub_kind>(base_kind | __contained_virtual_mask);
        }
        return base_kind;
      }
    }

    return __not_contained;
  }

  bool __vmi_class_type_info::__do_upcast(const __class_type_info* dst, const void* obj_ptr, __upcast_result& __restrict result) const {
    if (__class_type_info::__do_upcast(dst, obj_ptr, result)) {
      return true;
    }

    int src_details = result.src_details;
    if (src_details & __flags_unknown_mask) {
      src_details = __flags;
    }

    for (std::size_t i = __base_count; i--;) {
      __upcast_result result2(src_details);
      const void*     base       = obj_ptr;
      ptrdiff_t       offset     = __base_info[i].__offset();
      bool            is_virtual = __base_info[i].__is_virtual_p();
      bool            is_public  = __base_info[i].__is_public_p();

      if (!is_public && !(src_details & __non_diamond_repeat_mask)) {
        continue;
      }

      if (base) {
        base = convert_to_base(base, is_virtual, offset);
      }

      if (__base_info[i].__base_type->__do_upcast(dst, base, result2)) {
        if (result2.base_type == nonvirtual_base_type && is_virtual) {
          result2.base_type = __base_info[i].__base_type;
        }
        if (contained_p(result2.part2dst) && !is_public) {
          result2.part2dst = __sub_kind(result2.part2dst & ~__contained_public_mask);
        }

        if (!result.base_type) {
          result = result2;
          if (!contained_p(result.part2dst)) {
            return true;
          }

          if (result.part2dst & __contained_public_mask) {
            if (!(__flags & __non_diamond_repeat_mask)) {
              return true;
            }
          } else {
            if (!virtual_p(result.part2dst)) {
              return true;
            }
            if (!(__flags & __diamond_shaped_mask)) {
              return true;
            }
          }
        } else if (result.dst_ptr != result2.dst_ptr) {
          result.dst_ptr  = nullptr;
          result.part2dst = __contained_ambig;
          return true;
        } else if (result.dst_ptr) {
          result.part2dst = __sub_kind(result.part2dst | result2.part2dst);
        } else {
          if (result2.base_type == nonvirtual_base_type || result.base_type == nonvirtual_base_type || !(*result2.base_type == *result.base_type)) {
            result.part2dst = __contained_ambig;
            return true;
          }
          result.part2dst = __sub_kind(result.part2dst | result2.part2dst);
        }
      }
    }

    return result.part2dst != __unknown;
  }
} // namespace __cxxabiv1
