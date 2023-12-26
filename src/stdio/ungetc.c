#include <errno.h>
#include <internal/attribute.h>
#include <internal/branch.h>
#include <stdio.h>

__weak int ungetc(int ch, FILE* stream) {
  __if_unlikely (stream == NULL) {
    return EOF;
  }

  if ((stream->__mode & 0b11) != _IONBF && (stream->__mode & _IOBUF_MODE_READ) != 0 && stream->__buf_pos != 0) {
    stream->__ungetc_buf = ch;
    --stream->__buf_pos;
  } else {
    stream->__ungetc_buf = stream->__ungetc(ch, stream);
  }

  return stream->__ungetc_buf;
}
