#include <internal/cxx/__cxxabi/guard.h>
#include <stdatomic.h>

namespace __cxxabiv1 {
  extern "C" {
    int __cxa_guard_acquire(int* guard) noexcept {
      if (atomic_exchange_explicit(reinterpret_cast<atomic_int*>(guard), 1, memory_order_acquire) != 0) {
        return 0;
      }
      return 1;
    }
  }
} // namespace __cxxabiv1
