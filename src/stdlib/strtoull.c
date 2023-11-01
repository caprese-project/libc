#include <ctype.h>
#include <errno.h>
#include <internal/attribute.h>
#include <internal/branch.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

__weak unsigned long long int strtoull(const char* __restrict s, char** __restrict end, int base) {
  unsigned long long int result   = 0;
  bool                   negative = false;
  bool                   err      = false;

  if (end != NULL) {
    *end = (char*)s;
  }

  while (isspace(*s)) {
    ++s;
  }

  __if_unlikely (*s == '-') {
    negative = true;
    ++s;
  } else __if_unlikely (*s == '+') {
    ++s;
  }

  if ((base == 0 || base == 16) && s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
    s += 2;
    base = 16;
  } else if (base == 0 && s[0] == '0') {
    s += 1;
    base = 8;
  } else if (base == 0) {
    base = 10;
  }

  unsigned long long overflow_boundary           = ULLONG_MAX / base;
  unsigned long long overflow_boundary_remainder = ULLONG_MAX % base;

  while (true) {
    unsigned long long val;
    if (isdigit(*s)) {
      val = *s - '0';
    } else if (isupper(*s)) {
      val = *s - 'A';
    } else if (islower(*s)) {
      val = *s - 'a';
    } else {
      break;
    }

    __if_unlikely (val >= base) {
      break;
    }

    __if_unlikely (err || result > overflow_boundary || (result == overflow_boundary && val > overflow_boundary_remainder)) {
      err = true;
      __if_unlikely (end == NULL) {
        break;
      }
    }

    result *= base;
    result += val;
  }

  __if_unlikely (err) {
    result = ULLONG_MAX;
    errno  = ERANGE;
  } else if (negative) {
    result = -result;
  }

  if (end != NULL) {
    *end = (char*)s - 1;
  }

  return result;
}
