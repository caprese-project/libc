#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak int fputs(__unused const char* __restrict str, __unused FILE* __restrict stream) {
  int count = 0;
  while (*str) {
    if (fputc(*str++, stream) == EOF) {
      return EOF;
    }
    count++;
  }
  return count;
}
