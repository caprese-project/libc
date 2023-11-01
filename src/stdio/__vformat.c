#include <internal/branch.h>
#include <internal/unreachable.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static const char __upper_digits[] = "0123456789ABCDEF";
static const char __lower_digits[] = "0123456789abcdef";

#define __f_minus      (1 << 0)
#define __f_plus       (1 << 1)
#define __f_space      (1 << 2)
#define __f_zero       (1 << 3)
#define __f_apostrophe (1 << 4)
#define __f_hash       (1 << 5)

#define __l_hh 0
#define __l_h  1
#define __l_l  2
#define __l_ll 3
#define __l_j  4
#define __l_z  5
#define __l_t  6

#define __t_signed    0
#define __t_unsigned  1
#define __t_lower_hex 2
#define __t_upper_hex 3
#define __t_char      4
#define __t_ptr       5
#define __t_str       6
#define __t_raw       7

struct __vformat_field {
  int       flags;
  int       width;
  int       precision;
  int       length;
  uintmax_t value;
  int       type;
};

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) > (b) ? (b) : (a))

static void __parse_flags_field(struct __vformat_field* field, const char** ptr) {
  while (*++*ptr) {
    switch (**ptr) {
      case '-':
        field->flags |= __f_minus;
        break;
      case '+':
        field->flags |= __f_plus;
        break;
      case ' ':
        field->flags |= __f_space;
        break;
      case '0':
        field->flags |= __f_zero;
        break;
      case '\'':
        field->flags |= __f_apostrophe;
        break;
      case '#':
        field->flags |= __f_hash;
        break;
      default:
        --*ptr;
        return;
    }
  }
}

static void __parse_width_field(struct __vformat_field* field, const char** ptr) {
  ++*ptr;
  if (**ptr == '*') {
    field->width = -1;
  } else {
    do {
      if (**ptr >= '0' && **ptr <= '9') {
        field->width *= 10;
        field->width += **ptr - '0';
      } else {
        --*ptr;
        break;
      }
    } while (*++*ptr);
  }
}

static void __parse_precision_field(struct __vformat_field* field, const char** ptr) {
  ++*ptr;
  if (**ptr == '.') {
    ++*ptr;
    if (**ptr == '*') {
      field->precision = -1;
    } else {
      do {
        field->precision *= 10;
        if (**ptr >= '0' && **ptr <= '9') {
          field->precision += **ptr - '0';
        } else {
          --*ptr;
          break;
        }
      } while (*++*ptr);
    }
  } else {
    --*ptr;
  }
}

static void __parse_length_field(struct __vformat_field* field, const char** ptr) {
  switch (*++*ptr) {
    case 'h':
      if (*++*ptr == 'h') {
        field->length = __l_hh;
      } else {
        --*ptr;
        field->length = __l_h;
      }
      break;
    case 'l':
      if (*++*ptr == 'l') {
        field->length = __l_ll;
      } else {
        --*ptr;
        field->length = __l_l;
      }
      break;
    case 'j':
      field->length = __l_j;
      break;
    case 'z':
      field->length = __l_z;
      break;
    case 't':
      field->length = __l_t;
      break;
    default:
      --*ptr;
      break;
  }
}

static void __parse_type_field(struct __vformat_field* field, va_list* arg, const char** ptr) {
  ++*ptr;

  switch (**ptr) {
    case 'd':
    case 'i':
    case 'u':
    case 'x':
    case 'X':
    case 's':
      if (field->width == -1) {
        field->width = va_arg(*arg, int);
      }
      if (field->precision == -1) {
        field->precision = va_arg(*arg, int);
      }
      break;
    case 'p':
      field->flags &= ~__f_space;
      field->flags |= __f_zero;
      field->flags &= ~__f_apostrophe;
      field->flags |= __f_hash;

      field->width     = sizeof(uintptr_t) * 2;
      field->precision = 0;
      break;
  }

  switch (**ptr) {
    case 'd':
    case 'i':
    case 'u':
    case 'x':
    case 'X':
      switch (field->length) {
        case __l_hh:
          field->value = (char)va_arg(*arg, int);
          break;
        case __l_h:
          field->value = (short)va_arg(*arg, int);
          break;
        case __l_l:
          field->value = va_arg(*arg, long);
          break;
        case __l_ll:
          field->value = va_arg(*arg, long long);
          break;
        case __l_z:
          field->value = va_arg(*arg, size_t);
          break;
        case __l_j:
          field->value = va_arg(*arg, intmax_t);
          break;
        case __l_t:
          field->value = va_arg(*arg, ptrdiff_t);
          break;
        default:
          field->value = va_arg(*arg, int);
          break;
      }
      break;
    case 'c':
      field->value = (char)va_arg(*arg, int);
      break;
    case 'p':
      field->value = va_arg(*arg, uintptr_t);
      break;
    case 's':
      field->value = va_arg(*arg, uintptr_t);
      break;
  }

  switch (**ptr) {
    case 'd':
    case 'i':
      field->type = __t_signed;
      break;
    case 'u':
      field->type = __t_unsigned;
      break;
    case 'x':
      field->type = __t_lower_hex;
      break;
    case 'X':
      field->type = __t_upper_hex;
      break;
    case 'c':
      field->type = __t_char;
      break;
    case 'p':
      field->type = __t_ptr;
      break;
    case 's':
      field->type = __t_str;
      break;
    case '%':
    case '\0':
      field->type = __t_raw;
      break;
    default:
      field->type = __t_raw;
  }
}

static void __print_int(const struct __vformat_field* field, void* data, void (*callback)(int ch, void* data)) {
  bool      minus = false;
  uintmax_t value = field->value;

  if (field->type == __t_signed) {
    if ((intmax_t)field->value < 0) {
      value = -(intmax_t)field->value;
      minus = true;
    }
  }

  intmax_t base = 10;
  if (field->type == __t_lower_hex || field->type == __t_upper_hex || field->type == __t_ptr) {
    base = 16;
  }

  char        buf[32];
  int         i      = 0;
  const char* digits = field->type == __t_upper_hex ? __upper_digits : __lower_digits;
  do {
    buf[i++] = digits[value % base];
    if ((field->flags & __f_apostrophe) && i % 4 == 0) {
      buf[i++] = '\'';
    }
  } while (value /= base);

  int width = max(field->width, field->precision);

  if (width && (field->flags & __f_zero)) {
    while (i < width) {
      buf[i++] = '0';
      if ((field->flags & __f_apostrophe) && i % 4 == 0 && i + 1 < width) {
        buf[i++] = '\'';
      }
    }
  }

  if ((field->flags & __f_hash) && base == 16) {
    buf[i++] = 'x';
    buf[i++] = '0';
  }

  if (minus) {
    buf[i++] = '-';
  } else if (field->flags & __f_plus) {
    buf[i++] = '+';
  } else if (field->flags & __f_space) {
    buf[i++] = ' ';
  }

  if (width && !(field->flags & __f_zero) && !(field->flags & __f_minus)) {
    while (i < width) {
      buf[i++] = ' ';
    }
  }

  while (--i >= 0) {
    callback(buf[i], data);
  }

  if (width && !(field->flags & __f_zero) && minus) {
    while (i < width) {
      ++i;
      callback(' ', data);
    }
  }
}

static void __print_str(const struct __vformat_field* field, void* data, void (*callback)(int ch, void* data)) {
  const char* str;

  __if_unlikely (field->value == 0) {
    str = "(null)";
  } else {
    str = (const char*)field->value;
  }

  int len       = strlen(str);
  int max_width = 0;
  if (field->precision == 0) {
    max_width = len;
  } else {
    max_width = min(len, field->precision);
  }

  if (max_width < field->width && !(field->flags & __f_minus)) {
    for (int i = 0; i < field->width - max_width; ++i) {
      callback(' ', data);
    }
  }

  for (int i = 0; i < max_width; ++i) {
    callback(str[i], data);
  }

  if (max_width < field->width && (field->flags & __f_minus)) {
    for (int i = 0; i < field->width - max_width; ++i) {
      callback(' ', data);
    }
  }
}

void __vformat(const char* fmt, va_list arg, void* data, void (*callback)(int ch, void* data)) {
  for (const char* ptr = fmt; *ptr; ++ptr) {
    __if_likely (*ptr != '%') {
      callback(*ptr, data);
      continue;
    }

    struct __vformat_field field = {};

    __parse_flags_field(&field, &ptr);
    __parse_width_field(&field, &ptr);
    __parse_precision_field(&field, &ptr);
    __parse_length_field(&field, &ptr);
    __parse_type_field(&field, &arg, &ptr);

    switch (field.type) {
      case __t_signed:
      case __t_unsigned:
      case __t_lower_hex:
      case __t_upper_hex:
      case __t_ptr:
        __print_int(&field, data, callback);
        break;
      case __t_char:
        callback((char)field.value, data);
        break;
      case __t_str:
        __print_str(&field, data, callback);
        break;
      case __t_raw:
        callback('%', data);
        break;
      default:
        __unreachable();
    }
  }
}
