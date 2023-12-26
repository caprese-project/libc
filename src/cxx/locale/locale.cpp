#include <internal/cxx/locale/ctype.h>
#include <internal/cxx/locale/locale.h>
#include <internal/cxx/locale/num_get.h>
#include <internal/cxx/locale/num_put.h>

namespace std {
  namespace {
    __size_t last_locale_id = 0;
  } // namespace

  locale::facet::facet(__size_t refs): refs(refs) { }

  locale::facet::~facet() __noexcept { }

  locale::id::id(): _val(0) {
    ++last_locale_id;
    _val = last_locale_id;
  }

  void locale::_install_facet(facet* f, __size_t id) {
    if (id >= _facets.size()) {
      _facets.resize(id + 1);
    }

    _facets[id] = f;
  }

  locale::locale() __noexcept: locale(locale::global()) { }

  locale::locale(const locale& other) __noexcept {
    for (facet* facet : other._facets) {
      if (facet != nullptr) {
        ++facet->refs;
      }
    }
    _facets = other._facets;
  }

  locale::~locale() {
    for (facet* facet : _facets) {
      --facet->refs;
      if (facet->refs == 0) {
        delete facet;
      }
    }
  }

  struct __classic_locale {
    locale loc;

    __classic_locale() {
      loc._install_facet(new ctype<char>(ctype<char>::classic_table(), false, 1), ctype<char>::id.__get());
      loc._install_facet(new num_get<char>(1), num_get<char>::id.__get());
      loc._install_facet(new num_put<char>(1), num_put<char>::id.__get());
    }
  };

  const locale& locale::global() {
    static locale global_locale = locale::classic();
    return global_locale;
  }

  const locale& locale::classic() {
    static __classic_locale classic_locale;

    return classic_locale.loc;
  }
} // namespace std
