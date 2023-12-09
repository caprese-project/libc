#include <internal/cxx/__cxxabi/guard.h>
#include <stdatomic.h>

namespace __cxxabiv1 {
  extern "C" {
    void __cxa_guard_release(int* guard) noexcept {
      atomic_store_explicit(reinterpret_cast<atomic_int*>(guard), 0, memory_order_release);
    }
  }
} // namespace __cxxabiv1
