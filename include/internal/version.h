#ifndef CAPRESE_LIBC_INTERNAL_VERSION_H_
#define CAPRESE_LIBC_INTERNAL_VERSION_H_

#ifdef __STDC__
#define __C_STD_90__
#endif // __STDC__

#ifdef __STDC_VERSION__

#if __STDC_VERSION__ >= 199409l
#define __C_STD_95__
#endif // __STDC_VERSION__ >= 199409l

#if __STDC_VERSION__ >= 199901l
#define __C_STD_99__
#endif // __STDC_VERSION__ >= 199901l

#if __STDC_VERSION__ >= 201112l
#define __C_STD_11__
#endif // __STDC_VERSION__ >= 201112l

#if __STDC_VERSION__ >= 201710l
#define __C_STD_17__
#endif // __STDC_VERSION__ >= 201710l

#if __STDC_VERSION__ >= 202311l
#define __C_STD_23__
#endif // __STDC_VERSION__ >= 202311l

#endif // __STDC_VERSION__

#ifdef __cplusplus

#if __cplusplus >= 199711l
#define __CXX_STD_98__
#define __CXX_STD_03__
#endif // __cplusplus >= 199711l

#if __cplusplus >= 201103l
#define __CXX_STD_11__
#endif // __cplusplus >= 201103l

#if __cplusplus >= 201402l
#define __CXX_STD_14__
#endif // __cplusplus >= 201402l

#if __cplusplus >= 201703l
#define __CXX_STD_17__
#endif // __cplusplus >= 201703l

#if __cplusplus >= 202002l
#define __CXX_STD_20__
#endif // __cplusplus >= 202002l

#endif // __cplusplus

#endif // CAPRESE_LIBC_INTERNAL_VERSION_H_
