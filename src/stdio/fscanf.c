#include <internal/attribute.h>
#include <stdio.h>

__weak int fscanf(FILE* __restrict stream, const char* __restrict format, ...) {
  va_list ap;
  int     ret;

  va_start(ap, format);
  ret = vfscanf(stream, format, ap);
  va_end(ap);

  return ret;
}
