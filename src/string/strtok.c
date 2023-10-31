#include <internal/branch.h>
#include <string.h>

static char* __strtok_buffer = NULL;

__weak char* strtok(char* __restrict s1, const char* __restrict s2) {
  __if_unlikely (s1 != NULL) {
    __strtok_buffer = s1;
  } else __if_unlikely (__strtok_buffer == NULL) {
    return NULL;
  }

  // Skip tokens.

  char* buf = __strtok_buffer;
  while (*buf != '\0') {
    const char* p2 = s2;
    while (*p2 != '\0') {
      __if_unlikely (*buf == *p2) {
        break;
      }
      ++p2;
    }
    __if_unlikely (*p2 == '\0') {
      break;
    }
    ++buf;
  }

  __if_unlikely (*buf == '\0') {
    __strtok_buffer = NULL;
    return NULL;
  }

  __strtok_buffer = strpbrk(buf + 1, s2);
  __if_likely (__strtok_buffer != NULL) {
    *__strtok_buffer = '\0';
    ++__strtok_buffer;
  }

  return buf;
}
