#ifndef CAPRESE_LIBC_INTERNAL_CXX_NEW_OPERATOR_H_
#define CAPRESE_LIBC_INTERNAL_CXX_NEW_OPERATOR_H_

#include <internal/attribute.h>
#include <internal/cxx/new/align_val.h>
#include <internal/cxx/new/bad_alloc.h>
#include <internal/cxx/new/nothrow.h>
#include <internal/cxx/stddef.h>

__nodiscard_cxx_std_20 void* operator new(std::__size_t size) __throw_cxx_std_03(std::bad_alloc);
__nodiscard_cxx_std_20 void* operator new(std::__size_t size, const std::nothrow_t&) __noexcept;
__nodiscard_cxx_std_20 void* operator new(std::__size_t size, void* ptr) __noexcept;

#ifdef __CXX_STD_17__
__nodiscard_cxx_std_20 void* operator new(std::__size_t size, std::align_val_t alignment);
__nodiscard_cxx_std_20 void* operator new(std::__size_t size, std::align_val_t alignment, const std::nothrow_t&) __noexcept;
#endif // __CXX_STD_17__

__nodiscard_cxx_std_20 void* operator new[](std::__size_t size) __throw_cxx_std_03(std::bad_alloc);
__nodiscard_cxx_std_20 void* operator new[](std::__size_t size, const std::nothrow_t&) __noexcept;
__nodiscard_cxx_std_20 void* operator new[](std::__size_t size, void* ptr) __noexcept;

#ifdef __CXX_STD_17__
__nodiscard_cxx_std_20 void* operator new[](std::__size_t size, std::align_val_t alignment);
__nodiscard_cxx_std_20 void* operator new[](std::__size_t size, std::align_val_t alignment, const std::nothrow_t&) __noexcept;
#endif // __CXX_STD_17__

void operator delete(void* ptr) __noexcept;
void operator delete(void* ptr, const std::nothrow_t&) __noexcept;
void operator delete(void* ptr, void*) __noexcept;

#ifdef __CXX_STD_14__
void operator delete(void* ptr, std::__size_t size) __noexcept;
#endif // __CXX_STD_14__

#ifdef __CXX_STD_17__
void operator delete(void* ptr, std::align_val_t alignment) __noexcept;
void operator delete(void* ptr, std::__size_t size, std::align_val_t alignment) __noexcept;
void operator delete(void* ptr, std::align_val_t alignment, const std::nothrow_t&) __noexcept;
#endif // __CXX_STD_17__

void operator delete[](void* ptr) __noexcept;
void operator delete[](void* ptr, const std::nothrow_t&) __noexcept;
void operator delete[](void* ptr, void*) __noexcept;

#ifdef __CXX_STD_14__
void operator delete[](void* ptr, std::__size_t size) __noexcept;
#endif // __CXX_STD_14__

#ifdef __CXX_STD_17__
void operator delete[](void* ptr, std::align_val_t alignment) __noexcept;
void operator delete[](void* ptr, std::__size_t size, std::align_val_t alignment) __noexcept;
void operator delete[](void* ptr, std::align_val_t alignment, const std::nothrow_t&) __noexcept;
#endif // __CXX_STD_17__

#endif // CAPRESE_LIBC_INTERNAL_CXX_NEW_OPERATOR_H_
