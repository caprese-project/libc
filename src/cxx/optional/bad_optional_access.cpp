#include <internal/cxx/optional/bad_optional_access.h>

namespace std {
  const char* bad_optional_access::what() const noexcept {
    return "std::bad_optional_access";
  }
} // namespace std
