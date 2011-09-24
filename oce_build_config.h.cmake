/****************************************************************
**
**  File: oce_build_config.h.cmake, build-inc/oce-config.h
**
**  This configuration header is used to build OCE. It is
**  installed along other header files in order to know which
**  macros had been defined when compiling OCE, but it must
**  NOT be included when compiling 3rd party programs.
**
****************************************************************/


/* Define to 1 if using `alloca.c'. */
#cmakedefine C_ALLOCA 1

/* define if the compiler allows redefinition of stream input and output */
#cmakedefine DEF_IOS_OK 

#cmakedefine OCE_HAVE_FSTREAM 1

#cmakedefine OCE_HAVE_IOSTREAM 1

#cmakedefine OCE_HAVE_IOMANIP 1

#cmakedefine OCE_HAVE_LIMITS 1
#cmakedefine OCE_HAVE_CLIMITS 1

/* Define to 1 if you have the <dirent.h> header file. */
#cmakedefine HAVE_DIRENT_H 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#cmakedefine HAVE_DLFCN_H 1

/* Define if you have the <dl.h> header file. */
#cmakedefine HAVE_DL_H 1

/* Define if we have the Adobe postscript library -ldps. */
#cmakedefine HAVE_DPS

/* Define to 1 if you have the <DPS/dpsXclient.h> header file. */
#cmakedefine HAVE_DPS_DPSXCLIENT_H 1

/* Define if we have a function called "finite" in -lm. */
#cmakedefine HAVE_FINITE 

/* Define to 1 if you have the <floatingpoint.h> header file. */
#cmakedefine HAVE_FLOATINGPOINT_H 1

/* Define to 1 if you have the <ieeefp.h> header file. */
#cmakedefine HAVE_IEEEFP_H 1

/* Define to 1 if you have the <iomanip.h> header file. */
#cmakedefine OCE_HAVE_IOMANIP_H 1

/* Define to 1 if you have the <ios> header file. */
#cmakedefine HAVE_IOS 1

/* Define to 1 if you have the <fstream.h> header file. */
#cmakedefine OCE_HAVE_FSTREAM_H 1

/* Define to 1 if you have the <ios.h> header file. */
#cmakedefine HAVE_IOS_H 1

/* Define to 1 if you have the <iostream.h> header file. */
#cmakedefine OCE_HAVE_IOSTREAM_H 1

/* Define to 1 if you have the <libc.h> header file. */
#cmakedefine HAVE_LIBC_H 1

/* Define to 1 if you have the `e' library (-le). */
#cmakedefine HAVE_LIBE 1

/* Define to 1 if you have the `inks' library (-links). */
#cmakedefine HAVE_LIBINKS 1

/* Define to 1 if you have the <limits> header file. */
#cmakedefine OCE_HAVE_LIMITS_H 1

/* Define to 1 if you have the <malloc.h> header file. */
#cmakedefine HAVE_MALLOC_H 1

/* Define to 1 if you have the <ndir.h> header file. */
#cmakedefine HAVE_NDIR_H 1

/* Define to 1 if you have the <netdb.h> header file. */
#cmakedefine HAVE_NETDB_H 1

/* Define to 1 if you have the <net/if.h> header file. */
#cmakedefine HAVE_NET_IF_H 1

/* Define to 1 if you have the <osfcn.h> header file. */
#cmakedefine HAVE_OSFCN_H 1

/* Define to 1 if you have the <pwd.h> header file. */
#cmakedefine HAVE_PWD_H 1

/* Define to 1 if you have the <sigfpe.h> header file. */
#cmakedefine HAVE_SIGFPE_H 1

/* Define to 1 if you have the <signal.h> header file. */
#cmakedefine HAVE_SIGNAL_H 1

/* Define to 1 if you have the `statfs' function. */
#cmakedefine HAVE_STATFS 1

/* Define to 1 if you have the `statvfs' function. */
#cmakedefine HAVE_STATVFS 1

/* Define to 1 if you have the <stdlib.h> header file. */
#cmakedefine HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#cmakedefine HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#cmakedefine HAVE_STRING_H 1

/* Define if we have a function called "ieee_handler" in -lsunmath. */
#cmakedefine HAVE_SUNMATH

/* Define to 1 if you have the <sysent.h> header file. */
#cmakedefine HAVE_SYSENT_H 1

/* Define to 1 if you have the <sys/dir.h> header file. */
#cmakedefine HAVE_SYS_DIR_H 1

/* Define to 1 if you have the <sys/filio.h> header file. */
#cmakedefine HAVE_SYS_FILIO_H 1

/* Define to 1 if you have the <sys/ioctl.h> header file. */
#cmakedefine HAVE_SYS_IOCTL_H 1

/* Define to 1 if you have the <sys/ipc.h> header file. */
#cmakedefine HAVE_SYS_IPC_H 1

/* Define to 1 if you have the <sys/machsig.h> header file. */
#cmakedefine HAVE_SYS_MACHSIG_H 1

/* Define to 1 if you have the <sys/mman.h> header file. */
#cmakedefine HAVE_SYS_MMAN_H 1

/* Define to 1 if you have the <sys/ndir.h> header file. */
#cmakedefine HAVE_SYS_NDIR_H 1

/* Define to 1 if you have the <sys/param.h> header file. */
#cmakedefine HAVE_SYS_PARAM_H 1

/* Define to 1 if you have the <sys/select.h> header file. */
#cmakedefine HAVE_SYS_SELECT_H 1

/* Define to 1 if you have the <sys/sem.h> header file. */
#cmakedefine HAVE_SYS_SEM_H 1

/* Define to 1 if you have the <sys/siginfo.h> header file. */
#cmakedefine HAVE_SYS_SIGINFO_H 1

/* Define to 1 if you have the <sys/signal.h> header file. */
#cmakedefine HAVE_SYS_SIGNAL_H 1

/* Define to 1 if you have the <sys/socket.h> header file. */
#cmakedefine HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/statvfs.h> header file. */
#cmakedefine HAVE_SYS_STATVFS_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#cmakedefine HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/systeminfo.h> header file. */
#cmakedefine HAVE_SYS_SYSTEMINFO_H 1

/* Define to 1 if you have the <sys/times.h> header file. */
#cmakedefine HAVE_SYS_TIMES_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
#cmakedefine HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#cmakedefine HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/unistd.h> header file. */
#cmakedefine HAVE_SYS_UNISTD_H 1

/* Define to 1 if you have the <sys/utsname.h> header file. */
#cmakedefine HAVE_SYS_UTSNAME_H 1

/* Define to 1 if you have the <sys/vfs.h> header file. */
#cmakedefine HAVE_SYS_VFS_H 1

/* Define to 1 if you have the <time.h> header file. */
#cmakedefine HAVE_TIME_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#cmakedefine HAVE_UNISTD_H 1

/* Define to 1 if you have the <values.h> header file. */
#cmakedefine HAVE_VALUES_H 1

/* Define to 1 if you have the <X11/extensions/multibuf.h> header file. */
#cmakedefine HAVE_X11_EXTENSIONS_MULTIBUF_H 1

/* Define to 1 if you have the <X11/extensions/readdisplay.h> header file. */
#cmakedefine HAVE_X11_EXTENSIONS_READDISPLAY_H 1

/* Define if your C compiler doesn't accept -c and -o together. */
#cmakedefine NO_MINUS_C_MINUS_O

/* define if the class ostream has member function form */
#cmakedefine OSTREAM_FORM_OK 

/* Define if compiler has function prototypes */
#cmakedefine PROTOTYPES

/* define if the function semctl takes a value */
#cmakedefine SEMCTL_NO_REFERENCE

/* define if the function semop takes a value */
#cmakedefine SEMOP_NO_REFERENCE

/* define if semun has member __buf */
#cmakedefine SEMUN_BUF_DEFINED

/* define if the union semun is in sys/sem.h */
#cmakedefine SEMUN_DEFINED

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at run-time.
        STACK_DIRECTION > 0 => grows toward higher addresses
        STACK_DIRECTION < 0 => grows toward lower addresses
        STACK_DIRECTION = 0 => direction of growth unknown */
#define STACK_DIRECTION @STACK_DIRECTION@

/* Define if you have the ANSI C header files. */
#ifndef STDC_HEADERS
#cmakedefine STDC_HEADERS
#endif

/* Define if your <sys/time.h> declares `struct tm'. */
#cmakedefine TM_IN_SYS_TIME

/* Define if your processor stores words with the most significant byte first
   (like Motorola and SPARC, unlike Intel and VAX). */
#cmakedefine WORDS_BIGENDIAN

/* Define if on AIX 3.
   System headers sometimes define this.
   We just want to avoid a redefinition error message.  */
#ifndef _ALL_SOURCE
/* # undef _ALL_SOURCE */
#endif

/* Define if you need to in order for stat and other things to work. */
#cmakedefine _POSIX_SOURCE

/* Location where resource files will be installed. */
#cmakedefine OCE_INSTALL_DATA_DIR "@OCE_ABSPATH_DATA_DIR@"

/* Debug postfix for DLLs */
#if defined(_MSC_VER) && defined(_DEBUG)
#define OCE_DEBUG_POSTFIX "@CMAKE_DEBUG_POSTFIX@"
#else
#define OCE_DEBUG_POSTFIX ""
#endif

/* Location where TKOpenGl shared library will be installed. */
#ifdef _MSC_VER
#define OCE_DEFAULT_CSF_GraphicShr "@OCE_DEFAULT_CSF_GraphicShr@" OCE_DEBUG_POSTFIX ".dll"
#else
#cmakedefine OCE_DEFAULT_CSF_GraphicShr "@OCE_DEFAULT_CSF_GraphicShr@"
#endif

/* Whether OCE is build as shared lib */
#cmakedefine OCE_BUILD_SHARED_LIB
