#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak int fputc(__unused int ch, __unused FILE* stream) {
  errno = ENOSYS;
  return -1;
}
