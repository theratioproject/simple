
#ifndef _json_inttypes_h_
#define _json_inttypes_h_

#if defined(_MSC_VER) && _MSC_VER < 1600

/* Anything less than Visual Studio C++ 10 is missing stdint.h and inttypes.h */
typedef __int64 int64_t;
#define PRId64 "I64d"
#define SCNd64 "I64d"

#else

#ifdef HAVE_INTTYPES_H
typedef signed char  int8_t;
typedef signed short int16_t;
typedef signed int   int32_t;
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef signed long long   int64_t;
typedef unsigned long long uint64_t;
#endif
/* inttypes.h includes stdint.h */

#endif

#endif
