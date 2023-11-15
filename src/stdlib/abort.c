#include <internal/attribute.h>
#include <internal/unreachable.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>

__weak __noreturn void abort(void) {
  raise(SIGABRT);
  signal(SIGABRT, SIG_DFL);
  raise(SIGABRT);
  __unreachable();
}
