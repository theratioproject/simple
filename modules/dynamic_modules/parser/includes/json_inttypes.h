
#ifndef _json_inttypes_h_
#define _json_inttypes_h_

#if defined(_MSC_VER) && _MSC_VER < 1800

/* Anything less than Visual Studio C++ 10 is missing stdint.h and inttypes.h */
typedef __int64 int64_t;
#define PRId64 "I64d"
#define SCNd64 "I64d"

#include "inttypes.h"
#ifdef snprintf
#else
#define snprintf(buf,len, format,...) _snprintf_s(buf, len,len, format, __VA_ARGS__)
#endif

#else

#ifdef HAVE_INTTYPES_H
#include <inttypes.h>
#endif
/* inttypes.h includes stdint.h */

#endif

#endif
