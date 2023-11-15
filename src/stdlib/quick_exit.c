#include <internal/attribute.h>
#include <stdlib.h>

extern void (*__at_quick_exit_callbacks[32])();
extern void (**__extended_at_quick_exit_callbacks)();
extern int __at_quick_exit_callback_count;

__noreturn void quick_exit(int status) {
  while (__at_quick_exit_callback_count > 32) {
    __extended_at_quick_exit_callbacks[--__at_quick_exit_callback_count - 32]();
  }

  while (__at_quick_exit_callback_count > 0) {
    __at_quick_exit_callbacks[--__at_quick_exit_callback_count]();
  }

  _Exit(status);
}
