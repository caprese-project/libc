#include <ctype.h>
#include <internal/attribute.h>

__weak int isupper(int ch) {
#ifndef __OPTIMIZE_SIZE__
  return __ctype_table[(unsigned char)(ch & 0xff)] & __CTYPE_UPPER_CHAR;
#else
  return ch >= 'A' && ch <= 'Z';
#endif // __OPTIMIZE_SIZE__
}
