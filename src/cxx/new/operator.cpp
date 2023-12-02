#include <cstddef>
#include <cstdlib>
#include <internal/branch.h>
#include <internal/cxx/new/handler.h>
#include <internal/cxx/new/operator.h>

extern "C" {
  extern void* __alloc(void* ptr, std::__size_t size, std::__size_t alignment);
}

__weak void* operator new(std::__size_t size) __throw_cxx_std_03(std::bad_alloc) {
  __if_unlikely (size == 0) {
    size = 1;
  }

  void* ptr = ::__alloc(nullptr, size, sizeof(std::max_align_t));

  __if_unlikely (ptr == nullptr) {
    std::new_handler handler = std::get_new_handler();
    if (handler) {
      handler();
    } else {
      throw std::bad_alloc();
    }
  }

  return ptr;
}

__weak void* operator new(std::__size_t size, const std::nothrow_t&) __noexcept {
  void* ptr = nullptr;

  try {
    ptr = ::operator new(size);
  } catch (...) {
    // Do nothing.
  }

  return ptr;
}

__weak void* operator new(std::__size_t, void* ptr) __noexcept {
  return ptr;
}

#ifdef __CXX_STD_17__

__weak void* operator new(std::__size_t size, std::align_val_t alignment) {
  __if_unlikely (size == 0) {
    size = 1;
  }

  __if_unlikely (static_cast<std::__size_t>(alignment) < sizeof(void*)) {
    alignment = std::align_val_t(sizeof(void*));
  }

  void* ptr = ::__alloc(nullptr, size, static_cast<std::__size_t>(alignment));

  __if_unlikely (ptr == nullptr) {
    std::new_handler handler = std::get_new_handler();
    if (handler) {
      handler();
    } else {
      throw std::bad_alloc();
    }
  }

  return ptr;
}

__weak void* operator new(std::__size_t size, std::align_val_t alignment, const std::nothrow_t&) __noexcept {
  void* ptr = nullptr;

  try {
    ptr = ::operator new(size, alignment);
  } catch (...) {
    // Do nothing.
  }

  return ptr;
}

#endif // __CXX_STD_17__

__weak void* operator new[](std::__size_t size) __throw_cxx_std_03(std::bad_alloc) {
  return ::operator new(size);
}

__weak void* operator new[](std::__size_t size, const std::nothrow_t&) __noexcept {
  void* ptr = nullptr;

  try {
    ptr = ::operator new[](size);
  } catch (...) {
    // Do nothing.
  }

  return ptr;
}

__weak void* operator new[](std::__size_t, void* ptr) __noexcept {
  return ptr;
}

#ifdef __CXX_STD_17__

__weak void* operator new[](std::__size_t size, std::align_val_t alignment) {
  return ::operator new(size, alignment);
}

__weak void* operator new[](std::__size_t size, std::align_val_t alignment, const std::nothrow_t&) __noexcept {
  void* ptr = nullptr;

  try {
    ptr = ::operator new[](size, alignment);
  } catch (...) {
    // Do nothing.
  }

  return ptr;
}

#endif // __CXX_STD_17__

__weak void operator delete(void* ptr) __noexcept {
  ::free(ptr);
}

__weak void operator delete(void* ptr, const std::nothrow_t&) __noexcept {
  ::operator delete(ptr);
}

__weak void operator delete(void*, void*) __noexcept { }

#ifdef __CXX_STD_14__

__weak void operator delete(void* ptr, std::__size_t) __noexcept {
  ::operator delete(ptr);
}

#endif // __CXX_STD_14__

#ifdef __CXX_STD_17__

__weak void operator delete(void* ptr, std::align_val_t) __noexcept {
  ::operator delete(ptr);
}

__weak void operator delete(void* ptr, std::__size_t, std::align_val_t) __noexcept {
  ::operator delete(ptr);
}

__weak void operator delete(void* ptr, std::align_val_t, const std::nothrow_t&) __noexcept {
  ::operator delete(ptr);
}

#endif // __CXX_STD_17__

__weak void operator delete[](void* ptr) __noexcept {
  ::operator delete(ptr);
}

__weak void operator delete[](void* ptr, const std::nothrow_t&) __noexcept {
  ::operator delete[](ptr);
}

__weak void operator delete[](void*, void*) __noexcept { }

#ifdef __CXX_STD_14__

__weak void operator delete[](void* ptr, std::__size_t) __noexcept {
  ::operator delete[](ptr);
}

#endif // __CXX_STD_14__

#ifdef __CXX_STD_17__

__weak void operator delete[](void* ptr, std::align_val_t) __noexcept {
  ::operator delete[](ptr);
}

__weak void operator delete[](void* ptr, std::__size_t, std::align_val_t) __noexcept {
  ::operator delete[](ptr);
}

__weak void operator delete[](void* ptr, std::align_val_t, const std::nothrow_t&) __noexcept {
  ::operator delete[](ptr);
}

#endif // __CXX_STD_17__
