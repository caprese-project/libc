#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak int __finitialize(const char*, int, FILE*) {
  errno = ENOSYS;
  return EOF;
}
