#include <ctype.h>
#include <internal/attribute.h>

__weak int isxdigit(int ch) {
#ifndef __OPTIMIZE_SIZE__
  return __ctype_table[(unsigned char)(ch & 0xff)] & (__CTYPE_NUMBER_CHAR | __CTYPE_HEX_CHAR);
#else
  return isdigit(ch) || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F');
#endif // __OPTIMIZE_SIZE__
}
