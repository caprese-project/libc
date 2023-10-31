#include <ctype.h>
#include <internal/attribute.h>

__weak int islower(int ch) {
#ifndef __OPTIMIZE_SIZE__
  return __ctype_table[(unsigned char)(ch & 0xff)] & __CTYPE_LOWER_CHAR;
#else
  return ch >= 'a' && ch <= 'z';
#endif // __OPTIMIZE_SIZE__
}
