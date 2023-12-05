#include <internal/attribute.h>
#include <internal/branch.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

extern void* __alloc(void* ptr, size_t size, size_t alignment);

__weak void* calloc(size_t num, size_t size) {
  void* ptr = __alloc(NULL, num * size, 0);

  __if_unlikely (ptr == NULL) {
    return NULL;
  }

  return memset(ptr, 0, num * size);
}
