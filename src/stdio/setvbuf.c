#include <errno.h>
#include <internal/attribute.h>
#include <internal/branch.h>
#include <stdio.h>
#include <stdlib.h>

__weak int setvbuf(FILE* __restrict stream, char* __restrict buf, int mode, size_t size) {
  __if_unlikely (stream == NULL) {
    return EOF;
  }

  __if_unlikely (mode != _IOFBF && mode != _IOLBF && mode != _IONBF) {
    return EOF;
  }

  if (buf == NULL) {
    if (size == 0) {
      mode = _IONBF;
    } else {
      buf = malloc(size);
      __if_unlikely (buf == NULL) {
        return EOF;
      }
      mode = _IOFBF | _IOBUF_AUTO_ALLOCATED;
    }
  }

  stream->__mode     = mode;
  stream->__buf      = buf;
  stream->__buf_size = size;
  stream->__buf_pos  = 0;

  return 0;
}
