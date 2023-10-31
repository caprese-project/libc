#include <errno.h>
#include <internal/attribute.h>
#include <internal/branch.h>
#include <signal.h>

extern __signal_handler_t __signal(int sig, __signal_handler_t handler);

__weak __signal_handler_t signal(int sig, __signal_handler_t handler) {
  return __signal(sig, handler);
}
