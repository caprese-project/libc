#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak int fputs(__unused const char* __restrict str, __unused FILE* __restrict stream) {
  errno = ENOSYS;
  return -1;
}
