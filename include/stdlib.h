#ifndef CAPRESE_LIBC_STDLIB_H_
#define CAPRESE_LIBC_STDLIB_H_

#include <internal/attribute.h>
#include <stddef.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  typedef struct {
    int quot;
    int rem;
  } div_t;

  typedef struct {
    long int quot;
    long int rem;
  } ldiv_t;

  typedef struct {
    long long int quot;
    long long int rem;
  } lldiv_t;

  double                 atof(const char* s);
  int                    atoi(const char* s);
  long int               atol(const char* s);
  long long int          atoll(const char* s);
  double                 strtod(const char* __restrict s, char** __restrict end);
  float                  strtof(const char* __restrict s, char** __restrict end);
  long double            strtold(const char* __restrict s, char** __restrict end);
  long int               strtol(const char* __restrict s, char** __restrict end, int base);
  long long int          strtoll(const char* __restrict s, char** __restrict end, int base);
  unsigned long int      strtoul(const char* __restrict s, char** __restrict end, int base);
  unsigned long long int strtoull(const char* __restrict s, char** __restrict end, int base);

  div_t   div(int numer, int denom);
  ldiv_t  ldiv(long int numer, long int denom);
  lldiv_t lldiv(long long int numer, long long int denom);

  int abs(int x);

  void* malloc(size_t size);
  void* calloc(size_t num, size_t size);
  void* realloc(void* ptr, size_t size);
  void* aligned_alloc(size_t alignment, size_t size);
  void  free(void* ptr);

  __noreturn void abort(void);
  __noreturn void exit(int status);
  __noreturn void _Exit(int status);
  int             atexit(void (*func)(void));
  __noreturn void quick_exit(int status);
  int             at_quick_exit(void (*func)(void));

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // CAPRESE_LIBC_STDLIB_H_
