#ifndef CAPRESE_LIBC_INTERNAL_CXX_LOCALE_LOCALE_H_
#define CAPRESE_LIBC_INTERNAL_CXX_LOCALE_LOCALE_H_

#include <internal/attribute.h>
#include <internal/cxx/stddef.h>

namespace std {
  class locale {
  public:
    class id {
      friend class locale;

    public:
      id()                     = default;
      id(const id&)            = delete;
      id& operator=(const id&) = delete;
    };

    class facet {
      friend class locale;

    private:
      __size_t refs;

    protected:
      explicit facet(__size_t refs = 0);
      virtual ~facet() __noexcept;

      facet(const facet&)            = delete;
      facet& operator=(const facet&) = delete;
    };

    friend class facet;

    template<typename Facet>
    friend bool has_facet(const locale&) __noexcept;

    template<typename Facet>
    friend const Facet& use_facet(const locale&);

    using category = int;

    static constexpr category none     = 0x000;
    static constexpr category collate  = 0x010;
    static constexpr category ctype    = 0x020;
    static constexpr category monetary = 0x040;
    static constexpr category numeric  = 0x080;
    static constexpr category time     = 0x100;
    static constexpr category messages = 0x200;
    static constexpr category all      = collate | ctype | monetary | numeric | time | messages;

  public:
    locale() __noexcept;
    locale(const locale& other) __noexcept;
    const locale& operator=(const locale& other) __noexcept;
    ~locale();
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_LOCALE_LOCALE_H_
