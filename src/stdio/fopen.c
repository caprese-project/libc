#include <errno.h>
#include <internal/attribute.h>
#include <internal/branch.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

__weak int __parse_fopen_mode(const char* mode) {
  __if_unlikely (mode == NULL) {
    return 0;
  }

  if (strcmp("r", mode) == 0) {
    return _O_READ;
  } else if (strcmp("w", mode) == 0) {
    return _O_WRITE;
  } else if (strcmp("a", mode) == 0) {
    return _O_APPEND;
  } else if (strcmp("rb", mode) == 0) {
    return _O_READ | _O_BINARY;
  } else if (strcmp("wb", mode) == 0) {
    return _O_WRITE | _O_BINARY;
  } else if (strcmp("ab", mode) == 0) {
    return _O_APPEND | _O_BINARY;
  } else if (strcmp("r+", mode) == 0) {
    return _O_READ | _O_PLUS;
  } else if (strcmp("w+", mode) == 0) {
    return _O_WRITE | _O_PLUS;
  } else if (strcmp("a+", mode) == 0) {
    return _O_APPEND | _O_PLUS;
  } else if (strcmp("rb+", mode) == 0 || strcmp("r+b", mode) == 0) {
    return _O_READ | _O_BINARY | _O_PLUS;
  } else if (strcmp("wb+", mode) == 0 || strcmp("w+b", mode) == 0) {
    return _O_WRITE | _O_BINARY | _O_PLUS;
  } else if (strcmp("ab+", mode) == 0 || strcmp("a+b", mode) == 0) {
    return _O_APPEND | _O_BINARY | _O_PLUS;
  } else {
    return 0;
  }
}

__weak FILE* fopen(const char* __restrict filename, const char* __restrict mode) {
  __if_unlikely (filename == NULL) {
    return NULL;
  }

  int imode = __parse_fopen_mode(mode);
  __if_unlikely (imode == 0) {
    return NULL;
  }

  FILE* fp = malloc(sizeof(FILE));
  __if_unlikely (fp == NULL) {
    return NULL;
  }

  fp->__mode = imode;

  __if_unlikely (__finitialize(filename, 0, fp) == EOF) {
    free(fp);
    return NULL;
  }

  return fp;
}
