#ifndef CAPRESE_LIBC_FENV_H_
#define CAPRESE_LIBC_FENV_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  typedef size_t fenv_t;
  typedef size_t fexcept_t;

  extern const fenv_t  fe_dfl_env;
  extern const fenv_t* fe_dfl_env_p;

  int feclearexcept(int excepts);
  int fegetexceptflag(fexcept_t* flagp, int excepts);
  int feraiseexcept(int excepts);
  int fesetexceptflag(const fexcept_t* flagp, int excepts);
  int fetestexcept(int excepts);
  int fegetround(void);
  int fesetround(int round);
  int fegetenv(fenv_t* envp);
  int feholdexcept(fenv_t* envp);
  int fesetenv(const fenv_t* envp);
  int feupdateenv(const fenv_t* envp);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // CAPRESE_LIBC_FENV_H_
