/****************************************************************
**
**  File: oce_build_paths.h.cmake, build-inc/oce-paths.h
**
**  This configuration header is used to build OCE. It is
**  not installed.
**
****************************************************************/


/* Location where resource files will be installed. */
#cmakedefine OCE_INSTALL_DATA_DIR "@OCE_ABSPATH_DATA_DIR@"

/* Debug prefix, postfix and extension for DLLs */
#define OCE_LIBRARY_DEBUG_POSTFIX "@CMAKE_LIBRARY_DEBUG_POSTFIX@"
#define OCE_LIBRARY_PREFIX "@CMAKE_LIBRARY_PREFIX@"
#define OCE_LIBRARY_EXTENSION "@CMAKE_LIBRARY_EXTENSION@"

