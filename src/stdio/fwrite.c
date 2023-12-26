#include <errno.h>
#include <internal/attribute.h>
#include <internal/branch.h>
#include <stdio.h>

__weak size_t fwrite(const void* __restrict ptr, size_t size, size_t nmemb, FILE* __restrict stream) {
  __if_unlikely (size == 0 || nmemb == 0) {
    return 0;
  }
  return stream->__write(ptr, size, nmemb, stream);
}
