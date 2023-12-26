#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>
#include <string.h>

__weak int fflush(FILE* stream) {
  if (stream->__buf_pos != 0) {
    size_t size = stream->__write(stream->__buf, 1, stream->__buf_pos, stream);
    if (size != stream->__buf_pos) {
      memmove(stream->__buf, stream->__buf + size, stream->__buf_pos - size);
      stream->__buf_pos -= size;
      return EOF;
    }
    stream->__buf_pos = 0;
  }

  return 0;
}
