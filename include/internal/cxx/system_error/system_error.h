#ifndef CAPRESE_LIBC_INTERNAL_CXX_SYSTEM_ERROR_SYSTEM_ERROR_H_
#define CAPRESE_LIBC_INTERNAL_CXX_SYSTEM_ERROR_SYSTEM_ERROR_H_

#include <internal/cxx/stdexcept/runtime_error.h>

namespace std {
  class system_error : public runtime_error {};
}

#endif // CAPRESE_LIBC_INTERNAL_CXX_SYSTEM_ERROR_SYSTEM_ERROR_H_
