#include <ctype.h>
#include <internal/attribute.h>

__weak int toupper(int ch) {
  return islower(ch) ? ch - 'a' + 'A' : ch;
}
