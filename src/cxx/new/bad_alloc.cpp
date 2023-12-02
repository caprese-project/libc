#include <internal/cxx/new/bad_alloc.h>

namespace std {
  const char* bad_alloc::what() const noexcept {
    return "std::bad_alloc";
  }
} // namespace std
