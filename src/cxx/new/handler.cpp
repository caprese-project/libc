#include <internal/cxx/new/handler.h>

namespace {
  std::new_handler __new_handler = nullptr;
} // namespace

namespace std {
  new_handler set_new_handler(new_handler new_p) __noexcept {
    // TODO: lock
    new_handler old = __new_handler;
    __new_handler   = new_p;
    return old;
  }

  new_handler get_new_handler() __noexcept {
    return __new_handler;
  }
} // namespace std
