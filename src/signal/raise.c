#include <errno.h>
#include <internal/attribute.h>
#include <internal/branch.h>
#include <signal.h>

__weak int raise(__unused int sig) {
  return -1;
}
