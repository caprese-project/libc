#include <internal/cxx/typeinfo/exception.h>

namespace std {
  const char* bad_cast::what() const __noexcept {
    return "std::bad_cast";
  }

  const char* bad_typeid::what() const __noexcept {
    return "std::bad_typeid";
  }
} // namespace std
