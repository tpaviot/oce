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


/* Define to 1 if you have the <strings.h> header file. */
#cmakedefine HAVE_STRINGS_H 1

/* Define to 1 if you have the <mm_malloc.h> header file. */
#cmakedefine HAVE_MM_MALLOC_H 1

/* Define to 1 if you have the <atomic.h> header file. */
#cmakedefine OCE_HAVE_ATOMIC_H 1

/* Define to 1 if the localtime_r function is available. */
#cmakedefine HAVE_LOCALTIME_R 1

/* Define to 1 if the posix_memalign function is available. */
#cmakedefine HAVE_POSIX_MEMALIGN 1

/* Define if your processor stores words with the most significant byte first
   (like Motorola and SPARC, unlike Intel and VAX). */
#cmakedefine WORDS_BIGENDIAN

/* Whether OCE is build as static lib */
#cmakedefine OCE_BUILD_STATIC_LIB

/* Define MACOSX_USE_GLX to use X11 OpenGL on OSX */
#cmakedefine MACOSX_USE_GLX

/* Define if uint32_t and int are the same type */
#cmakedefine OCE_IS_DUPLICATE_UINT32_T

/* Make OCE release number visible when displaying OCCT version number */
#cmakedefine OCC_VERSION_DEVELOPMENT "@OCC_VERSION_DEVELOPMENT@"

