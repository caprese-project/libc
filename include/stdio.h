#ifndef CAPRESE_LIBC_STDIO_H_
#define CAPRESE_LIBC_STDIO_H_

#include <internal/attribute.h>
#include <stdarg.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  struct __FILE;
  typedef struct __FILE FILE;

  typedef ptrdiff_t fpos_t;

  int   remove(const char* filename);
  int   rename(const char* old_name, const char* new_name);
  FILE* tmpfile(void);
  char* tmpnam(char* s);

  int   fclose(FILE* stream);
  int   fflush(FILE* stream);
  FILE* fopen(const char* __restrict filename, const char* __restrict mode);
  FILE* freopen(const char* __restrict filename, const char* __restrict mode, FILE* __restrict stream);
  void  setbuf(FILE* __restrict stream, char* __restrict buf);
  int   setvbuf(FILE* __restrict stream, char* __restrict buf, int mode, size_t size);

  int fprintf(FILE* __restrict stream, const char* __restrict format, ...);
  int fscanf(FILE* __restrict stream, const char* __restrict format, ...);
  int printf(const char* __restrict format, ...);
  int scanf(const char* __restrict format, ...);
  int snprintf(char* __restrict dst, size_t n, const char* __restrict format, ...);
  int sprintf(char* __restrict dst, const char* __restrict format, ...);
  int sscanf(const char* __restrict s, const char* __restrict format, ...);
  int vfprintf(FILE* __restrict stream, const char* __restrict format, va_list arg);
  int vfscanf(FILE* __restrict stream, const char* __restrict format, va_list arg);
  int vprintf(const char* __restrict format, va_list arg);
  int vscanf(const char* __restrict format, va_list arg);
  int vsnprintf(char* __restrict dst, size_t n, const char* __restrict format, va_list arg);
  int vsprintf(char* __restrict dst, const char* __restrict format, va_list arg);
  int vsscanf(const char* __restrict dst, const char* __restrict format, va_list arg);

  int   fgetc(FILE* stream);
  char* fgets(char* __restrict dst, int n, FILE* __restrict stream);
  int   fputc(int ch, FILE* stream);
  int   fputs(const char* __restrict str, FILE* __restrict stream);
  int   getc(FILE* stream);
  int   getchar(void);
  int   putc(int ch, FILE* stream);
  int   putchar(int ch);
  int   puts(const char* str);
  int   ungetc(int ch, FILE* stream);

  size_t fread(void* __restrict ptr, size_t size, size_t nmemb, FILE* __restrict stream);
  size_t fwrite(const void* __restrict ptr, size_t size, size_t nmemb, FILE* __restrict stream);

  int      fgetpos(FILE* __restrict stream, fpos_t* __restrict pos);
  int      fseek(FILE* stream, long int offset, int whence);
  int      fsetpos(FILE* stream, const fpos_t* pos);
  long int ftell(FILE* stream);
  void     rewind(FILE* stream);

  void clearerr(FILE* stream);
  int  feof(FILE* stream);
  int  ferror(FILE* stream);
  void perror(const char* str);

  FILE* __stdin();
  FILE* __stdout();
  FILE* __stderr();

  void __vformat(const char* fmt, va_list arg, void* data, void (*callback)(int ch, void* data));

#define stdin  __stdin()
#define stdout __stdout()
#define stderr __stderr()

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#define _IOFBF 1
#define _IOLBF 2
#define _IONBF 3

#define BUFSIZ 0x1000

#define EOF (-1)

#define SEEK_CUR 1
#define SEEK_END 2
#define SEEK_SET 3

#endif // CAPRESE_LIBC_STDIO_H_
