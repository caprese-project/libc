#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak long int ftell(__unused FILE* stream) {
  errno = ENOSYS;
  return -1;
}
