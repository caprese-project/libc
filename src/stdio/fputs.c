#include <errno.h>
#include <internal/attribute.h>
#include <internal/branch.h>
#include <stdio.h>

static int __fputs_fbf(const char* __restrict str, FILE* __restrict stream) {
  while (*str != '\0') {
    if (stream->__buf_pos == stream->__buf_size) {
      fflush(stream);
      __if_unlikely (stream->__buf_pos == stream->__buf_size) {
        return EOF;
      }
    }

    stream->__buf[stream->__buf_pos++] = *str;
    ++str;
  }

  return 0;
}

static int __fputs_lbf(const char* __restrict str, FILE* __restrict stream) {
  while (*str != '\0') {
    if (stream->__buf_pos == stream->__buf_size) {
      fflush(stream);
      __if_unlikely (stream->__buf_pos == stream->__buf_size) {
        return EOF;
      }
    }

    stream->__buf[stream->__buf_pos++] = *str;
    if (*str == '\n') {
      fflush(stream);
    }

    ++str;
  }

  return 0;
}

static int __fputs_nbf(const char* __restrict str, FILE* __restrict stream) {
  size_t n = strlen(str);
  __if_unlikely (n == 0) {
    return 0;
  }
  size_t size = stream->__write(str, 1, n, stream);
  return n == size ? 0 : EOF;
}

__weak int fputs(const char* __restrict str, FILE* __restrict stream) {
  __if_unlikely (str == NULL || stream == NULL) {
    return EOF;
  }

  if ((stream->__buf_mode & _IOBUF_MODE_READ) != 0) {
    fflush(stream);
  }

  switch (stream->__buf_mode & 0b11) {
    case _IOFBF:
      return __fputs_fbf(str, stream);
    case _IOLBF:
      return __fputs_lbf(str, stream);
    case _IONBF:
      return __fputs_nbf(str, stream);
  }

  return EOF;
}
