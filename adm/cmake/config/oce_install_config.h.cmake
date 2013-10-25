/****************************************************************
**
**  File: oce_install_config.h.cmake, oce-config.h
**
**  This configuration header is installed with OCE headers.
**  It should NOT be used while building OCE.  It defines
**  a subset of the macros configured by CMake. This subset is
**  used by the installed OCE headers.
**
****************************************************************/



#cmakedefine OCE_HAVE_IOMANIP 1
#cmakedefine OCE_HAVE_IOMANIP_H 1

#cmakedefine OCE_HAVE_FSTREAM 1
#cmakedefine OCE_HAVE_FSTREAM_H 1

#cmakedefine OCE_HAVE_IOSTREAM 1
#cmakedefine OCE_HAVE_IOSTREAM_H 1

#cmakedefine OCE_HAVE_LIMITS 1
#cmakedefine OCE_HAVE_CLIMITS 1
#cmakedefine OCE_HAVE_LIMITS_H 1

#cmakedefine MACOSX_USE_GLX

#cmakedefine OCE_IS_DUPLICATE_UINT32_T
