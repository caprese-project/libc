#include <internal/attribute.h>
#include <stdarg.h>
#include <stdio.h>

__weak int printf(const char* __restrict format, ...) {
  va_list ap;
  int     ret;

  va_start(ap, format);
  ret = vfprintf(stdout, format, ap);
  va_end(ap);

  return ret;
}
