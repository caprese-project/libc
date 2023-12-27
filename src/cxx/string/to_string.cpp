#include <cstdio>
#include <cstdlib>
#include <string>

namespace std {
  string to_string(int val) {
    char buf[32];
    sprintf(buf, "%d", val);
    return string(buf);
  }

  string to_string(unsigned val) {
    char buf[32];
    sprintf(buf, "%u", val);
    return string(buf);
  }

  string to_string(long val) {
    char buf[32];
    sprintf(buf, "%ld", val);
    return string(buf);
  }

  string to_string(unsigned long val) {
    char buf[32];
    sprintf(buf, "%lu", val);
    return string(buf);
  }

  string to_string(long long val) {
    char buf[32];
    sprintf(buf, "%lld", val);
    return string(buf);
  }

  string to_string(unsigned long long val) {
    char buf[32];
    sprintf(buf, "%llu", val);
    return string(buf);
  }
} // namespace std
