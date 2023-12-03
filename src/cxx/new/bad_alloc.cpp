#include <internal/cxx/new/bad_alloc.h>

namespace std {
  const char* bad_alloc::what() const noexcept {
    return "std::bad_alloc";
  }

  const char* bad_array_new_length::what() const noexcept {
    return "std::bad_array_new_length";
  }
} // namespace std
