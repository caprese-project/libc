#include <errno.h>
#include <internal/attribute.h>
#include <internal/branch.h>
#include <stdio.h>

__weak size_t fread(void* __restrict ptr, size_t size, size_t nmemb, FILE* __restrict stream) {
  __if_unlikely (ptr == NULL || size == 0 || nmemb == 0 || stream == NULL) {
    return 0;
  }
  return stream->__read(ptr, size, nmemb, stream);
}
