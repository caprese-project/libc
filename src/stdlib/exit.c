#include <stdlib.h>

__weak __noreturn void exit(int status) {
  _Exit(status);
}
