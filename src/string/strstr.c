#include <string.h>

__weak char* strstr(const char* s1, const char* s2) {
  // TODO: optimize this function.
  const char* p1 = s1;
  while (*p1 != '\0') {
    if (strcmp(p1, s2) == 0) {
      return (char*)p1;
    }
    ++p1;
  }
  return NULL;
}
