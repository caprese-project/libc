#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak int fsetpos(__unused FILE* stream, const __unused fpos_t* pos) {
  errno = ENOSYS;
  return -1;
}
