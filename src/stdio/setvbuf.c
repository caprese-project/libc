#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak int setvbuf(__unused FILE* __restrict stream, __unused char* __restrict buf, __unused int mode, __unused size_t size) {
  errno = ENOSYS;
  return -1;
}
