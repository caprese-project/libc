#include <errno.h>
#include <internal/attribute.h>
#include <internal/branch.h>
#include <stdio.h>

__weak char* fgets(char* __restrict dst, int n, FILE* __restrict stream) {
  __if_unlikely (dst == NULL || n == 0 || stream == NULL) {
    return NULL;
  }

  char* s = dst;

  if (stream->__ungetc_buf != EOF) {
    *dst++ = stream->__ungetc_buf;
    --n;
    stream->__ungetc_buf = EOF;
  }

  if (stream->__buf_pos != 0) {
    if ((stream->__buf_mode & _IOBUF_MODE_READ) != 0) {
      while (stream->__buf_pos != 0 && n > 0) {
        *dst++ = stream->__buf[--stream->__buf_pos];
        --n;
      }
    } else {
      fflush(stream);
    }
  }

  if (n != 0) {
    size_t size = stream->__read(dst, 1, n, stream);
    dst += size;

    if (size != n) {
      *dst = '\0';
      return NULL;
    }
  }

  *dst = '\0';

  return s;
}
