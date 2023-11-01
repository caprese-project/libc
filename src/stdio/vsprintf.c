#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

static void __vsprintf_callback(int ch, void* data) {
  char** d = data;
  *d++     = (char)ch;
}

__weak int vsprintf(char* __restrict dst, const char* __restrict format, va_list arg) {
  char* d = dst;
  __vformat(format, arg, &d, __vsprintf_callback);
  *d = '\0';
  return d - dst;
}
