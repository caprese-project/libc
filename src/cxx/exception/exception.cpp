#include <internal/cxx/exception/exception.h>

namespace std {
  const char* exception::what() const __noexcept {
    return "std::exception";
  }
} // namespace std
