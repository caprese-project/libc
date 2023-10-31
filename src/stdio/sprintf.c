#include <internal/attribute.h>
#include <stdio.h>

__weak int sprintf(char* __restrict dst, const char* __restrict format, ...) {
  va_list ap;
  int     ret;

  va_start(ap, format);
  ret = vsprintf(dst, format, ap);
  va_end(ap);

  return ret;
}
