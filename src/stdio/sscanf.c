#include <internal/attribute.h>
#include <stdio.h>

int sscanf(const char* __restrict s, const char* __restrict format, ...) {
  va_list ap;
  int     ret;

  va_start(ap, format);
  ret = vsscanf(s, format, ap);
  va_end(ap);

  return ret;
}
