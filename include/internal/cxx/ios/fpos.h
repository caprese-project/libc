#ifndef CAPRESE_LIBC_INTERNAL_CXX_IOS_FPOS_H_
#define CAPRESE_LIBC_INTERNAL_CXX_IOS_FPOS_H_

#include <internal/cxx/ios/types.h>

namespace std {
  template<typename State>
  class fpos {
    streamoff _off;
    State     _state;

  public:
    fpos(): _off(0), _state() { }

    fpos(streamoff off): _off(off), _state() { }

    fpos(const fpos&)            = default;
    fpos& operator=(const fpos&) = default;
    ~fpos()                      = default;

    fpos& operator+=(streamoff off) noexcept {
      _off += off;
      return *this;
    }

    fpos& operator-=(streamoff off) noexcept {
      _off -= off;
      return *this;
    }

    fpos operator+(streamoff off) const noexcept {
      return fpos(_off + off);
    }

    fpos operator-(streamoff off) const noexcept {
      return fpos(_off - off);
    }

    streamoff operator-(const fpos& other) const noexcept {
      return _off - other._off;
    }

    bool operator==(const fpos& other) const noexcept {
      return _off == other._off;
    }

    bool operator!=(const fpos& other) const noexcept {
      return _off != other._off;
    }

    operator streamoff() const noexcept {
      return _off;
    }

    void state(State state) noexcept {
      _state = state;
    }

    State state() const noexcept {
      return _state;
    }
  };
} // namespace std

#endif // CAPRESE_LIBC_INTERNAL_CXX_IOS_FPOS_H_
