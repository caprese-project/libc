#ifndef CAPRESE_LIBC_INTERNAL_CXX_NEW_HANDLER_H_
#define CAPRESE_LIBC_INTERNAL_CXX_NEW_HANDLER_H_

#include <internal/attribute.h>

namespace std {
  using new_handler = void (*)();

  new_handler set_new_handler(new_handler new_p) __noexcept;
  new_handler get_new_handler() __noexcept;
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_NEW_HANDLER_H_
