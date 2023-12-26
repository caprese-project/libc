#include <internal/attribute.h>
#include <internal/branch.h>
#include <stdio.h>

__weak char* gets(char* str) {
  __if_unlikely (str == NULL) {
    return NULL;
  }

  int ch;

  while ((ch = getchar()) != EOF) {
    if (ch == EOF) {
      *str = '\0';
      return NULL;
    }

    if (ch == '\n') {
      break;
    }

    *str++ = ch;
  }

  *str = '\0';

  return str;
}
