#include <internal/attribute.h>
#include <internal/branch.h>
#include <stdint.h>
#include <stdio.h>

__weak char* gets_s(char* str, rsize_t n) {
  __if_unlikely (str == NULL || n <= 0) {
    return NULL;
  }

  __if_unlikely (n >= RSIZE_MAX) {
    *str = '\0';
    return str;
  }

  int ch;

  while (n > 1 && (ch = getchar()) != EOF) {
    if (ch == '\n') {
      break;
    }

    *str++ = ch;
    n--;
  }

  *str = '\0';

  return str;
}
