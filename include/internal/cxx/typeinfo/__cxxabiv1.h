#ifndef CAPRESE_LIBC_INTERNAL_CXX_TYPEINFO___CXXABIV1_H_
#define CAPRESE_LIBC_INTERNAL_CXX_TYPEINFO___CXXABIV1_H_

#include <cstddef>
#include <cstdint>
#include <internal/attribute.h>

namespace __cxxabiv1 {
  class __fundamental_type_info;
  class __array_type_info;
  class __function_type_info;
  class __enum_type_info;
  class __pbase_type_info;
  class __pointer_type_info;
  class __pointer_to_member_type_info;
  class __base_class_type_info;
  class __class_type_info;
  class __si_class_type_info;
  class __vmi_class_type_info;
} // namespace __cxxabiv1

namespace std {
  class type_info {
    type_info(const type_info&)            = delete;
    type_info& operator=(const type_info&) = delete;

  protected:
    const char* __name;

    explicit type_info(const char* name);

  public:
    virtual ~type_info();

    const char* name() const __noexcept;

    bool before(const type_info& rhs) const __noexcept;

    bool operator==(const type_info& rhs) const __noexcept;

    virtual bool __is_pointer_p() const;
    virtual bool __is_function_p() const;
    virtual bool __do_catch(const type_info*, void**, unsigned int) const;
    virtual bool __do_upcast(const ::__cxxabiv1::__class_type_info*, void**) const;
  };
} // namespace std

namespace __cxxabiv1 {
  using ::std::type_info;

  class __fundamental_type_info: public type_info {
  public:
    explicit __fundamental_type_info(const char*);
    virtual ~__fundamental_type_info() = default;
  };

  class __array_type_info: public type_info {
  public:
    explicit __array_type_info(const char*);
    virtual ~__array_type_info() = default;
  };

  class __function_type_info: public type_info {
  public:
    explicit __function_type_info(const char*);
    virtual ~__function_type_info() = default;

  protected:
    virtual bool __is_function_p() const;
  };

  class __enum_type_info: public type_info {
  public:
    explicit __enum_type_info(const char*);
    virtual ~__enum_type_info() = default;
  };

  class __pbase_type_info: public type_info {
  public:
    enum __masks {
      __const_mask            = 1 << 0,
      __volatile_mask         = 1 << 2,
      __restrict_mask         = 1 << 3,
      __incomplete_mask       = 1 << 4,
      __incomplete_class_mask = 1 << 5,
      __transaction_safe_mask = 1 << 6,
      __noexcept_mask         = 1 << 7,
    };

    unsigned int     __flags;
    const type_info* __pointee;

    explicit __pbase_type_info(const char*, int, const type_info*);
    virtual ~__pbase_type_info() = default;

  protected:
    __pbase_type_info(const __pbase_type_info&)            = default;
    __pbase_type_info& operator=(const __pbase_type_info&) = default;

    virtual bool __do_catch(const type_info*, void**, unsigned int) const;
    virtual bool __pointer_catch(const __pbase_type_info*, void**, unsigned int) const;
  };

  class __pointer_type_info: public __pbase_type_info {
  public:
    explicit __pointer_type_info(const char*, int, const type_info*);
    virtual ~__pointer_type_info() = default;

  protected:
    virtual bool __is_pointer_p() const;
    virtual bool __pointer_catch(const __pbase_type_info*, void**, unsigned int) const;
  };

  class __pointer_to_member_type_info: public __pbase_type_info {
  public:
    __class_type_info* __context;

    explicit __pointer_to_member_type_info(const char*, int, const type_info*, __class_type_info*);
    virtual ~__pointer_to_member_type_info() = default;

  protected:
    __pointer_to_member_type_info(const __pointer_to_member_type_info&)            = default;
    __pointer_to_member_type_info& operator=(const __pointer_to_member_type_info&) = default;

    virtual bool __pointer_catch(const __pbase_type_info*, void**, unsigned int) const;
  };

  struct __base_class_type_info {
    enum __offset_flag_masks {
      __virtual_mask = 1 << 0,
      __public_mask  = 1 << 1,
      __hwm_bit      = 2,
      __offset_shift = 1 << 3,
    };

    const __class_type_info* __base_type;
    int64_t                  __offset_flags;

    bool      __is_virtual_p() const;
    bool      __is_public_p() const;
    ptrdiff_t __offset() const;
  };

  class __class_type_info: public type_info {
  public:
    enum __sub_kind {
      __unknown = 0,
      __not_contained,
      __contained_ambig,
      __contained_virtual_mask = __base_class_type_info::__virtual_mask,
      __contained_public_mask  = __base_class_type_info::__public_mask,
      __contained_mask         = 1 << __base_class_type_info::__hwm_bit,
      __contained_private      = __contained_mask,
      __contained_public       = __contained_mask | __contained_public_mask,
    };

    struct __upcast_result {
      const void*              dst_ptr;
      __sub_kind               part2dst;
      int                      src_details;
      const __class_type_info* base_type;

      __upcast_result(int);
    };

    struct __dyncast_result {
      const void* dst_ptr;
      __sub_kind  whole2dst;
      __sub_kind  whole2src;
      __sub_kind  dst2src;
      int         whole_details;

      __dyncast_result(int = /* __vmi_class_type_info::__flags_unknown_mask */ 0x10);

    protected:
      __dyncast_result(const __dyncast_result&)            = default;
      __dyncast_result& operator=(const __dyncast_result&) = default;
    };

    explicit __class_type_info(const char*);
    virtual ~__class_type_info() = default;

  protected:
    virtual bool __do_upcast(const __class_type_info*, void**) const;
    virtual bool __do_catch(const type_info*, void**, unsigned int) const;

  public:
    virtual bool       __do_upcast(const __class_type_info*, const void*, __upcast_result& __restrict) const;
    __sub_kind         __find_public_src(ptrdiff_t, const void*, const __class_type_info*, const void*) const;
    virtual bool       __do_dyncast(ptrdiff_t, __sub_kind, const __class_type_info*, const void*, const __class_type_info*, const void*, __dyncast_result& __restrict) const;
    virtual __sub_kind __do_find_public_src(ptrdiff_t, const void*, const __class_type_info*, const void*) const;
  };

  class __si_class_type_info: public __class_type_info {
  public:
    const __class_type_info* __base_type;

    explicit __si_class_type_info(const char*, const __class_type_info*);
    virtual ~__si_class_type_info() = default;

  protected:
    __si_class_type_info(const __si_class_type_info&)            = default;
    __si_class_type_info& operator=(const __si_class_type_info&) = default;

    virtual bool       __do_dyncast(ptrdiff_t, __sub_kind, const __class_type_info*, const void*, const __class_type_info*, const void*, __dyncast_result& __restrict) const;
    virtual __sub_kind __do_find_public_src(ptrdiff_t, const void*, const __class_type_info*, const void*) const;
    virtual bool       __do_upcast(const __class_type_info*, const void*, __upcast_result& __restrict) const;
  };

  class __vmi_class_type_info: public __class_type_info {
  public:
    enum __flags_masks {
      __non_diamond_repeat_mask = 1 << 0,
      __diamond_shaped_mask     = 1 << 2,
      __flags_unknown_mask      = 1 << 4,
    };

    unsigned int           __flags;
    unsigned int           __base_count;
    __base_class_type_info __base_info[1];

    explicit __vmi_class_type_info(const char*, int);
    virtual ~__vmi_class_type_info() = default;

  protected:
    virtual bool       __do_dyncast(ptrdiff_t, __sub_kind, const __class_type_info*, const void*, const __class_type_info*, const void*, __dyncast_result& __restrict) const;
    virtual __sub_kind __do_find_public_src(ptrdiff_t, const void*, const __class_type_info*, const void*) const;
    virtual bool       __do_upcast(const __class_type_info*, const void*, __upcast_result& __restrict) const;
  };

  inline static bool contained_p(__class_type_info::__sub_kind access_path) {
    return access_path >= __class_type_info::__contained_mask;
  }

  inline static bool public_p(__class_type_info::__sub_kind access_path) {
    return access_path & __class_type_info::__contained_public_mask;
  }

  inline static bool virtual_p(__class_type_info::__sub_kind access_path) {
    return access_path & __class_type_info::__contained_virtual_mask;
  }

  inline static bool contained_public_p(__class_type_info::__sub_kind access_path) {
    return ((access_path & __class_type_info::__contained_public) == __class_type_info::__contained_public);
  }

  inline static bool contained_nonpublic_p(__class_type_info::__sub_kind access_path) {
    return ((access_path & __class_type_info::__contained_public) == __class_type_info::__contained_mask);
  }

  inline static bool contained_nonvirtual_p(__class_type_info::__sub_kind access_path) {
    return ((access_path & (__class_type_info::__contained_mask | __class_type_info::__contained_virtual_mask)) == __class_type_info::__contained_mask);
  }

  static const __class_type_info* const nonvirtual_base_type = static_cast<const __class_type_info*>(0) + 1;

  template<typename T>
  inline const T* adjust_pointer(const void* base, ptrdiff_t offset) {
    return reinterpret_cast<const T*>(reinterpret_cast<const char*>(base) + offset);
  }

  inline const void* convert_to_base(const void* addr, bool is_virtual, ptrdiff_t offset) {
    if (is_virtual) {
      const void* vtable = *static_cast<const void* const*>(addr);

      offset = *adjust_pointer<ptrdiff_t>(vtable, offset);
    }

    return adjust_pointer<void>(addr, offset);
  }
} // namespace __cxxabiv1

namespace std {
  using ::__cxxabiv1::type_info;
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_TYPEINFO___CXXABIV1_H_
