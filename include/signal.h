#ifndef CAPRESE_LIBC_SIGNAL_H_
#define CAPRESE_LIBC_SIGNAL_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef __signal_handle_t_defined
#define __signal_handle_t_defined
  typedef void (*__signal_handler_t)(int);
#endif // __signal_handle_t_defined

  typedef int sig_atomic_t;

  int                raise(int sig);
  __signal_handler_t signal(int sig, __signal_handler_t handler);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#define SIG_DFL ((__signal_handler_t)0)
#define SIG_ERR ((__signal_handler_t)-1)
#define SIG_IGN ((__signal_handler_t)1)

#define SIGABRT 0
#define SIGFPE  1
#define SIGILL  2
#define SIGINT  3
#define SIGSEGV 4
#define SIGTERM 5
#define NSIG    6

#endif // CAPRESE_LIBC_SIGNAL_H_
