#include <internal/attribute.h>
#include <stdio.h>

__weak int puts(const char* str) {
  return fputs(str, stdout) != EOF && putchar('\n') != EOF ? 0 : EOF;
}
