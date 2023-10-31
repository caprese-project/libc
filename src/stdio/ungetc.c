#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak int ungetc(__unused int ch, __unused FILE* stream) {
  errno = ENOSYS;
  return EOF;
}
