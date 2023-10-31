#include <internal/attribute.h>
#include <stdio.h>

__weak int vscanf(const char* __restrict format, va_list arg) {
  return vfscanf(stdin, format, arg);
}
