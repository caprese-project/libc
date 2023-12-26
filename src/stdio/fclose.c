#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak int fclose(FILE* stream) {
  fflush(stream);

  if (stream->__buf_mode & _IOBUF_AUTO_ALLOCATED) {
    free(stream->__buf);
    stream->__buf = NULL;
  }

  return __ffinalize(stream);
}
