#include <cstdio>
#include <internal/cxx/iostream/stdin_streambuf.h>
#include <internal/cxx/iostream/stdout_streambuf.h>
#include <istream>
#include <ostream>

namespace std {
  alignas(istream) char cin[sizeof(istream)];
  alignas(ostream) char cout[sizeof(ostream)];
  alignas(ostream) char clog[sizeof(ostream)];
  alignas(ostream) char cerr[sizeof(ostream)];

  alignas(wistream) char wcin[sizeof(wistream)];
  alignas(wostream) char wcout[sizeof(wostream)];
  alignas(wostream) char wclog[sizeof(wostream)];
  alignas(wostream) char wcerr[sizeof(wostream)];

  alignas(__stdin_streambuf<char>) char __cin_streambuf[sizeof(__stdin_streambuf<char>)];
  alignas(__stdout_streambuf<char>) char __cout_streambuf[sizeof(__stdout_streambuf<char>)];
  alignas(__stdout_streambuf<char>) char __clog_streambuf[sizeof(__stdout_streambuf<char>)];
  alignas(__stdout_streambuf<char>) char __cerr_streambuf[sizeof(__stdout_streambuf<char>)];

  alignas(__stdin_streambuf<wchar_t>) char __wcin_streambuf[sizeof(__stdin_streambuf<wchar_t>)];
  alignas(__stdout_streambuf<wchar_t>) char __wcout_streambuf[sizeof(__stdout_streambuf<wchar_t>)];
  alignas(__stdout_streambuf<wchar_t>) char __wclog_streambuf[sizeof(__stdout_streambuf<wchar_t>)];
  alignas(__stdout_streambuf<wchar_t>) char __wcerr_streambuf[sizeof(__stdout_streambuf<wchar_t>)];

  struct __stdiostream_factory {
    __stdiostream_factory() {
      __stdin_streambuf<char>*  cin_strbuf  = ::new (__cin_streambuf) __stdin_streambuf<char>(stdin);
      __stdout_streambuf<char>* cout_strbuf = ::new (__cout_streambuf) __stdout_streambuf<char>(stdout);
      __stdout_streambuf<char>* clog_strbuf = ::new (__clog_streambuf) __stdout_streambuf<char>(stderr);
      __stdout_streambuf<char>* cerr_strbuf = ::new (__cerr_streambuf) __stdout_streambuf<char>(stderr);

      istream* cin_ptr  = ::new (cin) istream(cin_strbuf);
      ostream* cout_ptr = ::new (cout) ostream(cout_strbuf);
      ostream* clog_ptr = ::new (clog) ostream(clog_strbuf);
      ostream* cerr_ptr = ::new (cerr) ostream(cerr_strbuf);

      cin_ptr->tie(cout_ptr);
      clog_ptr->tie(cout_ptr);
      cerr_ptr->tie(cout_ptr);
    }

    ~__stdiostream_factory() {
      ostream* cout_ptr = reinterpret_cast<ostream*>(cout);
      ostream* clog_ptr = reinterpret_cast<ostream*>(clog);
      cout_ptr->flush();
      clog_ptr->flush();
    }
  };

  ios_base::Init::Init() {
    static __stdiostream_factory init;
  }

  ios_base::Init::~Init() { }
} // namespace std
