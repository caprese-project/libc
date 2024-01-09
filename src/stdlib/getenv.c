#include <internal/attribute.h>
#include <stdlib.h>

__weak char* getenv(__unused const char* name) {
  return NULL;
}
