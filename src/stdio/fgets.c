#include <errno.h>
#include <internal/attribute.h>
#include <internal/branch.h>
#include <stdio.h>

__weak char* fgets(char* __restrict dst, int n, FILE* __restrict stream) {
  __if_unlikely (dst == NULL || n == 0 || stream == NULL) {
    return NULL;
  }

  int ch;

  while (n > 1 && (ch = fgetc(stream)) != EOF) {
    *dst++ = ch;
    n--;
  }

  *dst = '\0';

  return dst;
}
