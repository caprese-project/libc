#include <errno.h>
#include <internal/attribute.h>
#include <internal/branch.h>
#include <stdbool.h>
#include <stdio.h>

struct __vfprintf_data {
  bool  eof;
  int   count;
  FILE* stream;
};

static void __vfprintf_callback(int ch, void* data) {
  struct __vfprintf_data* d = data;
  if (fputc(ch, d->stream) == EOF) {
    d->eof = true;
    return;
  }
  d->count++;
}

__weak int vfprintf(FILE* __restrict stream, const char* __restrict format, va_list arg) {
  struct __vfprintf_data data;
  data.eof    = false;
  data.count  = 0;
  data.stream = stream;

  __vformat(format, arg, &data, __vfprintf_callback);

  __if_unlikely (data.eof) {
    return -1;
  }

  return data.count;
}
