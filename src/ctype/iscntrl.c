#include <ctype.h>
#include <internal/attribute.h>

__weak int iscntrl(int ch) {
#ifndef __OPTIMIZE_SIZE__
  return __ctype_table[(unsigned char)(ch & 0xff)] & __CTYPE_CTRL_CHAR;
#else
  return (ch >= 0 && ch <= 0x1f) || ch == 0x7f;
#endif // __OPTIMIZE_SIZE__
}
