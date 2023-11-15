#ifndef CAPRESE_LIBC_SIGNAL_H_
#define CAPRESE_LIBC_SIGNAL_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  typedef int sig_atomic_t;

  int raise(int sig);
  void (*signal(int sig, void (*handler)(int)))(int);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#define SIG_DFL ((void (*)(int))0)
#define SIG_ERR ((void (*)(int)) - 1)
#define SIG_IGN ((void (*)(int))1)

#define SIGABRT 0
#define SIGFPE  1
#define SIGILL  2
#define SIGINT  3
#define SIGSEGV 4
#define SIGTERM 5
#define NSIG    6

#endif // CAPRESE_LIBC_SIGNAL_H_
