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

