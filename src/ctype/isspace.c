#include <ctype.h>
#include <internal/attribute.h>

__weak int isspace(int ch) {
#ifndef __OPTIMIZE_SIZE__
  return __ctype_table[(unsigned char)(ch & 0xff)] & __CTYPE_SPACE_CHAR;
#else
  return ch == ' ' || (ch >= '\t' && ch <= '\r');
#endif // __OPTIMIZE_SIZE__
}
