#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak char* fgets(__unused char* __restrict dst, __unused int n, __unused FILE* __restrict stream) {
  errno = ENOSYS;
  return NULL;
}
