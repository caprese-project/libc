#ifndef CAPRESE_LIBC_ERRNO_H_
#define CAPRESE_LIBC_ERRNO_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  int* __errno(void);

#define errno (*__errno())

#define ERANGE 1
#define EINVAL 2
#define EIO    3
#define ENOSYS 4

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // CAPRESE_LIBC_ERRNO_H_
