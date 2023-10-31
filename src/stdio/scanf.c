#include <internal/attribute.h>
#include <stdio.h>

__weak int scanf(const char* __restrict format, ...) {
  va_list ap;
  int     ret;

  va_start(ap, format);
  ret = vfscanf(stdin, format, ap);
  va_end(ap);

  return ret;
}
