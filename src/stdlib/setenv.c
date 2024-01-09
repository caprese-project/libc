#include <errno.h>
#include <internal/attribute.h>
#include <stdlib.h>

int setenv(__unused const char* name, __unused const char* value, __unused int overwrite) {
  errno = ENOSYS;
  return -1;
}
