#include <ctype.h>
#include <internal/attribute.h>

__weak int isblank(int ch) {
#ifndef __OPTIMIZE_SIZE__
  return __ctype_table[(unsigned char)(ch & 0xff)] & __CTYPE_BLANK_CHAR;
#else
  return ch == ' ' || ch == '\t';
#endif // __OPTIMIZE_SIZE__
}
