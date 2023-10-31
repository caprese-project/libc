#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak FILE* fopen(__unused const char* __restrict filename, __unused const char* __restrict mode) {
  errno = ENOSYS;
  return NULL;
}
