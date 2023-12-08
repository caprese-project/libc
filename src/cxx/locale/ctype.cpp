#include <cctype>
#include <cstring>
#include <internal/cxx/locale/ctype.h>

namespace std {
  ctype<char>::ctype(const mask* table, bool del, __size_t refs): locale::facet(refs), _table(table), _del(del) { }

  ctype<char>::~ctype() {
    if (_del) {
      delete[] _table;
      _table = nullptr;
    }
  }

  const ctype<char>::mask* ctype<char>::classic_table() __noexcept {
    return ::__ctype_table;
  }

  char ctype<char>::do_toupper(char ch) const {
    if (table()[ch] & lower) {
      return ch - 'a' + 'A';
    } else {
      return ch;
    }
  }

  const char* ctype<char>::do_toupper(char* low, const char* high) const {
    while (low != high) {
      *low = do_toupper(*low);
      ++low;
    }

    return high;
  }

  char ctype<char>::do_tolower(char ch) const {
    if (table()[ch] & upper) {
      return ch - 'A' + 'a';
    } else {
      return ch;
    }
  }

  const char* ctype<char>::do_tolower(char* low, const char* high) const {
    while (low != high) {
      *low = do_tolower(*low);
      ++low;
    }

    return high;
  }

  char ctype<char>::do_widen(char ch) const {
    return ch;
  }

  const char* ctype<char>::do_widen(const char* low, const char* high, char* dst) const {
    if (low != high) {
      memcpy(dst, low, high - low);
    }
    return high;
  }

  char ctype<char>::do_narrow(char ch, char dflt) const {
    if (ch <= '\x7f') {
      return ch;
    } else {
      return dflt;
    }
  }

  const char* ctype<char>::do_narrow(const char* low, const char* high, char dflt, char* dst) const {
    while (low != high) {
      *dst = do_narrow(*low, dflt);
      ++low;
      ++dst;
    }

    return high;
  }

  const ctype<char>::mask* ctype<char>::table() const __noexcept {
    if (_table != nullptr) {
      return _table;
    }

    return ctype<char>::classic_table();
  }

  bool ctype<char>::is(mask m, char ch) const {
    return table()[ch] & m;
  }

  const char* ctype<char>::is(const char* low, const char* high, mask* vec) const {
    while (low != high) {
      *vec = table()[*low];
      ++low;
      ++vec;
    }

    return high;
  }

  const char* ctype<char>::scan_is(mask m, const char* beg, const char* end) const {
    while (beg != end) {
      if (table()[*beg] & m) {
        return beg;
      }
      ++beg;
    }

    return end;
  }

  const char* ctype<char>::scan_not(mask m, const char* beg, const char* end) const {
    while (beg != end) {
      if (!(table()[*beg] & m)) {
        return beg;
      }
      ++beg;
    }

    return end;
  }

  char ctype<char>::toupper(char ch) const {
    return do_toupper(ch);
  }

  const char* ctype<char>::toupper(char* beg, const char* end) const {
    return do_toupper(beg, end);
  }

  char ctype<char>::tolower(char ch) const {
    return do_tolower(ch);
  }

  const char* ctype<char>::tolower(char* beg, const char* end) const {
    return do_tolower(beg, end);
  }

  char ctype<char>::widen(char ch) const {
    return do_widen(ch);
  }

  const char* ctype<char>::widen(const char* beg, const char* end, char* dst) const {
    return do_widen(beg, end, dst);
  }

  char ctype<char>::narrow(char ch, char dflt) const {
    return do_narrow(ch, dflt);
  }

  const char* ctype<char>::narrow(const char* beg, const char* end, char dflt, char* dst) const {
    return do_narrow(beg, end, dflt, dst);
  }
} // namespace std
