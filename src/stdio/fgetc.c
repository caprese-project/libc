#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak int fgetc(FILE* stream) {
  char ch;
  fgets(&ch, 1, stream);
  return ch;
}
