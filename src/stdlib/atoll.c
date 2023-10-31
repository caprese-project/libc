#include <ctype.h>
#include <internal/branch.h>
#include <stdbool.h>
#include <stdlib.h>

__weak long long int atoll(const char* s) {
  long long int result   = 0;
  bool          negative = false;

  while (isspace(*s)) {
    ++s;
  }

  if (*s == '-') {
    negative = true;
    ++s;
  } else __if_unlikely (*s == '+') {
    ++s;
  }

  while (isdigit(*s)) {
    result *= 10;
    result += *s - '0';
    ++s;
  }

  if (negative) {
    result = -result;
  }

  return result;
}
