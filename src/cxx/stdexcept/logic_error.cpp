#include <internal/cxx/stdexcept/logic_error.h>

namespace std {
  logic_error::logic_error(const char* msg): _msg(msg) { }

  logic_error::logic_error(const string& msg): _msg(msg) { }

  const char* logic_error::what() const noexcept {
    return _msg.c_str();
  }
} // namespace std
