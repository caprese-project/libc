#include <cassert>
#include <internal/cxx/ios/ios_base.h>
#include <internal/cxx/utility/swap.h>

namespace std {
  void ios_base::_init() {
    _ios_base_bits = static_cast<__ios_base_bits>(0);
    _prec          = 6;
    _wide          = 0;
  }

  void ios_base::_set_fmtflags(fmtflags fmtfl) {
    assert((fmtfl & _fmtflags_mask) == fmtfl);
    _ios_base_bits = static_cast<__ios_base_bits>((static_cast<fmtflags>(_ios_base_bits) & ~_fmtflags_mask) | fmtfl);
  }

  ios_base::fmtflags ios_base::_get_fmtflags() const {
    return static_cast<fmtflags>(_ios_base_bits) & _fmtflags_mask;
  }

  void ios_base::_set_iostate(iostate iostate) {
    assert((iostate & _iostate_mask) == iostate);
    _ios_base_bits = static_cast<__ios_base_bits>((static_cast<fmtflags>(_ios_base_bits) & ~_iostate_mask) | iostate);
  }

  ios_base::iostate ios_base::_get_iostate() const {
    return static_cast<iostate>(_ios_base_bits) & _iostate_mask;
  }

  void ios_base::_set_openmode(openmode openmode) {
    assert((openmode & _openmode_mask) == openmode);
    _ios_base_bits = static_cast<__ios_base_bits>((static_cast<fmtflags>(_ios_base_bits) & ~_openmode_mask) | openmode);
  }

  ios_base::openmode ios_base::_get_openmode() const {
    return static_cast<openmode>(_ios_base_bits) & _openmode_mask;
  }

  void ios_base::_set_seekdir(seekdir seekdir) {
    assert((seekdir & _seekdir_mask) == seekdir);
    _ios_base_bits = static_cast<__ios_base_bits>((static_cast<fmtflags>(_ios_base_bits) & ~_seekdir_mask) | seekdir);
  }

  ios_base::seekdir ios_base::_get_seekdir() const {
    return static_cast<seekdir>(_ios_base_bits) & _seekdir_mask;
  }

  void ios_base::_move(ios_base& other) {
    other._ios_base_bits = other._ios_base_bits;
    other._prec          = other._prec;
    other._wide          = other._wide;
  }

  void ios_base::_swap(ios_base& other) {
    using std::swap;
    swap(_ios_base_bits, other._ios_base_bits);
    swap(_prec, other._prec);
    swap(_wide, other._wide);
  }

  bool ios_base::_is_boolalpha() const {
    return (_get_fmtflags() & boolalpha) != 0;
  }

  bool ios_base::_is_showbase() const {
    return (_get_fmtflags() & showbase) != 0;
  }

  bool ios_base::_is_showpoint() const {
    return (_get_fmtflags() & showpoint) != 0;
  }

  bool ios_base::_is_showpos() const {
    return (_get_fmtflags() & showpos) != 0;
  }

  bool ios_base::_is_skipws() const {
    return (_get_fmtflags() & skipws) != 0;
  }

  bool ios_base::_is_uppercase() const {
    return (_get_fmtflags() & uppercase) != 0;
  }

  bool ios_base::_is_unitbuf() const {
    return (_get_fmtflags() & unitbuf) != 0;
  }

  bool ios_base::_is_internal() const {
    return (_get_fmtflags() & internal) != 0;
  }

  bool ios_base::_is_left() const {
    return (_get_fmtflags() & left) != 0;
  }

  bool ios_base::_is_right() const {
    return (_get_fmtflags() & right) != 0;
  }

  bool ios_base::_is_dec() const {
    return (_get_fmtflags() & dec) != 0;
  }

  bool ios_base::_is_hex() const {
    return (_get_fmtflags() & hex) != 0;
  }

  bool ios_base::_is_oct() const {
    return (_get_fmtflags() & oct) != 0;
  }

  bool ios_base::_is_fixed() const {
    return (_get_fmtflags() & fixed) != 0;
  }

  bool ios_base::_is_scientific() const {
    return (_get_fmtflags() & scientific) != 0;
  }

  bool ios_base::_is_hexfloat() const {
    return (_get_fmtflags() & floatfield) == (ios_base::fixed | ios_base::scientific);
  }

  bool ios_base::_is_defaultfloat() const {
    return (_get_fmtflags() & floatfield) == 0;
  }

  bool ios_base::_is_adjustfield_unset() const {
    return (_get_fmtflags() & adjustfield) == 0;
  }

  bool ios_base::_is_basefield_unset() const {
    return (_get_fmtflags() & basefield) == 0;
  }

  bool ios_base::_is_floatfield_unset() const {
    return (_get_fmtflags() & floatfield) == 0;
  }

  ios_base::~ios_base() { }

  ios_base::fmtflags ios_base::flags() const {
    return _get_fmtflags();
  }

  ios_base::fmtflags ios_base::flags(fmtflags fmtfl) {
    fmtflags old = _get_fmtflags();
    _set_fmtflags(fmtfl);
    return old;
  }

  ios_base::fmtflags ios_base::setf(fmtflags fmtfl) {
    assert((fmtfl & _fmtflags_mask) == fmtfl);
    return flags(flags() | fmtfl);
  }

  ios_base::fmtflags ios_base::setf(fmtflags fmtfl, fmtflags mask) {
    assert((fmtfl & _fmtflags_mask) == fmtfl);
    assert((mask & _fmtflags_mask) == mask);
    return flags((flags() & ~mask) | fmtfl);
  }

  ios_base::fmtflags ios_base::unsetf(fmtflags mask) {
    assert((mask & _fmtflags_mask) == mask);
    return flags(flags() & ~mask);
  }

  streamsize ios_base::precision() const {
    return _prec;
  }

  streamsize ios_base::precision(streamsize prec) {
    streamsize old = _prec;
    _prec          = prec;
    return old;
  }

  streamsize ios_base::width() const {
    return _wide;
  }

  streamsize ios_base::width(streamsize wide) {
    streamsize old = _wide;
    _wide          = wide;
    return old;
  }

  void ios_base::register_callback(event_callback cb, int index) {
    // TODO: impl
    (void)cb;
    (void)index;
  }
} // namespace std
