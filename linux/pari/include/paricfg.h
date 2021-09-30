/*  This file was created by Configure. Any change made to it will be lost
 *  next time Configure is run. */
#ifndef __PARICFG_H__
#define __PARICFG_H__
#define UNIX
#define GPHELP "\"/usr/bin/gphelp\""
#define GPDATADIR "/usr/share/pari"
#define SHELL_Q '\''

#define PARIVERSION "GP/PARI CALCULATOR Version 2.9.4 (released)"
#define PARIINFO "amd64 running linux (x86-64/GMP-6.1.2 kernel) 64-bit version"
#define PARI_VERSION_CODE 133380
#define PARI_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))
#define PARI_VERSION_SHIFT 8
#define PARI_VCSVERSION ""
#define PARI_MT_ENGINE "pthread"

#define PARI_DOUBLE_FORMAT -
#define GCC_VERSION "gcc version 7.3.0 (Ubuntu 7.3.0-1ubuntu1)"
#define ASMINLINE

/*  Location of GNU gzip program (enables reading of .Z and .gz files). */
#define GNUZCAT
#define ZCAT "/bin/gzip -dc"

#define READLINE "7.0"
#define LONG_IS_64BIT
#define HAS_EXP2
#define HAS_LOG2
#define HAS_ISATTY
#define HAS_ALARM
#define HAS_SYSTEM
#define USE_GETRUSAGE 1
#define USE_GETTIMEOFDAY 1
#define HAS_SIGACTION
#define HAS_WAITPID
#define HAS_GETENV
#define HAS_SETSID
#define HAS_DLOPEN
#define STACK_CHECK
#define HAS_VSNPRINTF
#define HAS_TIOCGWINSZ
#define HAS_STRFTIME
#define HAS_STAT
#define HAS_MMAP
#define ENABLE_TLS
#endif
