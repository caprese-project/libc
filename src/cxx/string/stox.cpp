#include <cstdlib>
#include <string>

namespace std {
  int stoi(const string& str, size_t* idx, int base) {
    char* end;
    long  result = strtol(str.c_str(), &end, base);
    if (idx != nullptr) {
      *idx = end - str.c_str();
    }
    return static_cast<int>(result);
  }

  long stol(const string& str, size_t* idx, int base) {
    char* end;
    long  result = strtol(str.c_str(), &end, base);
    if (idx != nullptr) {
      *idx = end - str.c_str();
    }
    return result;
  }

  unsigned long stoul(const string& str, size_t* idx, int base) {
    char*         end;
    unsigned long result = strtoul(str.c_str(), &end, base);
    if (idx != nullptr) {
      *idx = end - str.c_str();
    }
    return result;
  }

  long long stoll(const string& str, size_t* idx, int base) {
    char*     end;
    long long result = strtoll(str.c_str(), &end, base);
    if (idx != nullptr) {
      *idx = end - str.c_str();
    }
    return result;
  }

  unsigned long long stoull(const string& str, size_t* idx, int base) {
    char*              end;
    unsigned long long result = strtoull(str.c_str(), &end, base);
    if (idx != nullptr) {
      *idx = end - str.c_str();
    }
    return result;
  }
} // namespace std
