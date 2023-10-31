cmake_minimum_required(VERSION 3.20)

add_library(caprese_libc_stdio)

target_sources(
  caprese_libc_stdio PRIVATE
  clearerr.c
  fclose.c
  feof.c
  ferror.c
  fflush.c
  fgetc.c
  fgetpos.c
  fgets.c
  fopen.c
  fprintf.c
  fputc.c
  fputs.c
  fread.c
  freopen.c
  fscanf.c
  fseek.c
  fsetpos.c
  ftell.c
  fwrite.c
  getc.c
  getchar.c
  perror.c
  printf.c
  putc.c
  putchar.c
  puts.c
  remove.c
  rename.c
  rewind.c
  scanf.c
  setbuf.c
  setvbuf.c
  snprintf.c
  sprintf.c
  sscanf.c
  tmpfile.c
  tmpnam.c
  ungetc.c
  vfprintf.c
  vfscanf.c
  vprintf.c
  vscanf.c
  vsnprintf.c
  vsprintf.c
  vsscanf.c
)

target_include_directories(
  caprese_libc_stdio PUBLIC
  $<BUILD_INTERFACE:${LIBC_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:include>
)
