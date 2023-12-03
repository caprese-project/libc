#include <internal/cxx/typeinfo/__cxxabiv1.h>

namespace std {
  type_info::type_info(const char* name): __name(name) {};
  type_info::~type_info() {};

  const char* type_info::name() const __noexcept {
    return __name[0] == '*' ? __name + 1 : __name;
  }

  bool type_info::before(const type_info& rhs) const __noexcept {
    if (__name[0] == '*' && rhs.__name[0] == '*') {
      return __name < rhs.__name;
    } else {
      return __builtin_strcmp(__name, rhs.__name) < 0;
    }
  }

  bool type_info::operator==(const type_info& rhs) const __noexcept {
    if (__name == rhs.__name) {
      return true;
    } else if (__name[0] != '*' && __builtin_strcmp(__name, rhs.__name) == 0) {
      return true;
    } else {
      return false;
    }
  }

  bool type_info::__is_pointer_p() const {
    return false;
  }

  bool type_info::__is_function_p() const {
    return false;
  }

  bool type_info::__do_catch(const type_info*, void**, unsigned) const {
    return false;
  }

  bool type_info::__do_upcast(const ::__cxxabiv1::__class_type_info*, void**) const {
    return false;
  }
} // namespace std
