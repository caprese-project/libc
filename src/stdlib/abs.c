#include <internal/attribute.h>
#include <stdlib.h>

__weak int abs(int x) {
  return x < 0 ? -x : x;
}
