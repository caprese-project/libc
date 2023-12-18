#ifndef CAPRESE_LIBC_INTERNAL_CXX_IOS_IOS_BASE_H_
#define CAPRESE_LIBC_INTERNAL_CXX_IOS_IOS_BASE_H_

#include <cstdint>
#include <internal/cxx/ios/types.h>
#include <internal/cxx/system_error/system_error.h>
#include <internal/version.h>

namespace std {
  class ios_base {
  public:
    class failure: public system_error { };

    enum struct __ios_base_bits : uint32_t {
      __fmtflags_boolalpha_bit  = 1 << 0,
      __fmtflags_dec_bit        = 1 << 1,
      __fmtflags_fixed_bit      = 1 << 2,
      __fmtflags_hex_bit        = 1 << 3,
      __fmtflags_internal_bit   = 1 << 4,
      __fmtflags_left_bit       = 1 << 5,
      __fmtflags_oct_bit        = 1 << 6,
      __fmtflags_right_bit      = 1 << 7,
      __fmtflags_scientific_bit = 1 << 8,
      __fmtflags_showbase_bit   = 1 << 9,
      __fmtflags_showpoint_bit  = 1 << 10,
      __fmtflags_showpos_bit    = 1 << 11,
      __fmtflags_skipws_bit     = 1 << 12,
      __fmtflags_unitbuf_bit    = 1 << 13,
      __fmtflags_uppercase_bit  = 1 << 14,
      __iostate_bad_bit         = 1 << 15,
      __iostate_eof_bit         = 1 << 16,
      __iostate_fail_bit        = 1 << 17,
      __openmode_app_bit        = 1 << 18,
      __openmode_ate_bit        = 1 << 19,
      __openmode_binary_bit     = 1 << 20,
      __openmode_in_bit         = 1 << 21,
      __openmode_out_bit        = 1 << 22,
      __openmode_noreplace_bit  = 1 << 23,
      __openmode_trunc_bit      = 1 << 24,
      __seekdir_beg_bit         = 1 << 25,
      __seekdir_cur_bit         = 1 << 26,
      __seekdir_end_bit         = 1 << 27,
    };

    using fmtflags = uint32_t;
    using iostate  = uint32_t;
    using openmode = uint32_t;
    using seekdir  = uint32_t;

    enum event {
      erase_event,
      imbue_event,
      copyfmt_event,
    };

    using event_callback = void (*)(event, ios_base&, int);

    class Init {
    public:
      Init();
      Init(const Init&)            = default;
      Init& operator=(const Init&) = default;
      ~Init();
    };

    static constexpr fmtflags boolalpha   = static_cast<fmtflags>(__ios_base_bits::__fmtflags_boolalpha_bit);
    static constexpr fmtflags dec         = static_cast<fmtflags>(__ios_base_bits::__fmtflags_dec_bit);
    static constexpr fmtflags fixed       = static_cast<fmtflags>(__ios_base_bits::__fmtflags_fixed_bit);
    static constexpr fmtflags hex         = static_cast<fmtflags>(__ios_base_bits::__fmtflags_hex_bit);
    static constexpr fmtflags internal    = static_cast<fmtflags>(__ios_base_bits::__fmtflags_internal_bit);
    static constexpr fmtflags left        = static_cast<fmtflags>(__ios_base_bits::__fmtflags_left_bit);
    static constexpr fmtflags oct         = static_cast<fmtflags>(__ios_base_bits::__fmtflags_oct_bit);
    static constexpr fmtflags right       = static_cast<fmtflags>(__ios_base_bits::__fmtflags_right_bit);
    static constexpr fmtflags scientific  = static_cast<fmtflags>(__ios_base_bits::__fmtflags_scientific_bit);
    static constexpr fmtflags showbase    = static_cast<fmtflags>(__ios_base_bits::__fmtflags_showbase_bit);
    static constexpr fmtflags showpoint   = static_cast<fmtflags>(__ios_base_bits::__fmtflags_showpoint_bit);
    static constexpr fmtflags showpos     = static_cast<fmtflags>(__ios_base_bits::__fmtflags_showpos_bit);
    static constexpr fmtflags skipws      = static_cast<fmtflags>(__ios_base_bits::__fmtflags_skipws_bit);
    static constexpr fmtflags unitbuf     = static_cast<fmtflags>(__ios_base_bits::__fmtflags_unitbuf_bit);
    static constexpr fmtflags uppercase   = static_cast<fmtflags>(__ios_base_bits::__fmtflags_uppercase_bit);
    static constexpr fmtflags adjustfield = left | right | internal;
    static constexpr fmtflags basefield   = dec | oct | hex;
    static constexpr fmtflags floatfield  = scientific | fixed;

    static constexpr iostate badbit  = static_cast<iostate>(__ios_base_bits::__iostate_bad_bit);
    static constexpr iostate eofbit  = static_cast<iostate>(__ios_base_bits::__iostate_eof_bit);
    static constexpr iostate failbit = static_cast<iostate>(__ios_base_bits::__iostate_fail_bit);
    static constexpr iostate goodbit = static_cast<iostate>(0);

    static constexpr openmode app    = static_cast<openmode>(__ios_base_bits::__openmode_app_bit);
    static constexpr openmode ate    = static_cast<openmode>(__ios_base_bits::__openmode_ate_bit);
    static constexpr openmode binary = static_cast<openmode>(__ios_base_bits::__openmode_binary_bit);
    static constexpr openmode in     = static_cast<openmode>(__ios_base_bits::__openmode_in_bit);
    static constexpr openmode out    = static_cast<openmode>(__ios_base_bits::__openmode_out_bit);
    static constexpr openmode trunc  = static_cast<openmode>(__ios_base_bits::__openmode_trunc_bit);

#ifndef __CXX_STD_23__
    static constexpr openmode noreplace = static_cast<openmode>(__ios_base_bits::__openmode_noreplace_bit);
#endif // __CXX_STD_23__

    static constexpr seekdir beg = static_cast<seekdir>(__ios_base_bits::__seekdir_beg_bit);
    static constexpr seekdir cur = static_cast<seekdir>(__ios_base_bits::__seekdir_cur_bit);
    static constexpr seekdir end = static_cast<seekdir>(__ios_base_bits::__seekdir_end_bit);

  private:
    static constexpr fmtflags _fmtflags_mask = (uppercase << 1) - 1;
    static constexpr iostate  _iostate_mask  = ((failbit << 1) - 1) & ~_fmtflags_mask;
    static constexpr openmode _openmode_mask = ((trunc << 1) - 1) & ~(_fmtflags_mask | _iostate_mask);
    static constexpr seekdir  _seekdir_mask  = ((end << 1) - 1) & ~(_fmtflags_mask | _iostate_mask | _openmode_mask);

    __ios_base_bits _ios_base_bits;
    streamsize      _prec;
    streamsize      _wide;

  protected:
    ios_base() = default;

    void     _init();
    void     _set_fmtflags(fmtflags fmtfl);
    fmtflags _get_fmtflags() const;
    void     _set_iostate(iostate iostate);
    iostate  _get_iostate() const;
    void     _set_openmode(openmode openmode);
    openmode _get_openmode() const;
    void     _set_seekdir(seekdir seekdir);
    seekdir  _get_seekdir() const;
    void     _move(ios_base& other);
    void     _swap(ios_base& other);

  public:
    bool _is_boolalpha() const;
    bool _is_showbase() const;
    bool _is_showpoint() const;
    bool _is_showpos() const;
    bool _is_skipws() const;
    bool _is_uppercase() const;
    bool _is_unitbuf() const;
    bool _is_internal() const;
    bool _is_left() const;
    bool _is_right() const;
    bool _is_dec() const;
    bool _is_hex() const;
    bool _is_oct() const;
    bool _is_fixed() const;
    bool _is_scientific() const;
    bool _is_hexfloat() const;
    bool _is_defaultfloat() const;
    bool _is_adjustfield_unset() const;
    bool _is_basefield_unset() const;
    bool _is_floatfield_unset() const;

    ios_base(const ios_base&)            = delete;
    ios_base& operator=(const ios_base&) = delete;

    virtual ~ios_base();

    fmtflags flags() const;
    fmtflags flags(fmtflags fmtfl);

    fmtflags setf(fmtflags fmtfl);
    fmtflags setf(fmtflags fmtfl, fmtflags mask);

    fmtflags unsetf(fmtflags mask);

    streamsize precision() const;
    streamsize precision(streamsize prec);

    streamsize width() const;
    streamsize width(streamsize wide);

    void register_callback(event_callback cb, int index);
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_IOS_IOS_BASE_H_
