#ifndef CAPRESE_LIBC_INTERNAL_CXX_EXCEPTION_TERMINATE_H_
#define CAPRESE_LIBC_INTERNAL_CXX_EXCEPTION_TERMINATE_H_

#include <internal/attribute.h>

namespace std {
  using terminate_handler = void (*)();
  terminate_handler set_terminate(terminate_handler callback) __noexcept;
  terminate_handler get_terminate() __noexcept;
  __noreturn void   terminate() __noexcept;
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_EXCEPTION_TERMINATE_H_
