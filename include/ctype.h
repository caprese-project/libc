#ifndef CAPRESE_LIBC_CTYPE_H_
#define CAPRESE_LIBC_CTYPE_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  int isalnum(int ch);
  int isalpha(int ch);
  int isblank(int ch);
  int iscntrl(int ch);
  int isdigit(int ch);
  int isgraph(int ch);
  int islower(int ch);
  int isprint(int ch);
  int ispunct(int ch);
  int isspace(int ch);
  int isupper(int ch);
  int isxdigit(int ch);
  int tolower(int ch);
  int toupper(int ch);

#define __CTYPE_UPPER_CHAR  (1 << 0) // upper char (A-Z)
#define __CTYPE_LOWER_CHAR  (1 << 1) // lower char (a-z)
#define __CTYPE_NUMBER_CHAR (1 << 2) // number (0-9)
#define __CTYPE_SPACE_CHAR  (1 << 3) // space (' ' | '\t' | '\v' | '\r' | '\f')
#define __CTYPE_PUNCT_CHAR  (1 << 4) // punctuation (!-@ | [-` | {-~)
#define __CTYPE_CTRL_CHAR   (1 << 5) // control (0x00-0x1f | 0x7f)
#define __CTYPE_HEX_CHAR    (1 << 6) // hex-digit (a-f | A-F)
#define __CTYPE_BLANK_CHAR  (1 << 7) // blank (' ' | '\t')

#ifndef __OPTIMIZE_SIZE__
  extern const unsigned char __ctype_table[256];
#endif // !__OPTIMIZE_SIZE__

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // CAPRESE_LIBC_CTYPE_H_
