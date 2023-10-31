#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak int vsnprintf(__unused char* __restrict dst, __unused size_t n, __unused const char* __restrict format, __unused va_list arg) {
  errno = ENOSYS;
  return -1;
}
