#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak int vfscanf(__unused FILE* __restrict stream, __unused const char* __restrict format, __unused va_list arg) {
  errno = ENOSYS;
  return -1;
}
