#include <internal/attribute.h>
#include <internal/branch.h>
#include <stdlib.h>

void (*__atexit_callbacks[32])();
void (**__extended_atexit_callbacks)();
int __atexit_callback_count;

__weak int atexit(void (*func)()) {
  if (__atexit_callback_count < 32) {
    __atexit_callbacks[__atexit_callback_count] = func;
  } else __if_unlikely (__atexit_callback_count & 32) {
    void (**new_atexit_callbacks)() = realloc(__extended_atexit_callbacks, __atexit_callback_count * sizeof(void*));
    __if_unlikely (new_atexit_callbacks == NULL) {
      return 1;
    }
    __extended_atexit_callbacks                               = new_atexit_callbacks;
    __extended_atexit_callbacks[__atexit_callback_count - 32] = func;
  } else {
    __extended_atexit_callbacks[__atexit_callback_count - 32] = func;
  }
  ++__atexit_callback_count;
  return 0;
}
