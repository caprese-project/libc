#include <typeinfo>

namespace __cxxabiv1 {
  class __class_type_info: public std::type_info { };

  class __si_class_type_info: public __class_type_info { };
} // namespace __cxxabiv1
