#include <internal/attribute.h>
#include <string.h>

__weak char* strerror(__unused int errnum) {
  // TODO: implement this function.
  return "strerror() is not implemented";
}
