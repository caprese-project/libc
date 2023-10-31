#include <ctype.h>
#include <internal/attribute.h>

__weak int tolower(int ch) {
  return isupper(ch) ? ch - 'A' + 'a' : ch;
}
