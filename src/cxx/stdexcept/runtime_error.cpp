#include <internal/cxx/stdexcept/runtime_error.h>

namespace std {
  runtime_error::runtime_error(const char* msg): _msg(msg) { }

  runtime_error::runtime_error(const string& msg): _msg(msg) { }

  const char* runtime_error::what() const __noexcept {
    return _msg.c_str();
  }
} // namespace std
