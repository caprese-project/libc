#include <internal/attribute.h>
#include <stdio.h>

__weak int vprintf(const char* __restrict format, va_list arg) {
  return vfprintf(stdout, format, arg);
}
