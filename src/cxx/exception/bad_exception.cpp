#include <internal/cxx/exception/bad_exception.h>

namespace std {
  const char* bad_exception::what() const __noexcept {
    return "std::bad_exception";
  }
} // namespace std
