#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak int rename(__unused const char* old_name, __unused const char* new_name) {
  errno = ENOSYS;
  return -1;
}
