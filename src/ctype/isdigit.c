#include <ctype.h>
#include <internal/attribute.h>

__weak int isdigit(int ch) {
#ifndef __OPTIMIZE_SIZE__
  return __ctype_table[(unsigned char)(ch & 0xff)] & __CTYPE_NUMBER_CHAR;
#else
  return ch >= '0' && ch <= '9';
#endif // __OPTIMIZE_SIZE__
}
