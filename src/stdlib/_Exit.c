#include <stdlib.h>

__weak __noreturn void _Exit(__unused int status) {
  while (1) { }
}
