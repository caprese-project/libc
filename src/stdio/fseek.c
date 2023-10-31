#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak int fseek(__unused FILE* stream, __unused long int offset, __unused int whence) {
  errno = ENOSYS;
  return -1;
}
