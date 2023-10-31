#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak char* tmpnam(__unused char* s) {
  errno = ENOSYS;
  return NULL;
}
