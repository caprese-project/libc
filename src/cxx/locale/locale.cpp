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

  locale::locale() __noexcept: _facets(nullptr), _facets_size(0) { }

  locale::locale(const locale& other) __noexcept: _facets(nullptr), _facets_size(other._facets_size) {
    if (other._facets != nullptr) {
      _facets = new facet*[other._facets_size];

      for (__size_t i = 0; i < other._facets_size; i++) {
        _facets[i] = other._facets[i];
        _facets[i]->refs++;
      }
    }
  }

  const locale& locale::operator=(const locale& other) __noexcept {
    this->~locale();

    _facets_size = other._facets_size;
    if (other._facets != nullptr) {
      _facets = new facet*[other._facets_size];

      for (__size_t i = 0; i < other._facets_size; i++) {
        _facets[i] = other._facets[i];
        _facets[i]->refs++;
      }
    }

    return *this;
  }

  locale::~locale() {
    if (_facets) {
      for (__size_t i = 0; i < _facets_size; i++) {
        if (_facets[i]->refs == 0) {
          delete _facets[i];
        } else {
          _facets[i]->refs--;
        }
      }

      delete[] _facets;
      _facets = nullptr;
    }
  }

  struct __classic_locale {
    locale loc;

    __classic_locale() {
      loc._facets_size = 3;
      loc._facets      = new locale::facet*[loc._facets_size];
      loc._facets[0]   = new ctype<char>(ctype<char>::classic_table(), false, 1);
      loc._facets[1]   = new num_get<char>(1);
      loc._facets[2]   = new num_put<char>(1);
    }
  };

  const locale& locale::classic() {
    static __classic_locale classic_locale;

    return classic_locale.loc;
  }
} // namespace std
