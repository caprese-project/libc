#include <internal/attribute.h>
#include <stdio.h>

__weak int putc(int ch, FILE* stream) {
  return fputc(ch, stream);
}
