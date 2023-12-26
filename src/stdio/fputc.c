#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak int fputc(int ch, FILE* stream) {
  char str[2] = { ch, '\0' };
  return fputs(str, stream);
}
