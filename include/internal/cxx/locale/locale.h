#ifndef CAPRESE_LIBC_INTERNAL_CXX_LOCALE_LOCALE_H_
#define CAPRESE_LIBC_INTERNAL_CXX_LOCALE_LOCALE_H_

#include <internal/attribute.h>
#include <internal/cxx/memory/allocator.h>
#include <internal/cxx/stddef.h>
#include <internal/cxx/stl_base/vec_storage.h>
#include <internal/cxx/stl_base/vla.h>

namespace std {
  class locale {
    template<typename T>
    using __container_type = __vla<__vector_storage<T, allocator<T>>>;

  public:
    class facet {
      friend class locale;

      template<typename Facet>
      friend bool has_facet(const locale&) __noexcept;

      template<typename Facet>
      friend const Facet& use_facet(const locale&);

    private:
      __size_t refs;

    protected:
      explicit facet(__size_t refs = 0);
      virtual ~facet() __noexcept;

      facet(const facet&)            = delete;
      facet& operator=(const facet&) = delete;
    };

    class id {
      __size_t _val;

    public:
      id();
      id(const id&)            = delete;
      id& operator=(const id&) = delete;

      inline __size_t __get() const {
        return _val;
      }
    };

    friend class facet;

    friend struct __classic_locale;

    template<typename Facet>
    friend bool has_facet(const locale&) __noexcept;

    template<typename Facet>
    friend const Facet& use_facet(const locale&);

    using category = int;

  public:
    static constexpr category none     = 0x000;
    static constexpr category collate  = 0x010;
    static constexpr category ctype    = 0x020;
    static constexpr category monetary = 0x040;
    static constexpr category numeric  = 0x080;
    static constexpr category time     = 0x100;
    static constexpr category messages = 0x200;
    static constexpr category all      = collate | ctype | monetary | numeric | time | messages;

    static const locale& classic();

  protected:
    __container_type<facet*> _facets;

  protected:
    void _install_facet(facet* f, __size_t id);
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_LOCALE_LOCALE_H_
