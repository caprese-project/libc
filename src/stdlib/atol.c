#include <stdlib.h>

__weak long int atol(const char* s) {
  return (long int)atoll(s);
}
