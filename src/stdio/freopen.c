#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak FILE* freopen(__unused const char* __restrict filename, __unused const char* __restrict mode, __unused FILE* __restrict stream) {
  errno = ENOSYS;
  return NULL;
}
