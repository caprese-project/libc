#include <internal/attribute.h>
#include <stddef.h>

__weak void* __alloc(__unused void* ptr, __unused size_t size, __unused size_t alignment) {
  return NULL;
}
