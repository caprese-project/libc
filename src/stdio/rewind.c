#include <internal/attribute.h>
#include <stdio.h>

__weak void rewind(FILE* stream) {
  fseek(stream, 0, SEEK_SET);
  clearerr(stream);
}
