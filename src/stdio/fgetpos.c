#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak int fgetpos(__unused FILE* __restrict stream, __unused fpos_t* __restrict pos) {
  errno = ENOSYS;
  return -1;
}
