#include <internal/attribute.h>
#include <stdio.h>

__weak int putchar(int ch) {
  return fputc(ch, stdout);
}
