#ifndef CAPRESE_LIBC_INTTYPES_H_
#define CAPRESE_LIBC_INTTYPES_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  typedef struct {
    intmax_t quot;
    intmax_t rem;
  } imaxdiv_t;

  intmax_t  imaxabs(intmax_t j);
  imaxdiv_t imaxdiv(intmax_t numer, intmax_t denom);
  intmax_t  strtoimax(const char* __restrict nptr, char** __restrict end, int base);
  uintmax_t strtoumax(const char* __restrict nptr, char** __restrict endptr, int base);
  intmax_t  wcstoimax(const wchar_t* __restrict nptr, wchar_t** __restrict end, int base);
  uintmax_t wcstoumax(const wchar_t* __restrict nptr, wchar_t** __restrict end, int base);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // CAPRESE_LIBC_INTTYPES_H_
