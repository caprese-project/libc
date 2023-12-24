#ifndef CAPRESE_LIBC_STRING_H_
#define CAPRESE_LIBC_STRING_H_

#include <internal/attribute.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  int memcmp(const void* s1, const void* s2, size_t n);
  int strcmp(const char* s1, const char* s2);
  int strncmp(const char* s1, const char* s2, size_t n);

  char* strcat(char* __restrict dst, const char* __restrict src);
  char* strncat(char* __restrict dst, const char* __restrict src, size_t n);

  void*  memchr(const void* s, int ch, size_t n);
  char*  strchr(const char* s, int ch);
  char*  strrchr(const char* s, int ch);
  size_t strcspn(const char* s1, const char* s2);
  size_t strspn(const char* s1, const char* s2);
  char*  strpbrk(const char* s1, const char* s2);
  char*  strstr(const char* s1, const char* s2);
  char*  strtok(char* __restrict s1, const char* __restrict s2);

  void* memset(void* s, int ch, size_t n);
  void* memcpy(void* __restrict dst, const void* __restrict src, size_t n);
  void* memmove(void* dst, const void* src, size_t n);
  char* strcpy(char* __restrict dst, const char* __restrict src);
  char* strncpy(char* __restrict dst, const char* __restrict src, size_t n);

  char* strerror(int errnum);

  size_t strlen(const char* s);
  size_t strnlen(const char* s, size_t n);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // CAPRESE_LIBC_STRING_H_
