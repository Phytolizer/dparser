
#ifndef DPARSE_EXPORT_H
#define DPARSE_EXPORT_H

#ifdef DPARSE_STATIC_DEFINE
#  define DPARSE_EXPORT
#  define DPARSE_NO_EXPORT
#else
#  ifndef DPARSE_EXPORT
#    ifdef dparse_EXPORTS
        /* We are building this library */
#      define DPARSE_EXPORT 
#    else
        /* We are using this library */
#      define DPARSE_EXPORT 
#    endif
#  endif

#  ifndef DPARSE_NO_EXPORT
#    define DPARSE_NO_EXPORT 
#  endif
#endif

#ifndef DPARSE_DEPRECATED
#  define DPARSE_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef DPARSE_DEPRECATED_EXPORT
#  define DPARSE_DEPRECATED_EXPORT DPARSE_EXPORT DPARSE_DEPRECATED
#endif

#ifndef DPARSE_DEPRECATED_NO_EXPORT
#  define DPARSE_DEPRECATED_NO_EXPORT DPARSE_NO_EXPORT DPARSE_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef DPARSE_NO_DEPRECATED
#    define DPARSE_NO_DEPRECATED
#  endif
#endif

#endif /* DPARSE_EXPORT_H */
