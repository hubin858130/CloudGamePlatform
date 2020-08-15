#ifndef LOG4CPLUS_CONFIG_DEFINES_HXX
#define LOG4CPLUS_CONFIG_DEFINES_HXX

/* */
#undef LOG4CPLUS_HAVE_SYSLOG_H

/* */
#undef LOG4CPLUS_HAVE_NETINET_IN_H

/* */
#undef LOG4CPLUS_HAVE_SYS_TYPES_H

/* */
#undef LOG4CPLUS_HAVE_SYS_SOCKET_H

/* */
#undef LOG4CPLUS_HAVE_SYS_STAT_H

/* */
#undef LOG4CPLUS_HAVE_SYS_TIMEB_H

/* */
#undef LOG4CPLUS_HAVE_SYS_TIME_H

/* */
#undef LOG4CPLUS_HAVE_TIME_H

/* */
#undef LOG4CPLUS_HAVE_NETDB_H

/* */
#undef LOG4CPLUS_HAVE_UNISTD_H

/* */
#undef LOG4CPLUS_HAVE_ERRNO_H

/* */
#undef LOG4CPLUS_HAVE_STDARG_H

/* */
#undef LOG4CPLUS_HAVE_STDIO_H

/* */
#undef LOG4CPLUS_HAVE_WCHAR_H

/* */
#undef LOG4CPLUS_HAVE_FTIME

/* */
#undef LOG4CPLUS_HAVE_GETADDRINFO

/* */
#undef LOG4CPLUS_HAVE_GETHOSTBYNAME_R

/* */
#undef LOG4CPLUS_HAVE_GETPID

/* */
#undef LOG4CPLUS_HAVE_GETTIMEOFDAY

/* */
#undef LOG4CPLUS_HAVE_GMTIME_R

/* */
#undef LOG4CPLUS_HAVE_HTONL

/* */
#undef LOG4CPLUS_HAVE_HTONS

/* */
#undef LOG4CPLUS_HAVE_LOCALTIME_R

/* */
#undef LOG4CPLUS_HAVE_LSTAT

/* */
#undef LOG4CPLUS_HAVE_NTOHL

/* */
#undef LOG4CPLUS_HAVE_NTOHS

/* */
#undef LOG4CPLUS_HAVE_STAT

/* Define if this is a single-threaded library. */
#undef LOG4CPLUS_SINGLE_THREADED

/* */
#undef LOG4CPLUS_USE_PTHREADS

/* Define for compilers/standard libraries that support more than just the "C"
   locale. */
#undef LOG4CPLUS_WORKING_LOCALE

/* Define to int if undefined. */
#undef socklen_t

/* Defined for --enable-debugging builds. */
#undef LOG4CPLUS_DEBUGGING

/* Defined if the compiler understands __declspec(export) or __attribute__((export)) construct. */
#undef LOG4CPLUS_DECLSPEC_EXPORT

/* Defined if the compiler understands __declspec(import) or __attribute__((import)) construct. */
#define LOG4CPLUS_DECLSPEC_IMPORT

/* Defined if the host OS provides ENAMETOOLONG errno value. */
#undef LOG4CPLUS_HAVE_ENAMETOOLONG

/* Define to 1 if you have the `clock_gettime' function. */
#undef LOG4CPLUS_HAVE_CLOCK_GETTIME

#endif // LOG4CPLUS_CONFIG_DEFINES_HXX
