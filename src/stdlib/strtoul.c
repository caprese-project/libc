#include <errno.h>
#include <internal/branch.h>
#include <limits.h>
#include <stdlib.h>

__weak unsigned long int strtoul(const char* __restrict s, char** __restrict end, int base) {
  unsigned long long int result = strtoull(s, end, base);
  __if_unlikely (result > ULONG_MAX) {
    errno = ERANGE;
    return ULONG_MAX;
  }
  return (unsigned long int)result;
}
