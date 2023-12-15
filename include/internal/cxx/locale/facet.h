#ifndef CAPRESE_LIBC_INTERNAL_CXX_LOCALE_FACET_H_
#define CAPRESE_LIBC_INTERNAL_CXX_LOCALE_FACET_H_

#include <internal/attribute.h>
#include <internal/cxx/fwd/localefwd.h>
#include <internal/cxx/locale/locale.h>
#include <internal/cxx/typeinfo/exception.h>
#include <internal/exception.h>

namespace std {
  template<typename Facet>
  bool has_facet(const locale& loc) __noexcept {
    if (Facet::id.__get() < loc._facets.size()) {
#if __cpp_rtti
      return dynamic_cast<const Facet*>(loc._facets[Facet::id.__get()]) != nullptr;
#else
      return static_cast<const Facet*>(loc._facets[Facet::id.__get()]) != nullptr;
#endif // !__cpp_rtti
    } else {
      return false;
    }
  }

  template<typename Facet>
  const Facet& use_facet(const locale& loc) {
    if (!has_facet<Facet>(loc)) {
      __throw_exception(bad_cast());
    }

#if __cpp_rtti
    return dynamic_cast<const Facet&>(*loc._facets[Facet::id.__get()]);
#else
    return static_cast<const Facet&>(*loc._facets[Facet::id.__get()]);
#endif
  }
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_LOCALE_FACET_H_
