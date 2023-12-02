#include <cstdio>
#include <cstdlib>
#include <internal/cxx/exception/terminate.h>

namespace {
  std::terminate_handler __terminate_handler = nullptr;
} // namespace

namespace std {
  terminate_handler set_terminate(terminate_handler callback) __noexcept {
    // TODO: lock
    terminate_handler old = __terminate_handler;
    __terminate_handler   = callback;
    return old;
  }

  terminate_handler get_terminate() __noexcept {
    return __terminate_handler;
  }

  __noreturn void terminate() __noexcept {
    if (__terminate_handler) {
      __terminate_handler();

      fprintf(stderr, "std::terminate() returned\n");
      abort();
    } else {
      abort();
    }
  }
} // namespace std
