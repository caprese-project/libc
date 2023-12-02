#ifndef CAPRESE_LIBC_INTERNAL_CXX_NEW_ALIGN_VAL_H_
#define CAPRESE_LIBC_INTERNAL_CXX_NEW_ALIGN_VAL_H_

#include <internal/cxx/stddef.h>
#include <internal/version.h>

namespace std {
#ifdef __CXX_STD_17__

  enum class align_val_t : __size_t {
  };

#endif // __CXX_STD_17__
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_NEW_ALIGN_VAL_H_
