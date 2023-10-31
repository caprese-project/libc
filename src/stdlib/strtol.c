#include <errno.h>
#include <internal/branch.h>
#include <limits.h>
#include <stdlib.h>

__weak long int strtol(const char* __restrict s, char** __restrict end, int base) {
  long long int result = strtoll(s, end, base);
  __if_unlikely (result > LONG_MAX) {
    errno = ERANGE;
    return LONG_MAX;
  } else __if_unlikely (result < LONG_MIN) {
    errno = ERANGE;
    return LONG_MIN;
  }
  return (long int)result;
}
