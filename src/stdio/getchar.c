#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak int getchar(void) {
  return fgetc(stdin);
}
