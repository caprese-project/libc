#include <cstring>
#include <internal/branch.h>
#include <internal/cxx/stdexcept/stdexcept_string.h>
#include <string>

namespace std {
  __stdexcept_string::__stdexcept_string(const char* data): _data(nullptr), _size(0) {
    _size = strlen(_data);

    __if_unlikely (_size == 0) {
      return;
    }

    _data = new char[_size + 1];
    memcpy(_data, data, _size);
    _data[_size - 1] = '\0';
  }

  __stdexcept_string::__stdexcept_string(const string& data): _data(nullptr), _size(0) {
    _size = data.size();

    __if_unlikely (_size == 0) {
      return;
    }

    _data = new char[_size + 1];
    memcpy(_data, data.c_str(), _size);
    _data[_size - 1] = '\0';
  }

  __stdexcept_string::__stdexcept_string(const __stdexcept_string& other): _data(nullptr), _size(0) {
    _size = other._size;

    __if_unlikely (_size == 0) {
      return;
    }

    _data = new char[_size + 1];
    memcpy(_data, other._data, _size);
    _data[_size - 1] = '\0';
  }

  __stdexcept_string::__stdexcept_string(__stdexcept_string&& other): _data(other._data), _size(other._size) {
    other._data = nullptr;
    other._size = 0;
  }

  __stdexcept_string::~__stdexcept_string() __noexcept {
    delete[] _data;
  }

  const char* __stdexcept_string::c_str() const __noexcept {
    return _data;
  }
} // namespace std
