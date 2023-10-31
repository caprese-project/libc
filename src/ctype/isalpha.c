#include <ctype.h>
#include <internal/attribute.h>

__weak int isalpha(int ch) {
#ifndef __OPTIMIZE_SIZE__
  return __ctype_table[(unsigned char)(ch & 0xff)] & (__CTYPE_UPPER_CHAR | __CTYPE_LOWER_CHAR);
#else
  return isupper(ch) || islower(ch);
#endif // __OPTIMIZE_SIZE__
}
