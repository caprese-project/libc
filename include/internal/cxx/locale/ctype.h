#ifndef CAPRESE_LIBC_INTERNAL_CXX_LOCALE_CTYPE_H_
#define CAPRESE_LIBC_INTERNAL_CXX_LOCALE_CTYPE_H_

#include <cctype>
#include <internal/cxx/fwd/localefwd.h>
#include <internal/cxx/locale/locale.h>

namespace std {
  class ctype_base {
  public:
    using mask = unsigned char;

    static constexpr mask space  = __CTYPE_SPACE_CHAR;
    static constexpr mask print  = __CTYPE_UPPER_CHAR | __CTYPE_LOWER_CHAR | __CTYPE_NUMBER_CHAR | __CTYPE_PUNCT_CHAR | __CTYPE_BLANK_CHAR;
    static constexpr mask cntrl  = __CTYPE_CTRL_CHAR;
    static constexpr mask upper  = __CTYPE_UPPER_CHAR;
    static constexpr mask lower  = __CTYPE_LOWER_CHAR;
    static constexpr mask alpha  = __CTYPE_UPPER_CHAR | __CTYPE_LOWER_CHAR;
    static constexpr mask digit  = __CTYPE_NUMBER_CHAR;
    static constexpr mask punct  = __CTYPE_PUNCT_CHAR;
    static constexpr mask xdigit = __CTYPE_NUMBER_CHAR | __CTYPE_HEX_CHAR;
    static constexpr mask blank  = __CTYPE_BLANK_CHAR;
    static constexpr mask alnum  = alpha | digit;
    static constexpr mask graph  = alnum | punct;
  };

  template<typename Char>
  class __ctype_helper: public locale::facet, public ctype_base {
  public:
    using char_type = Char;

  protected:
  protected:
    explicit __ctype_helper(__size_t refs = 0): locale::facet(refs) { }

    virtual ~__ctype_helper() { }

    virtual bool             do_is(mask m, char_type ch) const                                                 = 0;
    virtual bool             do_is(const char_type* low, const char_type* high, mask* vec) const               = 0;
    virtual bool             do_scan_is(mask m, const char_type* beg, const char_type* end) const              = 0;
    virtual const char_type* do_scan_not(mask m, const char_type* beg, const char_type* end) const             = 0;
    virtual char_type        do_toupper(char_type ch) const                                                    = 0;
    virtual const char_type* do_toupper(char_type* beg, const char_type* end) const                            = 0;
    virtual char_type        do_tolower(char_type ch) const                                                    = 0;
    virtual char_type        do_tolower(char_type* beg, const char_type* end) const                            = 0;
    virtual char_type        do_widen(char ch) const                                                           = 0;
    virtual const char*      do_widen(const char* beg, const char* end, char_type* dst) const                  = 0;
    virtual char             do_narrow(char_type ch, char dflt) const                                          = 0;
    virtual const char_type* do_narrow(const char_type* beg, const char_type* end, char dflt, char* dst) const = 0;

  public:
    bool is(mask m, char_type ch) const {
      return do_is(m, ch);
    }

    const char_type* is(const char_type* low, const char_type* high, mask* vec) const {
      return do_is(low, high, vec);
    }

    const char_type* scan_is(mask m, const char_type* beg, const char_type* end) const {
      return do_scan_is(m, beg, end);
    }

    const char_type* scan_not(mask m, const char_type* beg, const char_type* end) const {
      return do_scan_not(m, beg, end);
    }

    char_type toupper(char_type ch) const {
      return do_toupper(ch);
    }

    const char_type* toupper(char_type* beg, const char_type* end) const {
      return do_toupper(beg, end);
    }

    char_type tolower(char_type ch) const {
      return do_tolower(ch);
    }

    const char_type* tolower(char_type* beg, const char_type* end) const {
      return do_tolower(beg, end);
    }

    char_type widen(char ch) const {
      return do_widen(ch);
    }

    const char* widen(const char* beg, const char* end, char_type* dst) const {
      return do_widen(beg, end, dst);
    }

    char narrow(char_type ch, char dflt) const {
      return do_narrow(ch, dflt);
    }

    const char_type* narrow(const char_type* beg, const char_type* end, char dflt, char* dst) const {
      return do_narrow(beg, end, dflt, dst);
    }
  };

  template<typename Char>
  class ctype: public __ctype_helper<Char> {
  public:
    using char_type = typename __ctype_helper<Char>::char_type;
    using mask      = typename __ctype_helper<Char>::mask;

  public:
    static locale::id id;

  protected:
    virtual ~ctype();

    virtual bool             do_is(mask m, char_type ch) const;
    virtual bool             do_is(const char_type* low, const char_type* high, mask* vec) const;
    virtual bool             do_scan_is(mask m, const char_type* beg, const char_type* end) const;
    virtual const char_type* do_scan_not(mask m, const char_type* beg, const char_type* end) const;
    virtual char_type        do_toupper(char_type ch) const;
    virtual const char_type* do_toupper(char_type* beg, const char_type* end) const;
    virtual char_type        do_tolower(char_type ch) const;
    virtual char_type        do_tolower(char_type* beg, const char_type* end) const;
    virtual char_type        do_widen(char ch) const;
    virtual const char*      do_widen(const char* beg, const char* end, char_type* dst) const;
    virtual char             do_narrow(char_type ch, char dflt) const;
    virtual const char_type* do_narrow(const char_type* beg, const char_type* end, char dflt, char* dst) const;

  public:
    explicit ctype(__size_t refs = 0): __ctype_helper<Char>(refs) { }
  };

  template<typename Char>
  locale::id ctype<Char>::id;

  template<>
  class ctype<char>: public locale::facet, public ctype_base {
  public:
    using char_type = char;
    using mask      = ctype_base::mask;

  protected:
    bool        _del;
    const mask* _table;

  public:
    static locale::id id;

  public:
    static const mask* classic_table() __noexcept;

  protected:
    virtual ~ctype();

    virtual char        do_toupper(char ch) const;
    virtual const char* do_toupper(char* low, const char* high) const;
    virtual char        do_tolower(char ch) const;
    virtual const char* do_tolower(char* low, const char* high) const;
    virtual char        do_widen(char ch) const;
    virtual const char* do_widen(const char* low, const char* high, char* dst) const;
    virtual char        do_narrow(char ch, char dflt) const;
    virtual const char* do_narrow(const char* low, const char* high, char dflt, char* dst) const;

  public:
    explicit ctype(const mask* table = nullptr, bool del = false, __size_t refs = 0);

    const mask* table() const __noexcept;

    bool        is(mask m, char ch) const;
    const char* is(const char* low, const char* high, mask* vec) const;
    const char* scan_is(mask m, const char* beg, const char* end) const;
    const char* scan_not(mask m, const char* beg, const char* end) const;
    char        toupper(char ch) const;
    const char* toupper(char* beg, const char* end) const;
    char        tolower(char ch) const;
    const char* tolower(char* beg, const char* end) const;
    char        widen(char ch) const;
    const char* widen(const char* beg, const char* end, char* dst) const;
    char        narrow(char ch, char dflt) const;
    const char* narrow(const char* beg, const char* end, char dflt, char* dst) const;
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_LOCALE_CTYPE_H_
