#include <internal/attribute.h>
#include <stdlib.h>

extern void (*__atexit_callbacks[32])();
extern void (**__extended_atexit_callbacks)();
extern int __atexit_callback_count;

__weak __noreturn void exit(int status) {
  while (__atexit_callback_count > 32) {
    __extended_atexit_callbacks[--__atexit_callback_count - 32]();
  }

  while (__atexit_callback_count > 0) {
    __atexit_callbacks[--__atexit_callback_count]();
  }

  _Exit(status);
}
