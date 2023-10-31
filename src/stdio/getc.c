#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak int getc(__unused FILE* stream) {
  errno = ENOSYS;
  return -1;
}