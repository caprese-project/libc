#include <internal/attribute.h>
#include <stdio.h>

__weak void setbuf(FILE* __restrict stream, char* __restrict buf) {
  setvbuf(stream, buf, buf ? _IOFBF : _IONBF, BUFSIZ);
}
