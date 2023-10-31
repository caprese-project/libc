#include <internal/branch.h>
#include <stddef.h>
#include <string.h>

__weak size_t strcspn(const char* s1, const char* s2) {
  const char* p1 = s1;
  while (*p1 != '\0') {
    const char* p2 = s2;
    while (*p2 != '\0') {
      __if_unlikely (*p1 == *p2) {
        return (size_t)(p1 - s1);
      }
      ++p2;
    }
    ++p1;
  }
  return (size_t)(p1 - s1);
}
