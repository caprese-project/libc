#include <ctype.h>
#include <internal/attribute.h>

__weak int isprint(int ch) {
#ifndef __OPTIMIZE_SIZE__
  return __ctype_table[(unsigned char)(ch & 0xff)] & (__CTYPE_UPPER_CHAR | __CTYPE_LOWER_CHAR | __CTYPE_NUMBER_CHAR | __CTYPE_PUNCT_CHAR | __CTYPE_BLANK_CHAR);
#else
  return isgraph(ch) || isblank(ch);
#endif // __OPTIMIZE_SIZE__
}
