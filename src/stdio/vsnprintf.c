#include <errno.h>
#include <internal/attribute.h>
#include <internal/branch.h>
#include <stdio.h>

static struct __vsnprintf_data {
  char*  dst;
  size_t n;
};

static void __vsnprintf_callback(int ch, void* data) {
  struct __vsnprintf_data* d = data;
  if (d->n == 0) {
    return;
  }
  *d->dst++ = ch;
  d->n--;
}

__weak int vsnprintf(char* __restrict dst, size_t n, const char* __restrict format, va_list arg) {
  __if_unlikely (n == 0) {
    return 0;
  }

  struct __vsnprintf_data data;
  data.dst = dst;
  data.n   = n - 1;

  __vformat(format, arg, &data, __vsnprintf_callback);

  *data.dst = '\0';

  return data.dst - dst;
}
