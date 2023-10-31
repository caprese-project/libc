#include <assert.h>
#include <internal/attribute.h>
#include <stdio.h>
#include <stdlib.h>

__weak __noreturn void __assertion_failed(const char* file, int line, const char* function, const char* condition) {
  fprintf(stderr, "Assertion failed: %s, %s at %s:%d", condition, function, file, line);
  abort();
}
