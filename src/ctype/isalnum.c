#include <ctype.h>
#include <internal/attribute.h>

__weak int isalnum(int ch) {
#ifndef __OPTIMIZE_SIZE__
  return __ctype_table[(unsigned char)(ch & 0xff)] & (__CTYPE_UPPER_CHAR | __CTYPE_LOWER_CHAR | __CTYPE_NUMBER_CHAR);
#else
  return isalpha(ch) || isdigit(ch);
#endif // __OPTIMIZE_SIZE__
}
