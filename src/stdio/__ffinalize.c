#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak int __ffinalize(FILE*) {
  errno = ENOSYS;
  return EOF;
}
