#include <internal/cxx/typeinfo/__cxxabiv1.h>
#include <typeinfo>

namespace __cxxabiv1 {
  namespace {
    using ptr_to_member_function = void (__pbase_type_info::*)();
    using ptr_to_member          = int __pbase_type_info::*;
  } // namespace

  __pbase_type_info::__pbase_type_info(const char* name, int flags, const type_info* pointee): type_info(name), __flags(flags), __pointee(pointee) { }

  __pbase_type_info::~__pbase_type_info() { }

  bool __pbase_type_info::__do_catch(const type_info* thr_type, void** thr_obj, unsigned int outer) const {
    if (*this == *thr_type) {
      return true;
    }

    if (*thr_type == typeid(nullptr)) {
      if (typeid(*this) == typeid(__pointer_type_info)) {
        *thr_obj = nullptr;
        return true;
      } else if (typeid(*this) == typeid(__pointer_to_member_type_info)) {
        if (__pointee->__is_function_p()) {
          static const ptr_to_member_function pmf = nullptr;
          *thr_obj                                = const_cast<ptr_to_member_function*>(&pmf);
          return true;
        } else {
          static const ptr_to_member pm = nullptr;
          *thr_obj                      = const_cast<ptr_to_member*>(&pm);
          return true;
        }
      }
    }

    if (typeid(*this) != typeid(*thr_type)) {
      return false;
    }

    if ((outer & 1) == 0) {
      return false;
    }

    const __pbase_type_info* thrown_type  = static_cast<const __pbase_type_info*>(thr_type);
    unsigned int             thrown_flags = thrown_type->__flags;

    const unsigned fqual_mask  = __transaction_safe_mask | __noexcept_mask;
    unsigned int   throw_fqual = (thrown_flags & fqual_mask);
    unsigned int   catch_fqual = (__flags & fqual_mask);

    if (throw_fqual & ~catch_fqual) {
      thrown_flags &= catch_fqual;
    }

    if (catch_fqual & ~throw_fqual) {
      return false;
    }

    if (thrown_flags & ~__flags) {
      return false;
    }

    if ((__flags & __const_mask) == 0) {
      outer &= ~1;
    }

    return __pointer_catch(thrown_type, thr_obj, outer);
  }

  bool __pbase_type_info::__pointer_catch(const __pbase_type_info* thrown_type, void** thr_obj, unsigned int outer) const {
    return __pointee->__do_catch(thrown_type->__pointee, thr_obj, outer + 2);
  }
} // namespace __cxxabiv1
