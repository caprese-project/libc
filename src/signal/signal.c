#include <errno.h>
#include <internal/attribute.h>
#include <internal/branch.h>
#include <signal.h>

__weak void (*signal(__unused int sig, __unused void (*handler)(int)))(int) {
  return SIG_ERR;
}
