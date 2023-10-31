#include <errno.h>
#include <internal/attribute.h>
#include <internal/branch.h>
#include <signal.h>

extern int __raise(int sig);

__weak int raise(int sig) {
  return __raise(sig);
}
