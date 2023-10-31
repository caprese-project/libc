#include <internal/attribute.h>
#include <stdio.h>

int snprintf(char* __restrict dst, size_t n, const char* __restrict format, ...) {
  va_list ap;
  int     ret;

  va_start(ap, format);
  ret = vsnprintf(dst, n, format, ap);
  va_end(ap);

  return ret;
}
