/*
  Copyright 2002-2004 John Plevyak, All Rights Reserved
*/
#ifndef _d_H_
#define _d_H_

#define __USE_MINGW_ANSI_STDIO 1
#ifdef MEMWATCH
#define MEMWATCH_STDIO 1
#include "../../src/memwatch-2.67/memwatch.h"
#define MEM_GROW_MACRO
#endif
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#if !defined(__FreeBSD__) || (__FreeBSD_version >= 500000)
#include <inttypes.h>
#endif
#include <limits.h>
#include <sys/types.h>
#if !defined(__MINGW32__) && !defined(WIN32)
#include <sys/mman.h>
#include <sys/uio.h>
#endif
#if !defined(WIN32)
#include <unistd.h>
#include <sys/time.h>
#include <dirent.h>
#endif
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>

#ifdef LEAK_DETECT
#define GC_DEBUG
#include "gc.h"
#define MALLOC(n) GC_MALLOC(n)
#define CALLOC(m, n) GC_MALLOC((m) * (n))
#define FREE(p) GC_FREE(p)
#define REALLOC(p, n) GC_REALLOC((p), (n))
#define CHECK_LEAKS() GC_gcollect()
#else
#ifdef USE_GC
#include "gc.h"
#define MALLOC GC_MALLOC
#define REALLOC GC_REALLOC
#define FREE(_x)
#define malloc dont_use_malloc_use_MALLOC_instead
#define relloc dont_use_realloc_use_REALLOC_instead
#define free dont_use_free_use_FREE_instead
#else
#define MALLOC malloc
#define REALLOC realloc
#define FREE free
#endif
#endif

/* enough already with the signed/unsiged char issues
 */
#define isspace_(_c) isspace((unsigned char)(_c))
#define isdigit_(_c) isdigit((unsigned char)(_c))
#define isxdigit_(_c) isxdigit((unsigned char)(_c))
#define isprint_(_c) isprint((unsigned char)(_c))

/* Compilation Options
 */

#define round2(_x, _n) ((_x + ((_n)-1)) & ~((_n)-1))
#define tohex1(_x) ((((_x)&15) > 9) ? (((_x)&15) - 10 + 'A') : (((_x)&15) + '0'))
#define tohex2(_x) ((((_x) >> 4) > 9) ? (((_x) >> 4) - 10 + 'A') : (((_x) >> 4) + '0'))
#define numberof(_x) ((sizeof(_x)) / (sizeof((_x)[0])))

using int8 = int8_t;
using uint8 = uint8_t;
using int32 = int32_t;
using uint32 = uint32_t;
using int64 = int64_t;
using uint64 = uint64_t;
using int16 = int16_t;
using uint16 = uint16_t;
using uint = unsigned int;

#ifdef D_DEBUG
#define DBG(_x)                                                                                                        \
    if (d_debug_level > 1)                                                                                             \
    {                                                                                                                  \
        _x;                                                                                                            \
    }
#else
#define DBG(_x)
#endif

#include "dparse.hpp"
#include "arg.hpp"
#include "util.hpp"
#include "gram.hpp"
#include "lr.hpp"
#include "lex.hpp"
#include "scan.hpp"
#include "parse.hpp"
#include "write_tables.hpp"
#include "read_binary.hpp"

void d_version(char *);

#endif
