#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak FILE* tmpfile(void) {
  errno = ENOSYS;
  return NULL;
}
