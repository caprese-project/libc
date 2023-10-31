#include <ctype.h>
#include <internal/attribute.h>

__weak int ispunct(int ch) {
#ifndef __OPTIMIZE_SIZE__
  return __ctype_table[(unsigned char)(ch & 0xff)] & __CTYPE_PUNCT_CHAR;
#else
  return (ch >= '!' && ch <= '/') || (ch >= ':' && ch <= '@') || (ch >= '[' && ch <= '`') || (ch >= '{' && ch <= '~');
#endif // __OPTIMIZE_SIZE__
}
