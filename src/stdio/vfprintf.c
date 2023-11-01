#include <errno.h>
#include <internal/attribute.h>
#include <internal/branch.h>
#include <stdbool.h>
#include <stdio.h>

static struct __data {
  bool  eof;
  int   count;
  FILE* stream;
};

static void __vfprintf_callback(int ch, void* data) {
  struct __data* d = data;
  if (fputc(ch, d->stream) == EOF) {
    return EOF;
  }
  d->count++;
  return 0;
}

__weak int vfprintf(FILE* __restrict stream, const char* __restrict format, va_list arg) {
  struct __data data;
  data.eof    = false;
  data.count  = 0;
  data.stream = stream;

  __vformat(format, arg, &data, __vfprintf_callback);

  __if_unlikely (data.eof) {
    return -1;
  }

  return data.count;
}
