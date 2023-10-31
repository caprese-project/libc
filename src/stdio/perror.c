#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>
#include <string.h>

__weak void perror(const char* str) {
  fprintf(stderr, "%s: %s\n", str, strerror(errno));
}
