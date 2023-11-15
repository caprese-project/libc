#include <internal/attribute.h>
#include <internal/branch.h>
#include <stdlib.h>

void (*__at_quick_exit_callbacks[32])();
void (**__extended_at_quick_exit_callbacks)();
int __at_quick_exit_callback_count;

__weak int at_quick_exit(void (*func)(void)) {
  if (__at_quick_exit_callback_count < 32) {
    __at_quick_exit_callbacks[__at_quick_exit_callback_count] = func;
  } else __if_unlikely (__at_quick_exit_callback_count & 32) {
    void (**new_at_quick_exit_callbacks)() = realloc(__extended_at_quick_exit_callbacks, __at_quick_exit_callback_count * sizeof(void*));
    __if_unlikely (new_at_quick_exit_callbacks == NULL) {
      return 1;
    }
    __extended_at_quick_exit_callbacks                                      = new_at_quick_exit_callbacks;
    __extended_at_quick_exit_callbacks[__at_quick_exit_callback_count - 32] = func;
  } else {
    __extended_at_quick_exit_callbacks[__at_quick_exit_callback_count - 32] = func;
  }
  ++__at_quick_exit_callback_count;
  return 0;
}
