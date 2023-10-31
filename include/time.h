#ifndef CAPRESE_LIBC_TIME_H_
#define CAPRESE_LIBC_TIME_H_

#include <internal/attribute.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  struct tm {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
  };

  clock_t    clock(void);
  double     difftime(time_t time1, time_t time0);
  time_t     mktime(struct tm* timeptr);
  time_t     time(time_t* timer);
  int        timespec_get(struct timespec* ts, int base);
  char*      asctime(const struct tm* timeptr);
  char*      ctime(const time_t* timer);
  struct tm* gmtime(const time_t* timer);
  struct tm* localtime(const time_t* timer);
  size_t     strftime(char* __restrict s, size_t maxsize, const char* __restrict format, const struct tm* __restrict timeptr);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // CAPRESE_LIBC_TIME_H_
