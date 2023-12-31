#include <ctype.h>
#include <errno.h>
#include <internal/branch.h>
#include <internal/attribute.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

__weak long long int strtoll(const char* __restrict s, char** __restrict end, int base) {
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

  unsigned long long overflow_threshold          = negative ? -(unsigned long long)LLONG_MIN : LLONG_MAX;
  unsigned long long overflow_boundary           = overflow_threshold / base;
  unsigned long long overflow_boundary_remainder = overflow_threshold % base;

  while (true) {
    unsigned long long val;
    if (isdigit(*s)) {
      val = *s - '0';
    } else if (isupper(*s)) {
      val = *s - 'A' + 10;
    } else if (islower(*s)) {
      val = *s - 'a' + 10;
    } else {
      break;
    }

    __if_unlikely (val >= (unsigned long long)base) {
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
    ++s;
  }

  __if_unlikely (err) {
    result = negative ? LLONG_MIN : LLONG_MAX;
    errno  = ERANGE;
  } else if (negative) {
    result = -result;
  }

  if (end != NULL) {
    *end = (char*)s - 1;
  }

  return (long long int)result;
}
