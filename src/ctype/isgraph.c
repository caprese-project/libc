#include <ctype.h>
#include <internal/attribute.h>

__weak int isgraph(int ch) {
#ifndef __OPTIMIZE_SIZE__
  return __ctype_table[(unsigned char)(ch & 0xff)] & (__CTYPE_UPPER_CHAR | __CTYPE_LOWER_CHAR | __CTYPE_NUMBER_CHAR | __CTYPE_PUNCT_CHAR);
#else
  return isalnum(ch) || ispunct(ch);
#endif // __OPTIMIZE_SIZE__
}
