#include <errno.h>
#include <internal/attribute.h>

static int __errno_value;

__weak int* __errno(void) {
  return &__errno_value;
}
