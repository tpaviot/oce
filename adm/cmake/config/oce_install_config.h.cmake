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


#cmakedefine MACOSX_USE_GLX

#cmakedefine OCE_HAVE_ATOMIC_H

#cmakedefine OCE_IS_DUPLICATE_UINT32_T

#cmakedefine OCC_VERSION_DEVELOPMENT "@OCC_VERSION_DEVELOPMENT@"

