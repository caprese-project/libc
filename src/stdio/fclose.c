#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>
#include <stdlib.h>

__weak int fclose(FILE* stream) {
  fflush(stream);

  if (stream->__mode & _IOBUF_AUTO_ALLOCATED) {
    free(stream->__buf);
    stream->__buf = NULL;
  }

  return __ffinalize(stream);
}
