#include <internal/attribute.h>
#include <stddef.h>
#include <stdlib.h>

extern void* __alloc(void* ptr, size_t size, size_t alignment);

__weak void* malloc(size_t size) {
  return __alloc(NULL, size, 0);
}
