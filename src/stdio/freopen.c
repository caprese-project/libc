#include <errno.h>
#include <internal/attribute.h>
#include <internal/branch.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// fopen.c
extern int __parse_fopen_mode(const char* mode);

__weak FILE* freopen(const char* __restrict filename, const char* __restrict mode, FILE* __restrict stream) {
  int  imode = 0;
  bool alloc = false;

  if (stream != NULL) {
    imode = stream->__mode & _O_MASK;
    __ffinalize(stream);
  } else {
    stream = malloc(sizeof(FILE));
    __if_unlikely (stream == NULL) {
      return NULL;
    }
    alloc = true;
  }

  __if_unlikely (filename == NULL) {
    return NULL;
  }

  if (mode != NULL) {
    imode = __parse_fopen_mode(mode);
  }

  __if_unlikely (imode == 0) {
    return NULL;
  }

  stream->__mode = imode;

  __if_unlikely (__finitialize(filename, 1, stream) == EOF) {
    if (alloc) {
      free(stream);
    }
    return NULL;
  }

  return stream;
}
