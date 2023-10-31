#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak int remove(__unused const char* filename) {
  errno = ENOSYS;
  return -1;
}
