#include <errno.h>
#include <internal/attribute.h>
#include <stdio.h>

__weak size_t fwrite(__unused const void* __restrict ptr, __unused size_t size, __unused size_t nmemb, __unused FILE* __restrict stream) {
  errno = ENOSYS;
  return 0;
}