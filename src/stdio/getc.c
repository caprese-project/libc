#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak int getc(FILE* stream) {
  return fgetc(stream);
}
