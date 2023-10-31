#include <stdlib.h>

__weak int atoi(const char* s) {
  return (int)atoll(s);
}
