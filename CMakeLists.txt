# REQUIREMENTS: this script needs CMake 2.8 or higher. Downloads are available at http://www.cmake.org

# How to build OCE using CMake under Unix (Linux, Darwin etc.)?
# 1. Copy this file, as-is, to the top-level OCE folder
# 2. Make a build directory somewhere outside the OCE source tree
# 3. cmake "relative/path/to/OCE"
# 4. make
# 5. make install (or sudo make install)

# How to build OCE using CMake under Windows (Linux, Darwin etc.)?
# 1. Copy this file, as-is, to the top-level folder
# 2. Launch the cmake-gui, and select the top-level folder
# 3. You can choose whatever you want as an install directory
# 4. Click 'Configure'
# 5. Choose your generator
# 6. When configure is achived, you can change the variable with a red background
# 7. Click 'Generate'
# 8. From your IDE, open the generated makefile and run the compilation.

project(OCE)

set(OCE_VERSION_MAJOR 0)
set(OCE_VERSION_MINOR 19)
# OCE_VERSION_PATCH is used for bugfixes releases only
# (uncomment following line)
set(OCE_VERSION_PATCH)
#  Empty for official releases, set to -dev, -rc1, etc for development releases
set(OCE_VERSION_DEVEL -dev)

# bugfix release: add ${OCE_VERSION_PATCH} to OCE_VERSION
set(OCE_VERSION ${OCE_VERSION_MAJOR}.${OCE_VERSION_MINOR}${OCE_VERSION_DEVEL})

set(OCE_ABI_SOVERSION 11)
set(OCE_ABI_VERSION ${OCE_ABI_SOVERSION}.0.0)

# Set the minimum version of cmake required to 2.6
cmake_minimum_required( VERSION 2.6 )

# Policy CMP0043 introduced in cmake version 3.0 IGNORES the use of COMPILE_DEFINITIONS suffixed variables, e.g. COMPILE_DEFINITIONS_DEBUG
# Set to OLD behavior until minimum cmake version >= 2.8.10 (version that COMPILE_DEFINITIONS can be set by generator expressions instead)
if (POLICY CMP0043)
	cmake_policy(SET CMP0043 OLD)
endif (POLICY CMP0043)
# Policy CMP0042 introduced in cmake version 3.0 enables the use of @rpath in an install name via MACOSX_RPATH by default
# Set to OLD behavior so that all versions use the same behavior, or until minimum cmake version >= 2.8.12 (version where @rpath is available)
if (POLICY CMP0042)
	cmake_policy(SET CMP0042 OLD)
endif (POLICY CMP0042)

# Define helper macro option_with_default
macro( option_with_default OPTION_NAME OPTION_STRING OPTION_DEFAULT )
	if( NOT DEFINED ${OPTION_NAME} )
		set( ${OPTION_NAME} ${OPTION_DEFAULT} )
	endif( NOT DEFINED ${OPTION_NAME} )
	option( ${OPTION_NAME} "${OPTION_STRING}" ${${OPTION_NAME}} )
endmacro( option_with_default OPTION_NAME OPTION_STRING OPTION_DEFAULT )

############################
# Check 32/64 bit platform #
############################
if (${CMAKE_SIZEOF_VOID_P} MATCHES "8") # It is 64bit, otherwise 32 bit systems match 4
	add_definitions(-D_OCC64)
	set(BIT 64)
else (${CMAKE_SIZEOF_VOID_P} MATCHES "8")
	set(BIT 32)
endif(${CMAKE_SIZEOF_VOID_P} MATCHES "8")

message(STATUS "Build ${BIT}bit")

if(NOT CMAKE_CONFIGURATION_TYPES)
	if(CMAKE_BUILD_TYPE STREQUAL "")
		set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type." FORCE)
		set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Release" "Debug" "RelWithDebInfo" "MinSizeRel")
	endif(CMAKE_BUILD_TYPE STREQUAL "")
endif(NOT CMAKE_CONFIGURATION_TYPES)

if(CMAKE_BUILD_TOOL STREQUAL "nmake")
	set(NMAKE TRUE)
endif(CMAKE_BUILD_TOOL STREQUAL "nmake")

if(MSVC)
	option_with_default( OCE_INSTALL_PDB_FILES "Install PDB files (debug informations)" ON )
	option_with_default( OCE_MULTITHREADED_BUILD "Multithreaded build (/MP Option)" ON )
endif(MSVC)

if(MINGW)
	option_with_default( OCE_INSTALL_PRIVATE_SAMEDIR "Install private DLLs in the same binary directory" OFF )
endif(MINGW)

############################
# Library name definitions #
############################

if(MSVC)
	set( OCE_LIBRARY_PREFIX "" )
	set( CMAKE_DEBUG_POSTFIX "d" )
else(MSVC)
	set( OCE_LIBRARY_PREFIX "lib" )
endif(MSVC)


if(APPLE)
	if(OCE_NO_LIBRARY_VERSION)
		set( OCE_LIBRARY_EXTENSION ${CMAKE_SHARED_LIBRARY_SUFFIX} )
	else(OCE_NO_LIBRARY_VERSION)
		set( OCE_LIBRARY_EXTENSION ".${OCE_ABI_SOVERSION}${CMAKE_SHARED_LIBRARY_SUFFIX}" )
	endif(OCE_NO_LIBRARY_VERSION)
elseif(WIN32)
	# Don't encode library versions on Windows systems
	set( OCE_LIBRARY_EXTENSION ${CMAKE_SHARED_LIBRARY_SUFFIX} )
else()
	if(OCE_NO_LIBRARY_VERSION)
		set( OCE_LIBRARY_EXTENSION ${CMAKE_SHARED_LIBRARY_SUFFIX} )
	else(OCE_NO_LIBRARY_VERSION)
		set( OCE_LIBRARY_EXTENSION "${CMAKE_SHARED_LIBRARY_SUFFIX}.${OCE_ABI_SOVERSION}" )
	endif(OCE_NO_LIBRARY_VERSION)
endif()

if(BORLAND)
	option_with_default( OCE_INSTALL_TDS_FILES "Instal TDS files (debug informations)" ON )
endif(BORLAND)

if(WIN32)
	option_with_default( OCE_AUTOINSTALL_DEPENDENT_LIBS "Autoinstall dependent DLLs" ON )
	mark_as_advanced(OCE_AUTOINSTALL_DEPENDENT_LIBS)
endif()

if ((MSVC AND NOT NMAKE) OR CMAKE_COMPILER_IS_GNUCXX)
	set(OCE_COMPILER_SUPPORTS_PCH TRUE)
	if(MSVC)
		option_with_default( OCE_USE_PCH "Use Precompiled Headers" ON )
	else()
		option_with_default( OCE_USE_PCH "Use Precompiled Headers" OFF )
	endif()
	mark_as_advanced(OCE_USE_PCH)
endif((MSVC AND NOT NMAKE) OR CMAKE_COMPILER_IS_GNUCXX)

option_with_default( OCE_BUILD_SHARED_LIB "Build shared OCE libs" ON )
if(APPLE)
	option_with_default( OCE_OSX_USE_COCOA "Use native OSX Cocoa backend" ON )
endif(APPLE)
if(NOT MSVC AND NOT OCE_OSX_USE_COCOA)
	option_with_default( OCE_DISABLE_X11 "Disable components requiring X11 support" OFF )
	if(NOT APPLE AND NOT WIN32)
		mark_as_advanced(OCE_DISABLE_X11)
	endif(NOT APPLE AND NOT WIN32)
endif(NOT MSVC AND NOT OCE_OSX_USE_COCOA)
option_with_default( OCE_MODEL "Build model components" ON )
option_with_default( OCE_OCAF "Build application framework" ON )
option_with_default( OCE_DATAEXCHANGE "Build data exchange" ON )
option_with_default( OCE_DRAW "Build test harness \(DRAW\)" OFF )
option_with_default( OCE_VISUALISATION "Build visualisation component" ON )
option_with_default( OCE_WITH_GL2PS "Build with GL2PS" OFF )
option_with_default( OCE_WITH_FREEIMAGE "Build with FreeImage" OFF )
option_with_default( OCE_WITH_VTK "Build with VTK" OFF )
option_with_default( OCE_DISABLE_TKSERVICE_FONT "Disable TKService Font (only without Visualization)" OFF )
mark_as_advanced(OCE_DISABLE_TKSERVICE_FONT)
if(NOT WIN32)
  option_with_default( OCE_BUILD_TKERNEL_WITH_INSTALL_RPATH "Build TKernel with install RPATH" ON )
  mark_as_advanced(OCE_BUILD_TKERNEL_WITH_INSTALL_RPATH)
endif()
option_with_default( OCE_EXTRA_WARNINGS "Enable Maximum Warnings Level" OFF )
mark_as_advanced(OCE_EXTRA_WARNINGS)
if( NOT "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.8 )
	option_with_default( OCE_TESTING "Enable unittesting framework" ON )
endif( NOT "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.8 )
option_with_default( OCE_ADD_HEADERS "Add headers to project files" OFF )
mark_as_advanced(OCE_ADD_HEADERS)
if (NOT WIN32)
	option_with_default( OCE_RPATH_FILTER_SYSTEM_PATHS "Filter out system paths from RPATH" ON )
	mark_as_advanced(OCE_RPATH_FILTER_SYSTEM_PATHS)
endif (NOT WIN32)
# When building OCE as part of another application, it may be useful to copy
# header files in a temporary location so that dependent applications can be built
option_with_default( OCE_COPY_HEADERS_BUILD "Copy header files when building OCE" OFF )

option_with_default( OCE_USE_TCL_TEST_FRAMEWORK "Add occt-tests target" OFF )

#
# By default, OSX uses X11 OpenGl implementation
#
if (APPLE)
	if (NOT OCE_OSX_USE_COCOA)
		set(MACOSX_USE_GLX TRUE)
	endif(NOT OCE_OSX_USE_COCOA)
endif(APPLE)
# The default for the OCCT_DEBUG define is ON for all the platforms , in debug mode.
# In MSVC it is not desirable to have it ON by default, since users must
# compile/use the OCE debug libraries to build it's own programs in DEBUG mode.
# OCCT_DEBUG should be enabled by developers only, in this case
if ((MSVC OR BORLAND) AND CMAKE_CONFIGURATION_TYPES)
	set (DEB_DEFAULT "OFF")
else ()
	set (DEB_DEFAULT "ON")
endif ((MSVC OR BORLAND) AND CMAKE_CONFIGURATION_TYPES)

option_with_default( OCE_ENABLE_DEB_FLAG "Enables OCCT_DEBUG define in debug configuration" ${DEB_DEFAULT} )
mark_as_advanced(OCE_ENABLE_DEB_FLAG)

if(NOT MSVC)
	option_with_default( OCE_COVERAGE "Build with coverage testing" OFF )
	mark_as_advanced(OCE_COVERAGE)
	if(OCE_COVERAGE)
		set( CMAKE_BUILD_TYPE "Debug" CACHE INTERNAL "Build type, immutable" FORCE )
	endif(OCE_COVERAGE)
endif(NOT MSVC)

if( NOT DEFINED OCE_MULTITHREAD_LIBRARY)
	set( OCE_MULTITHREAD_LIBRARY "NONE" CACHE STRING "(values are: NONE TBB OPENMP)" )
endif( NOT DEFINED OCE_MULTITHREAD_LIBRARY)

if (${CMAKE_VERSION} VERSION_GREATER 2.8)
	set_property(CACHE OCE_MULTITHREAD_LIBRARY PROPERTY STRINGS NONE TBB OPENMP)
endif (${CMAKE_VERSION} VERSION_GREATER 2.8)

option( OCE_MULTITHREAD_LIBRARY "Multithread library" ${OCE_MULTITHREAD_LIBRARY} )

if( OCE_MULTITHREAD_LIBRARY STREQUAL "TBB" )
	option_with_default( OCE_TBB_MALLOC_SUPPORT "Use TBB for memory allocation" ON )
endif( OCE_MULTITHREAD_LIBRARY STREQUAL "TBB" )

if( OCE_USE_TCL_TEST_FRAMEWORK )
	set( tcl_test_groups 3rdparty;blend;boolean;bugs;caf;chamfer;de;demo;draft;feat;geometry;heal;mesh;mkface;nproject;offset;perf;pipe;prism;sewing;thrusection;v3d;xcaf;xml )
	if( NOT DEFINED OCE_TCL_TEST_GROUP)
		set( OCE_TCL_TEST_GROUP "ALL" CACHE STRING "Group of OCCT test packages to run (values are: ALL;${tcl_test_groups})" )
	endif( NOT DEFINED OCE_TCL_TEST_GROUP)
	mark_as_advanced(OCE_TCL_TEST_GROUP)
	if (${CMAKE_VERSION} VERSION_GREATER 2.8)
		set_property(CACHE OCE_TCL_TEST_GROUP PROPERTY STRINGS "ALL;${tcl_test_groups}")
	endif (${CMAKE_VERSION} VERSION_GREATER 2.8)
endif( OCE_USE_TCL_TEST_FRAMEWORK )

if( NOT DEFINED OCE_INSTALL_PREFIX )
	if( WIN32 )
		set(OCE_INSTALL_PREFIX
			"c:/OCE-${OCE_VERSION}")
	else( WIN32 )
		set(OCE_INSTALL_PREFIX
			"/usr/local")
	endif( WIN32 )
endif( NOT DEFINED OCE_INSTALL_PREFIX )

set( OCE_INSTALL_PREFIX ${OCE_INSTALL_PREFIX} CACHE
	PATH "Install prefix prepended to target to create install location" )
set( CMAKE_INSTALL_PREFIX "${OCE_INSTALL_PREFIX}" CACHE INTERNAL "Prefix
	prepended to install directories if target destination is not absolute,
	immutable" FORCE )

if( OCE_BUILD_SHARED_LIB )
	set( OCE_LIBRARY_TYPE SHARED )
	set( OCE_BUILD_STATIC_LIB FALSE )
else( OCE_BUILD_SHARED_LIB )
	set( OCE_LIBRARY_TYPE STATIC )
	set( OCE_BUILD_STATIC_LIB TRUE )
	if ( WIN32 )
		add_definitions("-DHAVE_NO_DLL")
	endif( WIN32 )
endif( OCE_BUILD_SHARED_LIB )

# MSVC specific options
if(MSVC_IDE)
	if (NOT DEFINED OCE_USE_MSVC_EXPRESS )
		set (OCE_USE_MSVC_EXPRESS OFF)
	endif (NOT DEFINED OCE_USE_MSVC_EXPRESS)
	option( OCE_USE_MSVC_EXPRESS "Use a Visual C++ express IDE"
		${OCE_USE_MSVC_EXPRESS} )

	if(NOT OCE_USE_MSVC_EXPRESS)
		#Use solution folders.
		set_property(GLOBAL PROPERTY USE_FOLDERS ON)
		set(USE_SOLUTION_FOLDERS TRUE)
	else( NOT OCE_USE_MSVC_EXPRESS)
		set_property(GLOBAL PROPERTY USE_FOLDERS OFF)
	endif( NOT OCE_USE_MSVC_EXPRESS)

	option( OCE_USE_STATIC_MSVC_RUNTIME "Use static version of the MSVC run-time library" OFF )
	mark_as_advanced( OCE_USE_STATIC_MSVC_RUNTIME )
endif(MSVC_IDE)

set_directory_properties(PROPERTIES COMPILE_DEFINITIONS_RELEASE NDEBUG)
set_directory_properties(PROPERTIES COMPILE_DEFINITIONS_MINSIZEREL NDEBUG)
set_directory_properties(PROPERTIES COMPILE_DEFINITIONS_RELWITHDEBINFO  NDEBUG)

if(OCE_ENABLE_DEB_FLAG)
	set_directory_properties(PROPERTIES COMPILE_DEFINITIONS_DEBUG "OCCT_DEBUG=1;_DEBUG")
else ()
	set_directory_properties(PROPERTIES COMPILE_DEFINITIONS_DEBUG "_DEBUG")
endif (OCE_ENABLE_DEB_FLAG)

if(OCE_MULTITHREAD_LIBRARY STREQUAL "NONE")
    add_definitions(-DIGNORE_NO_ATOMICS)
endif (OCE_MULTITHREAD_LIBRARY STREQUAL "NONE")

#  Make OCE version visible to OCC_VERSION_STRING_EXT
set(OCC_VERSION_DEVELOPMENT oce-${OCE_VERSION})

#
# Check components dependencies
#
set(OCE_FOUNDATION TRUE)
if(OCE_OCAF OR OCE_DATAEXCHANGE OR OCE_VISUALISATION OR OCE_DRAW)
	set(OCE_VISU_DEP TRUE)
else(OCE_OCAF OR OCE_DATAEXCHANGE OR OCE_VISUALISATION OR OCE_DRAW)
	set(OCE_VISU_DEP FALSE)
endif(OCE_OCAF OR OCE_DATAEXCHANGE OR OCE_VISUALISATION OR OCE_DRAW)
if(OCE_DISABLE_X11)
	set(OCE_VISU_DEP FALSE)
endif(OCE_DISABLE_X11)
if(OCE_DISABLE_X11 OR OCE_DISABLE_TKSERVICE_FONT)
	set(OCE_DRAW OFF CACHE BOOL "Build DRAWEXE" FORCE)
	set(OCE_VISUALISATION OFF CACHE BOOL "Build visualisation component" FORCE)
endif(OCE_DISABLE_X11 OR OCE_DISABLE_TKSERVICE_FONT)
if(OCE_DISABLE_TKSERVICE_FONT)
	# AIS_Dimension.cxx uses this flag to remove font-dependent code
	add_definitions(-DOCE_DISABLE_TKSERVICE_FONT)
endif(OCE_DISABLE_TKSERVICE_FONT)

if(NOT OCE_BUILD_SHARED_LIB AND OCE_DRAW)
	set(OCE_DRAW OFF CACHE BOOL "Build DRAWEXE" FORCE)
	message("Warning : DRAW disabled when statically linking")
endif(NOT OCE_BUILD_SHARED_LIB AND OCE_DRAW)

if(OCE_DRAW AND NOT OCE_DATAEXCHANGE)
	set(OCE_DATAEXCHANGE ON CACHE BOOL "Build data exchange" FORCE)
endif(OCE_DRAW AND NOT OCE_DATAEXCHANGE)
if(OCE_DATAEXCHANGE AND NOT OCE_OCAF)
	set(OCE_OCAF ON CACHE BOOL "Build application framework" FORCE)
endif(OCE_DATAEXCHANGE AND NOT OCE_OCAF)
if(OCE_OCAF AND NOT OCE_MODEL)
	set(OCE_MODEL ON CACHE BOOL "Build model components" FORCE)
endif(OCE_OCAF AND NOT OCE_MODEL)
if(OCE_VISUALISATION AND NOT OCE_MODEL)
	set(OCE_MODEL ON CACHE BOOL "Build model components" FORCE)
endif(OCE_VISUALISATION AND NOT OCE_MODEL)
if(OCE_DRAW AND NOT OCE_VISUALISATION)
	set(OCE_VISUALISATION ON CACHE BOOL "Build visualisation component" FORCE)
endif(OCE_DRAW AND NOT OCE_VISUALISATION)

# oce-win-bundle handling for MSVC and MINGW
if(MSVC OR MINGW)
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/oce-win-bundle/oce-bundle-root.empty")
      MESSAGE("Using oce-win-bundle checkout")
      option_with_default( OCE_USE_BUNDLE "Use OCE Windows Bundle that has been built and installed" ON )
      
      if(OCE_USE_BUNDLE)
          ADD_SUBDIRECTORY(oce-win-bundle)
          SET(OCE_SKIP_FIND_LIBRARIES TRUE)
      ENDIF()
  endif()
endif(MSVC OR MINGW)

if(OCE_VISUALISATION AND OCE_WITH_VTK)
	# Try to find the required VTK components.
	find_package(VTK QUIET COMPONENTS vtkCommonCore vtkInteractionStyle vtkIOExport vtkIOLegacy)

	# Now that we know we have a VTK version available, we call find_package with the correct rendering backend.
	if( NOT(VTK_VERSION_MAJOR LESS 7) AND VTK_RENDERING_BACKEND)
		# In VTK 7, the rendering backend is exported in the variable VTK_RENDERING_BACKEND
		find_package(VTK QUIET COMPONENTS vtkRendering${VTK_RENDERING_BACKEND} vtkCommonCore vtkInteractionStyle vtkIOExport vtkIOLegacy)
	else()
		find_package(VTK QUIET COMPONENTS vtkRenderingOpenGL vtkCommonCore vtkInteractionStyle vtkIOExport vtkIOLegacy)
	endif()

	if (TARGET vtkRenderingOpenGL2)
		add_definitions(-DOCE_VTK_OPENGL2_BACKEND)
	endif()
endif()

set(INSTALL_STDRESOURCE_FILES)
set(INSTALL_RESOURCE_FILES)
file(GLOB OS_TCL_SCRIPTS RELATIVE ${OCE_SOURCE_DIR} src/OS/*.tcl)
set(INSTALL_RESOURCE_FILES ${INSTALL_RESOURCE_FILES}
	${OS_TCL_SCRIPTS}
	src/UnitsAPI/Lexi_Expr.dat
	src/UnitsAPI/Units.dat )
set(INSTALL_STDRESOURCE_FILES ${INSTALL_STDRESOURCE_FILES}
	src/UnitsAPI/CurrentUnits
	src/UnitsAPI/MDTVBaseUnits
	src/UnitsAPI/MDTVCurrentUnits )

find_package(Threads)
if(OCE_MULTITHREAD_LIBRARY STREQUAL "TBB")
	find_path(TBB_INCLUDE_DIR tbb/tbb.h DOC "Location of header files for TBB (containing tbb/tbb.h)" ${CMAKE_SYSTEM_INCLUDE_PATH})
	if(TBB_INCLUDE_DIR)
		if(MSVC)
			if(CMAKE_CL_64)
				set(TBB_ARCH intel64)
			else(CMAKE_CL_64)
				set(TBB_ARCH ia32)
			endif(CMAKE_CL_64)

			get_filename_component(TBB_ROOT "${TBB_INCLUDE_DIR}/.." ABSOLUTE)
			if(OCE_BUILD_SHARED_LIB)
				if(MSVC80)
					set(TBB_BIN_DIR "${TBB_ROOT}/bin/${TBB_ARCH}/vc8")
					set(TBB_LIB_DIR "${TBB_ROOT}/lib/${TBB_ARCH}/vc8")
				elseif(MSVC90)
					set(TBB_BIN_DIR "${TBB_ROOT}/bin/${TBB_ARCH}/vc9")
					set(TBB_LIB_DIR "${TBB_ROOT}/lib/${TBB_ARCH}/vc9")
				elseif(MSVC10)
					set(TBB_BIN_DIR "${TBB_ROOT}/bin/${TBB_ARCH}/vc10")
					set(TBB_LIB_DIR "${TBB_ROOT}/lib/${TBB_ARCH}/vc10")
				elseif(MSVC11)
					set(TBB_BIN_DIR "${TBB_ROOT}/bin/${TBB_ARCH}/vc11")
					set(TBB_LIB_DIR "${TBB_ROOT}/lib/${TBB_ARCH}/vc11")
				elseif(MSVC12)
					set(TBB_BIN_DIR "${TBB_ROOT}/bin/${TBB_ARCH}/vc12")
					set(TBB_LIB_DIR "${TBB_ROOT}/lib/${TBB_ARCH}/vc12")
				endif()
			else(OCE_BUILD_SHARED_LIB)
				set(TBB_LIB_DIR "${TBB_ROOT}/lib/${TBB_ARCH}/vc_mt")
			endif(OCE_BUILD_SHARED_LIB)
		endif(MSVC)

		find_library( TBB_LIBRARY tbb PATHS "${TBB_LIB_DIR}" "Path to the TBB library" )
		if (OCE_TBB_MALLOC_SUPPORT)
			find_library( TBB_MALLOC_LIBRARY tbbmalloc PATHS "${TBB_LIB_DIR}" "Path to the TBB MALLOC library")
		endif (OCE_TBB_MALLOC_SUPPORT)
		if(CMAKE_CONFIGURATION_TYPES OR NMAKE)
			find_library( TBB_LIBRARY_DEBUG tbb_debug PATHS "${TBB_LIB_DIR}" "Path to the TBB debug library" )
			if (OCE_TBB_MALLOC_SUPPORT)
				find_library( TBB_MALLOC_LIBRARY_DEBUG tbbmalloc_debug PATHS "${TBB_LIB_DIR}" "Path to the TBB MALLOC debug library")
			endif (OCE_TBB_MALLOC_SUPPORT)
		endif(CMAKE_CONFIGURATION_TYPES OR NMAKE)
	endif(TBB_INCLUDE_DIR)
	mark_as_advanced(TBB_INCLUDE_DIR TBB_LIBRARY)
endif(OCE_MULTITHREAD_LIBRARY STREQUAL "TBB")

if(OCE_MULTITHREAD_LIBRARY STREQUAL "OPENMP")
	find_package(OpenMP)
endif(OCE_MULTITHREAD_LIBRARY STREQUAL "OPENMP")

if(OCE_VISU_DEP AND NOT OCE_DISABLE_TKSERVICE_FONT)
	set(OCE_REQUIRES_FREETYPE TRUE)
endif()

if(OCE_VISU_DEP)
	## TKService requires OpenGL on Unix, see src/Xw/Xw_Window.cxx
	if (NOT (WIN32 OR (APPLE AND OCE_OSX_USE_COCOA)))
		find_package(OpenGL REQUIRED)
	endif (NOT (WIN32 OR (APPLE AND OCE_OSX_USE_COCOA)))
endif(OCE_VISU_DEP)

if(OCE_REQUIRES_FREETYPE AND NOT OCE_SKIP_FIND_LIBRARIES)
	## TKService requires FreeType
	find_package(Freetype REQUIRED)
	
	if(CMAKE_CONFIGURATION_TYPES OR NMAKE)
		find_library(FREETYPE_LIBRARY_DEBUG freetyped "Location of freetype debug library")
	endif(CMAKE_CONFIGURATION_TYPES OR NMAKE)
endif()

if(OCE_VISUALISATION)
	if(OCE_WITH_FREEIMAGE)
		find_path(FREEIMAGE_INCLUDE_DIR FreeImagePlus.h DOC "Location of header files for FreeImage" ${CMAKE_SYSTEM_INCLUDE_PATH})
		if(FREEIMAGE_INCLUDE_DIR)
			find_library( FREEIMAGE_LIBRARY freeimage "Path to the freeimage library" )

			if(CMAKE_CONFIGURATION_TYPES OR NMAKE)
				find_library( FREEIMAGE_LIBRARY_DEBUG freeimaged "Path to the freeimage debug library" )
			endif(CMAKE_CONFIGURATION_TYPES OR NMAKE)
		endif(FREEIMAGE_INCLUDE_DIR)
		mark_as_advanced(FREEIMAGE_INCLUDE_DIR FREEIMAGE_LIBRARY)
		if(WIN32)
			if(FREEIMAGE_INCLUDE_DIR)
				find_library( FREEIMAGEPLUS_LIBRARY freeimageplus "Path to the freeimageplus library" )
				if(CMAKE_CONFIGURATION_TYPES OR NMAKE)
					find_library( FREEIMAGEPLUS_LIBRARY_DEBUG freeimageplusd "Path to the freeimageplus debug library" )
				endif(CMAKE_CONFIGURATION_TYPES OR NMAKE)
			endif(FREEIMAGE_INCLUDE_DIR)
			mark_as_advanced(FREEIMAGEPLUS_LIBRARY)
		endif(WIN32)
	endif(OCE_WITH_FREEIMAGE)

	if (NOT WIN32 AND NOT OCE_OSX_USE_COCOA)
		find_package(X11 REQUIRED)
	endif(NOT WIN32 AND NOT OCE_OSX_USE_COCOA)

	if (NOT APPLE OR OCE_OSX_USE_COCOA)
		find_package(OpenGL REQUIRED)
		if(NOT ${OPENGL_GLU_FOUND} STREQUAL "YES")
			message( FATAL_ERROR "GLU not found" )
		endif(NOT ${OPENGL_GLU_FOUND} STREQUAL "YES")
	else (NOT APPLE OR OCE_OSX_USE_COCOA)
		set(OPENGL_INCLUDE_DIR /usr/X11R6/include/)
		set(OPENGL_LIBRARIES /usr/X11R6/lib/libGL.dylib /usr/X11R6/lib/libGLU.dylib)
	endif (NOT APPLE OR OCE_OSX_USE_COCOA)

	## GL2PS
	if(OCE_WITH_GL2PS)
		find_path(GL2PS_INCLUDE_DIR gl2ps.h DOC "Location of header files for GL2PS (containing gl2ps.h)" ${CMAKE_SYSTEM_INCLUDE_PATH})
		if(GL2PS_INCLUDE_DIR)
			find_library( GL2PS_LIBRARY gl2ps "Path to the gl2ps library" )
			if(CMAKE_CONFIGURATION_TYPES OR NMAKE)
				find_library( GL2PS_LIBRARY_DEBUG gl2psd "Path to the gl2ps debug library" )
			endif(CMAKE_CONFIGURATION_TYPES OR NMAKE)
		endif(GL2PS_INCLUDE_DIR)
		mark_as_advanced(GL2PS_INCLUDE_DIR GL2PS_LIBRARY)
	endif(OCE_WITH_GL2PS)

	if (NOT WIN32 AND NOT OCE_OSX_USE_COCOA)
		message(STATUS "X11 LIBS: ${X11_LIBRARIES}")
	endif(NOT WIN32 AND NOT OCE_OSX_USE_COCOA)
	message(STATUS "OPENGL LIBS: ${OPENGL_LIBRARIES}")
	message(STATUS "FREETYPE LIBS: ${FREETYPE_LIBRARIES}")
	message(STATUS "FREETYPE INCLUDES: ${FREETYPE_INCLUDE_DIRS}")
	message(STATUS "THREAD LIB: ${CMAKE_THREAD_LIBS_INIT}")

	file(GLOB TEXTURES_RGB_FILES RELATIVE ${OCE_SOURCE_DIR} src/Textures/*.rgb)
	file(GLOB SHADERS_FILES RELATIVE ${OCE_SOURCE_DIR} src/Shaders/*.*)
	set(INSTALL_RESOURCE_FILES ${INSTALL_RESOURCE_FILES} ${TEXTURES_RGB_FILES} ${SHADERS_FILES})
endif(OCE_VISUALISATION)

if(OCE_OCAF)
	file(GLOB XMLOCAFRESOURCE_XSD_FILES RELATIVE ${OCE_SOURCE_DIR} src/XmlOcafResource/*.xsd)
	set(INSTALL_RESOURCE_FILES ${INSTALL_RESOURCE_FILES}
		${XMLOCAFRESOURCE_XSD_FILES}
		src/StdResource/MigrationSheet.txt
		src/StdResource/MDTV-Standard.xwd
		src/StdResource/Plugin
		src/StdResource/Standard
		src/StdResource/Standard.us
		src/StdResource/StandardLite
		src/StdResource/TObj
		src/StdResource/XCAF )
endif(OCE_OCAF)

if(OCE_DATAEXCHANGE)
	set(INSTALL_RESOURCE_FILES ${INSTALL_RESOURCE_FILES}
		src/SHMessage/SHAPE.fr
		src/SHMessage/SHAPE.us
		src/XSMessage/IGES.fr
		src/XSMessage/IGES.us
		src/XSMessage/XSTEP.fr
		src/XSMessage/XSTEP.us
		src/XSTEPResource/IGES
		src/XSTEPResource/STEP)
endif(OCE_DATAEXCHANGE)

if(OCE_VISUALISATION)
	set(INSTALL_RESOURCE_FILES ${INSTALL_RESOURCE_FILES}
		src/Shaders/Declarations.glsl
		src/Shaders/DeclarationsImpl.glsl
		src/Shaders/FILES
		src/Shaders/PhongShading.fs
		src/Shaders/PhongShading.vs
		src/Shaders/RaytraceBase.fs
		src/Shaders/RaytraceBase.vs
		src/Shaders/RaytraceRender.fs
		src/Shaders/RaytraceSmooth.fs)
endif(OCE_VISUALISATION)

if(OCE_DRAW)
	if (APPLE AND NOT OCE_OSX_USE_COCOA)
		# under OSX-X11, should use a X11 based TCL/TK, for instance fink's implementation
		set(FINK_INSTALL_PATH /sw)
		mark_as_advanced(FINK_INSTALL_PATH)
		set(TCL_LIBRARY ${FINK_INSTALL_PATH}/lib/libtcl.dylib)
		set(TCL_INCLUDE_PATH ${FINK_INSTALL_PATH}/include)
		set(TCL_TCLSH ${FINK_INSTALL_PATH}/bin/tclsh)
		set(TK_LIBRARY ${FINK_INSTALL_PATH}/lib/libtk.dylib)
		set(TK_INCLUDE_PATH ${FINK_INSTALL_PATH}/include)
		set(TK_WISH ${FINK_INSTALL_PATH}/bin/wish)
		mark_as_advanced(TCL_INCLUDE_PATH TK_INCLUDE_PATH TCL_LIBRARY TK_LIBRARY)
	else(APPLE AND NOT OCE_OSX_USE_COCOA)
		find_package(TCL REQUIRED)
	endif(APPLE AND NOT OCE_OSX_USE_COCOA)
	message(STATUS "TCL LIB: ${TCL_LIBRARY}")
	message(STATUS "TK LIB: ${TK_LIBRARY}")
	file(GLOB DRAWRESOURCES_TCL_FILES RELATIVE ${OCE_SOURCE_DIR} src/DrawResources/*.tcl)
	set(INSTALL_RESOURCE_FILES ${INSTALL_RESOURCE_FILES}
		${DRAWRESOURCES_TCL_FILES}
		src/DrawResources/DrawDefault
		src/DrawResources/DrawPlugin
		src/DrawResources/lamp.ico
		src/TObj/TObj.msg )
endif(OCE_DRAW)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/build_inc
	${CMAKE_CURRENT_SOURCE_DIR}/inc)

if(OCE_COPY_HEADERS_BUILD)
	include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)
endif(OCE_COPY_HEADERS_BUILD)
 
###################################
# Architecture-specific libraries #
###################################
if(WIN32)
	set(LM)
	set(CSF_gdi32_LIB gdi32)
	set(CSF_advapi32_LIB advapi32)
	set(CSF_user32_LIB user32)
	set(CSF_kernel32_LIB kernel32)
	set(CSF_SOCKETLibs_LIB ws2_32)
	set(CSF_wsock32_LIB ws2_32)
	set(CSF_psapi_LIB psapi)
else(WIN32)
	set(LM "-lm")
	set(WIN32_LIBS "")
	set(CSF_gdi32_LIB "")
	set(CSF_advapi32_LIB "")
	set(CSF_user32_LIB "")
	set(CSF_kernel32_LIB "")
	set(CSF_SOCKETLibs_LIB "")
	set(CSF_wsock32_LIB "")
	set(CSF_psapi_LIB "")
endif(WIN32)

###################################################
# Check required headers, functions and libraries #
###################################################
if (NOT WIN32)
	# Check headers
	# I think these should all be check cxx headers, as I think there is no c
	# compilation anywhere in OCE
	include(CheckIncludeFile)
	check_include_file(strings.h HAVE_STRINGS_H)
	check_include_file(xlocale.h HAVE_XLOCALE_H)
	include(CheckIncludeFileCXX)
	check_include_file_cxx(mm_malloc.h HAVE_MM_MALLOC_H)
	check_include_file_cxx(atomic.h OCE_HAVE_ATOMIC_H)
	# Check library functions
	include(CheckFunctionExists)
	check_function_exists(localtime_r HAVE_LOCALTIME_R)
	check_function_exists(clock_gettime HAVE_CLOCK_GETTIME)
	check_function_exists(posix_memalign HAVE_POSIX_MEMALIGN)
	include(TestBigEndian)
	test_big_endian(WORDS_BIGENDIAN)

# TODO: check all headers/functions/libraries that are checked in configure.ac original OCC script
endif(NOT WIN32)

#######################################################
# Check compiler version - Determine Borland compiler #
#######################################################
if(BORLAND AND NOT BORLAND_VERSION)
	if(EXISTS ${CMAKE_CXX_COMPILER})
		execute_process(
			COMMAND ${CMAKE_CXX_COMPILER}  /?
			OUTPUT_VARIABLE _output
			ERROR_QUIET
		)

		string(REGEX MATCH "Embarcadero C[+][+] [0-9]+.[0-9]+"
			_borland_version "${_output}")

		if(_borland_version)
			string(REGEX MATCHALL "[0-9]+" _borland_version_list "${_borland_version}")
			list(GET _borland_version_list 0 _borland_major)
			list(GET _borland_version_list 1 _borland_minor)
		else()
			string(REGEX MATCH "Borland C[+][+] [0-9]+].[0-9]+"
				_borland_version "${_output}")

			if(_borland_version)
				string(REGEX MATCHALL "[0-9]+" _borland_version_list "${_borland_version}")
				list(GET _borland_version_list 0 _borland_major)
				list(GET _borland_version_list 1 _borland_minor)
			endif()
		endif()

		# XE2 compiler?
		if("v${_borland_major}.${_borland_minor}" STREQUAL "v6.41")
			set(BORLAND_VERSION "bcc32 v6.41 (RS XE2)")
			set(BORLAND_VERSION_RS_XE2 1)
		# XE compiler?
		elseif("v${_borland_major}.${_borland_minor}" STREQUAL "v6.30")
			set(BORLAND_VERSION "bcc32 v6.30 (RS XE)")
			set(BORLAND_VERSION_RS_XE 1)
		# 2010 compiler?
		elseif("v${_borland_major}.${_borland_minor}" STREQUAL "v6.20")
			set(BORLAND_VERSION "bcc32 v6.20 (RS 2010)")
			set(BORLAND_VERSION_RS_2010 1)
		# TODO: 2009 compiler?
		# TODO: 2007 compiler?
		# 2006 compiler?
		elseif("v${_borland_major}.${_borland_minor}" STREQUAL "v5.82")
			set(BORLAND_VERSION "bcc32 v5.82 (BDS 2006)")
			set(BORLAND_VERSION_BDS_2006 1)
		#TODO: Older compilers?
		else()
			set(BORLAND_VERSION "Unknown")
		endif()

		unset(_output)
		unset(_borland_version)
		unset(_borland_major)
		unset(_borland_minor)
	endif()
endif()

#######################################################
# Check platforms - Define specific compilation flags #
#######################################################
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CLANG TRUE)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
	set(INTEL TRUE)
endif()

if(UNIX)
	if(APPLE)
		######### MacOSX ###########
		message(STATUS "MacOSX platform detected")
		set(PLATFORM Darwin)
	else(APPLE)
		######### Unix/Linux ###########
		message(STATUS "Unix/Linux platform detected")
		set(PLATFORM Unix)
		if(INTEL)
			# Disable meaningless remarks
			# remark #383 given when initializing from a literal, e.g. abc("123")
			# remark #522 given when a function is defined inline but prototype is not
			# remark #858 given when a type qualifier is applied to a function return type
			# remark #981 "operands are evaluated in unspecified order", e.g. a = b() + c()
			add_definitions("-diag-disable 383,522,858,981")
		endif(INTEL)
	endif(APPLE)
	add_definitions(-DHAVE_CONFIG_H -DCSFDB -DOCC_CONVERT_SIGNALS)
else(UNIX)
	if(WIN32)
		######### Windows ###########
		message(STATUS "Windows system detected")
		add_definitions(-DWNT -DWIN32 -D_WINDOWS -DCSFDB -DHAVE_CONFIG_H )
		######### Borland ###########
		if(BORLAND)
			message(STATUS "Borland compiler detected: ${BORLAND_VERSION}")
		endif(BORLAND)
		set(PLATFORM win)
	else(WIN32)
		message(STATUS "Unknown platform")
	endif(WIN32)
endif(UNIX)
# TODO: better detection of different Unices (Linux, Solaris etc.)
# TODO: add CXX compiler flags for each platform

# Enable Extra warnings for each compiler
if( OCE_EXTRA_WARNINGS)
	if(MSVC)
		add_definitions("/W4 /wd4100 /wd4206 /wd4127")
	endif(MSVC)
	if(CMAKE_COMPILER_IS_GNUCXX)
		add_definitions("-Wall -Wextra")
	endif(CMAKE_COMPILER_IS_GNUCXX)
	if(CLANG)
		add_definitions("-Weverything")
	endif(CLANG)
	if(BORLAND)
		#TODO
	endif(BORLAND)
	if(INTEL)
		add_definitions("-Wall -Wremarks")
	endif(INTEL)
endif(OCE_EXTRA_WARNINGS)

if(OCE_MULTITHREADED_BUILD)
   if(MSVC AND NOT NMAKE) # /MP is useless in nmake
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
   endif()
endif()

#  Detect build problems with duplicate types
try_compile(CHECK_BODY_TEMPLATE ${CMAKE_BINARY_DIR}/CMakeTmpDup
	${OCE_SOURCE_DIR}/adm/cmake/config/TestDuplicateBodyTemplate.cxx
)
if (NOT CHECK_BODY_TEMPLATE)
	message(STATUS "Duplicate types found, do not define HashCode(Standard_Utf32Char)")
	set (OCE_IS_DUPLICATE_UINT32_T TRUE)
endif ()

################################################
# Define output path for generated libraries:  #
# platform/compiler-build_type-bits            #
# for instance:                                #
#     ./win32/bin/vc7.1-release-64             #
#     ./win32/bin/vc9-debug-32                 #
#     ./Unix/i386-debug-64                     #
################################################
if(WIN32)
	if(MSVC) # The compiler used is MSVC
		message(STATUS "Found MSVC compiler: ${MSVC} ${MSVC_VERSION}")
		set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/)
	else()
		IF (MINGW)
			message(STATUS "Found MINGW compiler: ${MINGW}")
		endif(MINGW)
		set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/win${BIT}/bin/${CMAKE_BUILD_TYPE})
	endif()
	set(EXECUTABLE_OUTPUT_PATH ${LIBRARY_OUTPUT_PATH})
else(WIN32)
	set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${PLATFORM}/${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_BUILD_TYPE}-${BIT})
endif(WIN32)
message(STATUS "output_path: ${LIBRARY_OUTPUT_PATH}")

# TODO: under win32/64, dlls and libs should not be in the same path (non MSVC)

if(MINGW)
	#MinGW Specific Flags
	message(STATUS "MinGW:")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mthreads")
	if(BIT MATCHES "64")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
	endif(BIT MATCHES "64")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mthreads")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mthreads -Wl,--export-all-symbols")
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -mthreads -Wl,--export-all-symbols")
	if(OCE_MULTITHREAD_LIBRARY STREQUAL "OPENMP")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fopenmp")
		set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fopenmp")
	endif(OCE_MULTITHREAD_LIBRARY STREQUAL "OPENMP")
	# For the file Message_MsgFile.cxx of TKernel we must additionally set the __TCollection_DLL define to resolve the needed HashCode() method
	set_source_files_properties("src/Message/Message_MsgFile.cxx" PROPERTIES COMPILE_FLAGS "-D__Message_DLL -D__TCollection_DLL")
	message(STATUS "CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}")
	
	# Define high enough WIN32 version
	add_definitions("-D_WIN32_WINNT=0x0501")
endif(MINGW)

# Disable secure CRT warnings and other MSVCRT specific things; disable bool conversion warning
if (MSVC)
	add_definitions("/D_CRT_SECURE_NO_WARNINGS /D_CRT_NONSTDC_NO_WARNINGS")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4800")

	if(OCE_USE_STATIC_MSVC_RUNTIME)
		message("Warning: OCE_USE_STATIC_MSVC_RUNTIME option can lead to deployment/maintenance issues. Use it when building
		an application executable that uses OCE, not when building redistributable OCE library for others
		to use. See the related discussion at https://github.com/tpaviot/oce/pull/577.")

		foreach(flag CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_MINSIZEREL
				CMAKE_CXX_FLAGS_RELWITHDEBINFO CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
				CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)
			if(${flag} MATCHES "/MD")
				STRING(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
			endif()
			if(${flag} MATCHES "/MDd")
				STRING(REGEX REPLACE "/MDd" "/MTd" ${flag} "${${flag}}")
			endif()
		endforeach()
	endif()
endif(MSVC)

# Libraries are installed by default in /usr/local/lib on UNIX
# based platforms and c:/OCE-VERSION/Win[32|64]/lib on windows based
# platforms

if(WIN32)
	set(_PSUFFIX "Win${BIT}/")
else(WIN32)
	set(_PSUFFIX "")
endif(WIN32)

# Binaries
if(NOT DEFINED OCE_INSTALL_BIN_DIR)
	set(OCE_INSTALL_BIN_DIR ${_PSUFFIX}bin)
endif(NOT DEFINED OCE_INSTALL_BIN_DIR)

# Libraries
if(NOT DEFINED OCE_INSTALL_LIB_DIR)
	set(OCE_INSTALL_LIB_DIR ${_PSUFFIX}lib${LIB_SUFFIX})
endif(NOT DEFINED OCE_INSTALL_LIB_DIR)

if(MSVC OR (MINGW AND OCE_INSTALL_PRIVATE_SAMEDIR))
	if(NOT DEFINED OCE_INSTALL_PACKAGE_LIB_DIR)
		set(OCE_INSTALL_PACKAGE_LIB_DIR ${OCE_INSTALL_LIB_DIR})
	endif(NOT DEFINED OCE_INSTALL_PACKAGE_LIB_DIR)
else(MSVC)
	if(NOT DEFINED OCE_INSTALL_PACKAGE_LIB_DIR)
		set(OCE_INSTALL_PACKAGE_LIB_DIR ${OCE_INSTALL_LIB_DIR}/oce-${OCE_VERSION})
	endif(NOT DEFINED OCE_INSTALL_PACKAGE_LIB_DIR)
endif()

# RPATHS
if(IS_ABSOLUTE ${OCE_INSTALL_LIB_DIR})
	set(OCE_INSTALL_LIB_DIR_RPATH ${OCE_INSTALL_LIB_DIR})
else(IS_ABSOLUTE ${OCE_INSTALL_LIB_DIR})
	set(OCE_INSTALL_LIB_DIR_RPATH ${OCE_INSTALL_PREFIX}/${OCE_INSTALL_LIB_DIR})
endif(IS_ABSOLUTE ${OCE_INSTALL_LIB_DIR})

if(IS_ABSOLUTE ${OCE_INSTALL_PACKAGE_LIB_DIR})
	set(OCE_INSTALL_PACKAGE_LIB_DIR_RPATH ${OCE_INSTALL_PACKAGE_LIB_DIR})
else(IS_ABSOLUTE ${OCE_INSTALL_PACKAGE_LIB_DIR})
	set(OCE_INSTALL_PACKAGE_LIB_DIR_RPATH ${OCE_INSTALL_PREFIX}/${OCE_INSTALL_PACKAGE_LIB_DIR})
endif(IS_ABSOLUTE ${OCE_INSTALL_PACKAGE_LIB_DIR})

# Includes
if(NOT DEFINED OCE_INSTALL_INCLUDE_DIR)
	set(OCE_INSTALL_INCLUDE_DIR include/oce)
endif(NOT DEFINED OCE_INSTALL_INCLUDE_DIR)

# Scripts
if(NOT DEFINED OCE_INSTALL_SCRIPT_DIR)
	set(OCE_INSTALL_SCRIPT_DIR ${OCE_INSTALL_PACKAGE_LIB_DIR})
endif(NOT DEFINED OCE_INSTALL_SCRIPT_DIR)

# Data
if(NOT DEFINED OCE_INSTALL_DATA_DIR)
	if(NOT MSVC)
		set(OCE_INSTALL_DATA_DIR share/oce-${OCE_VERSION})
	else ()
		set(OCE_INSTALL_DATA_DIR "share/oce")
	endif(NOT MSVC)
endif(NOT DEFINED OCE_INSTALL_DATA_DIR)
# Absolute path, written into oce-config.h
if(IS_ABSOLUTE ${OCE_INSTALL_DATA_DIR})
	set(OCE_ABSPATH_DATA_DIR ${OCE_INSTALL_DATA_DIR})
else(IS_ABSOLUTE ${OCE_INSTALL_DATA_DIR})
	set(OCE_ABSPATH_DATA_DIR ${CMAKE_INSTALL_PREFIX}/${OCE_INSTALL_DATA_DIR})
endif(IS_ABSOLUTE ${OCE_INSTALL_DATA_DIR})

# CMake
if(NOT DEFINED OCE_INSTALL_CMAKE_DATA_DIR)
	#  See http://www.cmake.org/cmake/help/cmake-2-8-docs.html#command:find_package
	#  and the definition of OCE_INSTALL_PREFIX at the beginning.
	#  CMake files are installed under INSTALL_PREFIX/INSTALL_CMAKE_DATA_DIR.
	if(WIN32)
		set(OCE_INSTALL_CMAKE_DATA_DIR cmake)
	else(WIN32)
		if(APPLE)
			set(OCE_INSTALL_CMAKE_DATA_DIR
				OCE.framework/Versions/${OCE_VERSION}/Resources)
		else(APPLE)
			set(OCE_INSTALL_CMAKE_DATA_DIR
				lib${LIB_SUFFIX}/oce-${OCE_VERSION})
		endif(APPLE)
	endif(WIN32)
endif(NOT DEFINED OCE_INSTALL_CMAKE_DATA_DIR)

# This relative path is written into OCEConfig.cmake to set OCE_INCLUDE_DIRS relative to OCEConfig.cmake
# There is no need to prepend OCE_INSTALL_PREFIX, CMake convention is to use slashes.
# The first part is required if -DOCE_INSTALL_CMAKE_DATA_DIR and -DOCE_INSTALL_INCLUDE_DIR are not both absolute paths.
if(IS_ABSOLUTE ${OCE_INSTALL_CMAKE_DATA_DIR})
	set(_OCE_INSTALL_CMAKE_DATA_DIR ${OCE_INSTALL_CMAKE_DATA_DIR})
else(IS_ABSOLUTE ${OCE_INSTALL_CMAKE_DATA_DIR})
	set(_OCE_INSTALL_CMAKE_DATA_DIR ${CMAKE_INSTALL_PREFIX}/${OCE_INSTALL_CMAKE_DATA_DIR})
endif(IS_ABSOLUTE ${OCE_INSTALL_CMAKE_DATA_DIR})
if(IS_ABSOLUTE ${OCE_INSTALL_INCLUDE_DIR})
	set(_OCE_INSTALL_INCLUDE_DIR ${OCE_INSTALL_INCLUDE_DIR})
else(IS_ABSOLUTE ${OCE_INSTALL_INCLUDE_DIR})
	set(_OCE_INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/${OCE_INSTALL_INCLUDE_DIR})
endif(IS_ABSOLUTE ${OCE_INSTALL_INCLUDE_DIR})
# Now the relative path can be generated
file(RELATIVE_PATH OCE_CMAKE_DATA_TO_INCLUDE_RELATIVE_DIR "${_OCE_INSTALL_CMAKE_DATA_DIR}" "${_OCE_INSTALL_INCLUDE_DIR}")

foreach(RESOURCE_FILE ${INSTALL_RESOURCE_FILES})
	get_filename_component(RESOURCE_PATH ${RESOURCE_FILE} PATH)
	install(FILES ${RESOURCE_FILE}
		DESTINATION ${OCE_INSTALL_DATA_DIR}/${RESOURCE_PATH})
endforeach(RESOURCE_FILE ${INSTALL_RESOURCE_FILES})
install(FILES ${INSTALL_STDRESOURCE_FILES}
	DESTINATION ${OCE_INSTALL_DATA_DIR}/src/StdResource)

if(WIN32)
	set(ENV_SCRIPTS
		${OCE_SOURCE_DIR}/scripts/env.bat
		${OCE_SOURCE_DIR}/scripts/msvc.bat
	)
	install(FILES ${ENV_SCRIPTS}
		DESTINATION ${OCE_INSTALL_SCRIPT_DIR})
endif(WIN32)

file(GLOB header_files ${OCE_SOURCE_DIR}/inc/*.*)

# Install each header file individually to work around a 8192 character
# argument limit on Visual Studio generators.
foreach(header ${header_files})
  install(FILES ${header}
    DESTINATION ${OCE_INSTALL_INCLUDE_DIR} COMPONENT Development
  )
endforeach()

set(OCE_INSTALL_DATA_DIR ${OCE_INSTALL_DATA_DIR})

#this is the header used to build OCE
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/adm/cmake/config/oce_build_config.h.cmake
	${CMAKE_CURRENT_BINARY_DIR}/build_inc/oce-config.h )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/build_inc/oce-config.h
	RENAME oce_build_config.defs
	DESTINATION ${OCE_INSTALL_INCLUDE_DIR} COMPONENT Development )

#installation paths are written into a separate file (which is not installed)
#so that only few files have to be recompiled when installation paths are modified
add_definitions(-DHAVE_OCE_PATHS_H)
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/adm/cmake/config/oce_build_paths.h.cmake
	${CMAKE_CURRENT_BINARY_DIR}/build_inc/oce-paths.h )

#this is the header that is installed on the system
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/adm/cmake/config/oce_install_config.h.cmake
	${CMAKE_CURRENT_BINARY_DIR}/install_inc/oce-config.h )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/install_inc/oce-config.h
		DESTINATION ${OCE_INSTALL_INCLUDE_DIR} COMPONENT Development )

# Version information
if(NOT OCE_NO_LIBRARY_VERSION)
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/adm/cmake/config/Version.rc.cmake
				${CMAKE_CURRENT_BINARY_DIR}/Version.rc)
set ( OCE_WIN32_RES_FILE ${CMAKE_CURRENT_BINARY_DIR}/Version.rc )
endif(NOT OCE_NO_LIBRARY_VERSION)

macro(process_module modulename modules_std)
	set(modules ${modules_std})
	if(NOT OCE_DISABLE_X11)
		list(APPEND modules ${ARGN})
	endif(NOT OCE_DISABLE_X11)
	foreach(module ${modules})
		if(NOT module MATCHES ".*EXE")
			list(APPEND OCE_LIBRARIES ${module})
		endif()
		set(TOOLKIT_MODULES "")
		set(TOOLKIT_DEPENDS "")
		set(TOOLKIT_INCLUDE_DIRECTORIES "")
		set(TOOLKIT_LIBS "")
		add_subdirectory( adm/cmake/${module} )

		if (USE_SOLUTION_FOLDERS)
			set_target_properties(${module} PROPERTIES FOLDER ${modulename} )
		endif(USE_SOLUTION_FOLDERS)
	endforeach(module ${modules})
endmacro(process_module modulename modules_std)

####################################################################################
# Process modules of each ToolKit                                                  #
####################################################################################
# Foundation
process_module( "Kernel" "TKernel;TKMath" )

# Modeling Data
if (OCE_MODEL)
	process_module( "Modeling Data" "TKG2d;TKG3d;TKGeomBase;TKBRep" )
endif (OCE_MODEL)

# Modeling Algorithms
if (OCE_MODEL)
	process_module( "Modeling Algorithms" "TKGeomAlgo;TKTopAlgo;TKPrim;TKBO;TKHLR;TKMesh;TKShHealing;TKXMesh;TKBool;TKFillet;TKFeat;TKOffset" )
endif (OCE_MODEL)

# Visualisation
if(OCE_VISU_DEP)
	process_module( "Visualization" "" "TKService;TKV3d" )
endif(OCE_VISU_DEP)
if(OCE_VISUALISATION)
	if(OCE_WITH_VTK)
		set(oce_vtk_component TKIVtk)
	endif()
	process_module( "Visualization" "" "TKOpenGl;TKMeshVS;TKNIS;TKVoxel;${oce_vtk_component}" )
endif(OCE_VISUALISATION)

# Application framework
if(OCE_OCAF)
	process_module( "OCAF" "TKCDF;PTKernel;TKLCAF;FWOSPlugin;TKPShape;TKBinL;TKXmlL;TKPLCAF;TKTObj;TKShapeSchema;TKStdLSchema" "TKCAF;TKBin;TKXml;TKPCAF;TKBinTObj;TKXmlTObj;TKStdSchema" )
endif(OCE_OCAF)

# Data exchange
if(OCE_DATAEXCHANGE)
	process_module( "Data Exchange" "TKSTL;TKXSBase;TKSTEPBase;TKIGES;TKSTEPAttr;TKSTEP209;TKSTEP" "TKVRML;TKXCAF;TKXCAFSchema;TKXmlXCAF;TKBinXCAF;TKXDEIGES;TKXDESTEP" )
endif(OCE_DATAEXCHANGE)

# DRAWEXE application
if(OCE_DRAW)
	if(OCE_USE_TCL_TEST_FRAMEWORK)
		set(oce_tcl_component TKQADraw)
	endif()
	if(OCE_WITH_VTK)
		set(oce_vtk_component TKIVtkDraw)
	endif()
	process_module( "Draw" "" "TKDraw;TKTopTest;${oce_vtk_component};TKViewerTest;TKXSDRAW;TKDCAF;TKXDEDRAW;TKTObjDRAW;${oce_tcl_component};DRAWEXE" )
endif(OCE_DRAW)

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/adm/cmake/config/ProjectConfig.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/OCEConfig.cmake @ONLY )
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/adm/cmake/config/ProjectConfigVersion.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/OCEConfigVersion.cmake @ONLY )
install(FILES ${PROJECT_BINARY_DIR}/OCEConfig.cmake ${PROJECT_BINARY_DIR}/OCEConfigVersion.cmake
	DESTINATION ${OCE_INSTALL_CMAKE_DATA_DIR} COMPONENT Development )

install(EXPORT OCE-libraries DESTINATION ${OCE_INSTALL_CMAKE_DATA_DIR} COMPONENT Development)

############
# PostBuild Step
############
# In win32, dependent libraries are required to run tests.
# Todo this works only with the bundle, all other libraries are not copied.
if(MSVC AND OCE_TESTING AND OCE_USE_BUNDLE)

		# Try to find TCL .dll filename
		if (OCE_DRAW)
			get_filename_component(TCL_BIN_DIR ${TCL_TCLSH} PATH)
			get_filename_component(TCL_LIB_NAME_DIR ${TCL_LIBRARY} NAME_WE)
		endif()

		# Post-build target. In reality it is not a post-build step	, but it doesn't matter
		add_custom_target(PostBuild ALL ${CMAKE_COMMAND} -E echo Copying dependent files DEPENDS ALL)

		if ( CMAKE_CONFIGURATION_TYPES )
			SET(MY_CMAKE_CONFIGURATION_TYPES ${CMAKE_CONFIGURATION_TYPES})
		else()
			SET(MY_CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE})
		endif()

		# This loop copies the DLLs in each configuration binary dir.
		foreach (config ${MY_CMAKE_CONFIGURATION_TYPES})
			set(my_dir "")
			if(CMAKE_CONFIGURATION_TYPES)
				set(my_dir "${config}/")
			endif()
			add_custom_command(TARGET PostBuild POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${LIBRARY_OUTPUT_PATH}/${my_dir} VERBATIM )
			
			if (OCE_DRAW)
				add_custom_command(TARGET PostBuild POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${TCL_BIN_DIR}/${TCL_LIB_NAME_DIR}.dll ${LIBRARY_OUTPUT_PATH}/${my_dir} VERBATIM)
			endif()

		endforeach()

endif(MSVC AND OCE_TESTING AND OCE_USE_BUNDLE)

##############
# Bundle AUTOINSTALL
##############

if (OCE_AUTOINSTALL_DEPENDENT_LIBS)
	# Note : these installs are optional because in multi-configuration types these may include
	# generator expressions and the EXISTS check fails in that case.

	IF(MINGW)
		if(OCE_BUILD_SHARED_LIB)
			SET(OCE_LIB_EXTENSION "dll.a")
		else()
			SET(OCE_LIB_EXTENSION "a")
		endif()
	ELSE()
		SET(OCE_LIB_EXTENSION "lib")
	ENDIF()

	if (OCE_VISU_DEP AND OCE_REQUIRES_FREETYPE)
		get_filename_component(FREETYPE_BIN_DIR ${FREETYPE_LIBRARY} PATH)
		if (CMAKE_CONFIGURATION_OPTIONS)
          get_filename_component(FREETYPE_BIN_DIR_DBG ${FREETYPE_LIBRARY_DEBUG} PATH)
        else()
          set(FREETYPE_BIN_DIR_DBG ${FREETYPE_BIN_DIR})
        endif()
		install(FILES ${FREETYPE_BIN_DIR_DBG}/${CMAKE_SHARED_LIBRARY_PREFIX}freetyped.dll DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Debug OPTIONAL)
    	install(FILES ${FREETYPE_BIN_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}freetype.dll DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel OPTIONAL)
    	install(FILES ${FREETYPE_BIN_DIR_DBG}/${CMAKE_STATIC_LIBRARY_PREFIX}freetyped.${OCE_LIB_EXTENSION} DESTINATION ${OCE_INSTALL_LIB_DIR} CONFIGURATIONS Debug OPTIONAL)
    	install(FILES ${FREETYPE_BIN_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}freetype.${OCE_LIB_EXTENSION} DESTINATION ${OCE_INSTALL_LIB_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel OPTIONAL)
    	if(OCE_INSTALL_PDB_FILES)
	    	install(FILES ${FREETYPE_BIN_DIR_DBG}/freetyped.pdb DESTINATION ${OCE_INSTALL_LIB_DIR} CONFIGURATIONS Debug OPTIONAL)
			install(FILES ${FREETYPE_BIN_DIR}/freetype.pdb DESTINATION ${OCE_INSTALL_LIB_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel OPTIONAL)
		endif()
	endif(OCE_VISU_DEP AND OCE_REQUIRES_FREETYPE)

	if (OCE_VISU_DEP AND OCE_WITH_GL2PS)
		get_filename_component(GL2PS_BIN_DIR ${GL2PS_LIBRARY} PATH)
		if(CMAKE_CONFIGURATION_TYPES OR NMAKE)
		 	get_filename_component(GL2PS_BIN_DIR_DBG ${GL2PS_LIBRARY_DEBUG} PATH)
		endif(CMAKE_CONFIGURATION_TYPES OR NMAKE)
		install(FILES ${GL2PS_BIN_DIR_DBG}/${CMAKE_SHARED_LIBRARY_PREFIX}gl2psd.dll DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Debug OPTIONAL)
    	install(FILES ${GL2PS_BIN_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}gl2ps.dll DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel OPTIONAL)
    	install(FILES ${GL2PS_BIN_DIR_DBG}/${CMAKE_STATIC_LIBRARY_PREFIX}gl2psd.${OCE_LIB_EXTENSION} DESTINATION ${OCE_INSTALL_LIB_DIR} CONFIGURATIONS Debug OPTIONAL)
    	install(FILES ${GL2PS_BIN_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gl2ps.${OCE_LIB_EXTENSION} DESTINATION ${OCE_INSTALL_LIB_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel OPTIONAL)
    	if(OCE_INSTALL_PDB_FILES)
	    	install(FILES ${GL2PS_BIN_DIR_DBG}/gl2psd.pdb DESTINATION ${OCE_INSTALL_LIB_DIR} CONFIGURATIONS Debug OPTIONAL)
			install(FILES ${GL2PS_BIN_DIR}/gl2ps.pdb DESTINATION ${OCE_INSTALL_LIB_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel OPTIONAL)
		endif()
	endif(OCE_VISU_DEP AND OCE_WITH_GL2PS)

	if (OCE_VISU_DEP AND OCE_WITH_FREEIMAGE)
		get_filename_component(FREEIMAGE_BIN_DIR ${FREEIMAGE_LIBRARY} PATH)
		get_filename_component(FREEIMAGEPLUS_BIN_DIR ${FREEIMAGE_LIBRARY} PATH)
		if(CMAKE_CONFIGURATION_TYPES OR NMAKE)
			get_filename_component(FREEIMAGE_BIN_DIR_DBG ${FREEIMAGE_LIBRARY_DEBUG} PATH)
			get_filename_component(FREEIMAGEPLUS_BIN_DIR_DBG ${FREEIMAGE_LIBRARY_DEBUG} PATH)
			install(FILES ${FREEIMAGE_BIN_DIR_DBG}/${CMAKE_SHARED_LIBRARY_PREFIX}freeimaged.dll DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Debug OPTIONAL)
			install(FILES ${FREEIMAGEPLUS_BIN_DIR_DBG}/${CMAKE_SHARED_LIBRARY_PREFIX}freeimageplusd.dll DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Debug OPTIONAL)
			install(FILES ${FREEIMAGEPLUS_BIN_DIR_DBG}/${CMAKE_STATIC_LIBRARY_PREFIX}freeimageplusd.${OCE_LIB_EXTENSION} DESTINATION ${OCE_INSTALL_LIB_DIR} CONFIGURATIONS Debug OPTIONAL)
		endif(CMAKE_CONFIGURATION_TYPES OR NMAKE)
		install(FILES ${FREEIMAGE_BIN_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}freeimage.dll DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel OPTIONAL)
    	install(FILES ${FREEIMAGE_BIN_DIR_DBG}/${CMAKE_STATIC_LIBRARY_PREFIX}freeimaged.${OCE_LIB_EXTENSION} DESTINATION ${OCE_INSTALL_LIB_DIR} CONFIGURATIONS Debug OPTIONAL)
    	install(FILES ${FREEIMAGE_BIN_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}freeimage.${OCE_LIB_EXTENSION} DESTINATION ${OCE_INSTALL_LIB_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel OPTIONAL)
		install(FILES ${FREEIMAGEPLUS_BIN_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}freeimageplus.dll DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel OPTIONAL)
    	install(FILES ${FREEIMAGEPLUS_BIN_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}freeimageplus.${OCE_LIB_EXTENSION} DESTINATION ${OCE_INSTALL_LIB_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel OPTIONAL)

    	if(OCE_INSTALL_PDB_FILES)
	    	install(FILES ${FREEIMAGE_BIN_DIR_DBG}/freeimaged.pdb DESTINATION ${OCE_INSTALL_LIB_DIR} CONFIGURATIONS Debug OPTIONAL)
			install(FILES ${FREEIMAGE_BIN_DIR}/freeimage.pdb DESTINATION ${OCE_INSTALL_LIB_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel OPTIONAL)
			install(FILES ${FREEIMAGEPLUS_BIN_DIR_DBG}/freeimageplusd.pdb DESTINATION ${OCE_INSTALL_LIB_DIR} CONFIGURATIONS Debug OPTIONAL)
			install(FILES ${FREEIMAGEPLUS_BIN_DIR}/freeimageplus.pdb DESTINATION ${OCE_INSTALL_LIB_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel OPTIONAL)
		endif()
	endif(OCE_VISU_DEP AND OCE_WITH_FREEIMAGE)

	# Install TCL
	if (OCE_DRAW)
		get_filename_component(TCL_BIN_DIR ${TCL_TCLSH} PATH)
		get_filename_component(TCL_LIB_NAME_DIR ${TCL_LIBRARY} NAME_WE)
		install(FILES ${TCL_BIN_DIR}/${TCL_LIB_NAME_DIR}.dll DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Debug OPTIONAL)
		install(FILES ${TCL_BIN_DIR}/${TCL_LIB_NAME_DIR}.dll DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel OPTIONAL)
	endif(OCE_DRAW)

	# Install TBB libraries
	if(OCE_MULTITHREAD_LIBRARY STREQUAL "TBB")
		IF(NOT DEFINED TBB_BIN_DIR)
			get_filename_component(TBB_BIN_DIR ${TBB_LIBRARY} PATH)
			if(CMAKE_CONFIGURATION_TYPES OR NMAKE)
				get_filename_component(TBB_BIN_DIR_DBG ${TBB_LIBRARY_DEBUG} PATH)
			endif(CMAKE_CONFIGURATION_TYPES OR NMAKE)
		ENDIF()
		if(NOT OCE_BUILD_SHARED_LIB)
			set(tbb_prefix "_static")
		endif()
		install(FILES "${TBB_BIN_DIR}/tbb${tbb_prefix}.dll" DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel OPTIONAL)
		install(FILES "${TBB_BIN_DIR}/tbb${tbb_prefix}.${OCE_LIB_EXTENSION}" DESTINATION ${OCE_INSTALL_LIB_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel OPTIONAL)
		if(CMAKE_CONFIGURATION_TYPES OR NMAKE)
			install(FILES "${TBB_BIN_DIR_DBG}/tbb_debug${tbb_prefix}.dll" DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Debug OPTIONAL)
			install(FILES "${TBB_BIN_DIR_DBG}/tbb_debug${tbb_prefix}.${OCE_LIB_EXTENSION}" DESTINATION ${OCE_INSTALL_LIB_DIR} CONFIGURATIONS Debug OPTIONAL)
		endif(CMAKE_CONFIGURATION_TYPES OR NMAKE)
		if(OCE_INSTALL_PDB_FILES)
			install(FILES "${TBB_BIN_DIR_DBG}/tbb_debug${tbb_prefix}.pdb" DESTINATION ${OCE_INSTALL_LIB_DIR} CONFIGURATIONS Debug OPTIONAL)
			install(FILES "${TBB_BIN_DIR}/tbb${tbb_prefix}.pdb" DESTINATION ${OCE_INSTALL_LIB_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel OPTIONAL)
		endif()
	endif(OCE_MULTITHREAD_LIBRARY STREQUAL "TBB")

	if(OCE_TBB_MALLOC_SUPPORT)
		if(NOT DEFINED TBB_BIN_DIR)
			get_filename_component(TBB_MALLOC_BIN_DIR ${TBB_MALLOC_LIBRARY} PATH)
			if(CMAKE_CONFIGURATION_TYPES OR NMAKE)
				get_filename_component(TBB_MALLOC_BIN_DIR_DBG ${TBB_MALLOC_LIBRARY_DEBUG} PATH)
			endif(CMAKE_CONFIGURATION_TYPES OR NMAKE)
		else()
			SET(TBB_MALLOC_BIN_DIR ${TBB_BIN_DIR})
			if(CMAKE_CONFIGURATION_TYPES OR NMAKE)
				SET(TBB_MALLOC_BIN_DIR_DBG ${TBB_BIN_DIR})
			endif(CMAKE_CONFIGURATION_TYPES OR NMAKE)
		endif()

		install(FILES "${TBB_MALLOC_BIN_DIR}/tbbmalloc.dll" DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel OPTIONAL)
		install(FILES "${TBB_MALLOC_BIN_DIR}/tbbmalloc.${OCE_LIB_EXTENSION}" DESTINATION ${OCE_INSTALL_LIB_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel OPTIONAL)
		if(CMAKE_CONFIGURATION_TYPES OR NMAKE)
			install(FILES "${TBB_MALLOC_BIN_DIR_DBG}/tbbmalloc_debug.dll" DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Debug OPTIONAL)
			install(FILES "${TBB_MALLOC_BIN_DIR_DBG}/tbbmalloc_debug.${OCE_LIB_EXTENSION}" DESTINATION ${OCE_INSTALL_LIB_DIR} CONFIGURATIONS Debug OPTIONAL)
		endif(CMAKE_CONFIGURATION_TYPES OR NMAKE)
		if(OCE_INSTALL_PDB_FILES)
			if(CMAKE_CONFIGURATION_TYPES OR NMAKE)
				install(FILES "${TBB_MALLOC_BIN_DIR_DBG}/tbbmalloc_debug.pdb" DESTINATION ${OCE_INSTALL_LIB_DIR} CONFIGURATIONS Debug OPTIONAL)
			endif(CMAKE_CONFIGURATION_TYPES OR NMAKE)
			install(FILES "${TBB_MALLOC_BIN_DIR}/tbbmalloc.pdb" DESTINATION ${OCE_INSTALL_LIB_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel OPTIONAL)
		endif()
	endif(OCE_TBB_MALLOC_SUPPORT)
endif(OCE_AUTOINSTALL_DEPENDENT_LIBS)


###############
# UnitTesting #
###############
if(OCE_TESTING)
	include(CTest)
	enable_testing()
	subdirs(test)
endif(OCE_TESTING)
if(OCE_COVERAGE)
	set(OCE_TESTING ON CACHE BOOL "Testing enabled by coverage option" FORCE)
	# build static libs, better coverage report
	set( OCE_BUILD_SHARED_LIB OFF CACHE BOOL "Build static libs" FORCE )
	set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -fprofile-arcs -ftest-coverage" CACHE STRING "Extra compile flags required by code coverage" FORCE)
	set(CMAKE_C_FLAGS_DEBUG "-O0 -g -fprofile-arcs -ftest-coverage" CACHE STRING "Extra compile flags required by code coverage" FORCE)
	set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "-fprofile-arcs -ftest-coverage" CACHE STRING "Extra linker flags required by code coverage" FORCE)
endif(OCE_COVERAGE)

if(OCE_USE_TCL_TEST_FRAMEWORK)
	if(WIN32)
		set(OCE_TEST_PATH_VAR_NAME "PATH")
		set(OCE_TEST_PATH_VAR_SEPARATOR ";")
	elseif(APPLE)
		set(OCE_TEST_PATH_VAR_NAME "DYLD_LIBRARY_PATH")
		set(OCE_TEST_PATH_VAR_SEPARATOR ":")
	else()
		set(OCE_TEST_PATH_VAR_NAME "LD_LIBRARY_PATH")
		set(OCE_TEST_PATH_VAR_SEPARATOR ":")
	endif()
	set (OCE_TEST_PATH_CURRENT_VALUE $ENV{${OCE_TEST_PATH_VAR_NAME}})
	if (OCE_TEST_PATH_CURRENT_VALUE)
		set(OCE_TEST_PATH_CURRENT_VALUE "${OCE_TEST_PATH_VAR_SEPARATOR}${OCE_TEST_PATH_CURRENT_VALUE}")
	endif ()
	set(OCE_TEST_PATH "${LIBRARY_OUTPUT_PATH}${OCE_TEST_PATH_CURRENT_VALUE}")
	get_target_property(DRAWEXE_COMMAND DRAWEXE LOCATION)
	configure_file(
	    "${CMAKE_CURRENT_SOURCE_DIR}/adm/cmake/config/DrawLaunchTests.cmake.in"
	    "${CMAKE_CURRENT_BINARY_DIR}/DrawLaunchTests.cmake" IMMEDIATE @ONLY)
	file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/DrawLaunchTests.draw)
	if(ALL STREQUAL ${OCE_TCL_TEST_GROUP})
		file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/DrawLaunchTests.draw "testgrid\n")
	else()
		file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/DrawLaunchTests.draw "testgrid ${OCE_TCL_TEST_GROUP}\n")
	endif()
	file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/DrawLaunchTests.draw "return")
	if(OCE_WITH_VTK)
		set(oce_vtk_components TKIVtk TKIVtkDraw)
	endif()
	add_custom_command(OUTPUT OcctTests COMMAND "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/DrawLaunchTests.cmake"
		DEPENDS TKernel TKMath TKG2d TKG3d TKGeomBase TKBRep TKGeomAlgo TKTopAlgo TKPrim TKBO TKHLR TKMesh TKShHealing TKXMesh TKBool TKFillet TKFeat TKOffset TKService TKV3d TKOpenGl TKMeshVS TKNIS TKVoxel TKCDF PTKernel TKLCAF FWOSPlugin TKPShape TKBinL TKXmlL TKPLCAF TKTObj TKShapeSchema TKStdLSchema TKCAF TKBin TKXml TKPCAF TKBinTObj TKXmlTObj TKStdSchema TKSTL TKXSBase TKSTEPBase TKIGES TKSTEPAttr TKSTEP209 TKSTEP TKVRML TKXCAF TKXCAFSchema TKXmlXCAF TKBinXCAF TKXDEIGES TKXDESTEP TKDraw TKTopTest ${oce_vtk_components} TKViewerTest TKXSDRAW TKDCAF TKXDEDRAW TKTObjDRAW TKQADraw DRAWEXE
		COMMENT "Running OCCT test suite...")
	add_custom_target(occt-tests DEPENDS OcctTests)
endif(OCE_USE_TCL_TEST_FRAMEWORK)


###############################################################################
# OCE Packaging                                                               #
# $make package                                                               #
###############################################################################

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "OpenCASCADE Community Edition")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE_LGPL_21.txt")
set(CPACK_SET_DESTDIR "ON")

set(CPACK_PACKAGE_VERSION_MAJOR ${OCE_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${OCE_VERSION_MINOR})
# bugfix release: add ${OCE_VERSION_PATCH} to the package version
# (uncomment following line)
#set(CPACK_PACKAGE_VERSION_PATCH ${OCE_VERSION_PATCH})
set(CPACK_PACKAGE_NAME OCE )

set(CPACK_PACKAGE_CONTACT "OCE Developers <oce-dev@googlegroups.com>")

###############################################################################
# Debian-specific CPack variables. Intended for quick-n-dirty dev packages,   #
# not to replace the official (and superior) debian tools.                    #
# to enable, run cmake with -DCPACK_GENERATOR="DEB", or uncomment             #
#set(CPACK_GENERATOR "DEB")                                                   #
###############################################################################
if( CPACK_GENERATOR MATCHES ".*DEB.*" )
	if( ${CMAKE_VERSION} STREQUAL "2.8.2" )
		# bug http://vtk.org/Bug/view.php?id=11020
		message( WARNING "CMake/CPack version 2.8.2 will not create working .deb packages!")
	endif()
	set(CPACK_DEBIAN_PACKAGE_SECTION "science")
	# debian source packages aren't yet supported by cmake, but the following list will help anyone who is trying to figure out what to apt-get install before building.
	set(CPACK_DEBIAN_PACKAGE_BUILDS_DEPENDS "debhelper (>= 6.0.7~), quilt, cmake (>= 2.8), libtool,
		libx11-dev, libxext-dev, tcl8.5-dev, tk8.5-dev,
		libgl1-mesa-dev | libgl-dev, libglu1-mesa-dev | libglu-dev,
		libgl2ps-dev")
	set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.3), libfreetype6 (>= 2.2.1),
		libgcc1 (>= 1:4.1.1), libgl1-mesa-glx, libgl2ps0, libglu1-mesa,
		libgomp1 (>= 4.2.1), libstdc++6 (>= 4.4.0), libx11-6, libxext6,
		libxt6, tcl8.5 (>= 8.5.0), tk8.5 (>= 8.5.0)")
	set(CPACK_DEBIAN_PACKAGE_SUGGESTS "opencascade-doc")
	set(CPACK_DEBIAN_PACKAGE_PROVIDES "libopencascade-foundation-6.5.0, libopencascade-modeling-6.5.0,
		libopencascade-visualization-6.5.0, libopencascade-ocaf-lite-6.5.0,
		libopencascade-ocaf-6.5.0, opencascade-draw")
	if( BIT EQUAL 64 )
		set( CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64" )
	else()
		set( CPACK_DEBIAN_PACKAGE_ARCHITECTURE "i386" )
	endif()
	string( TOLOWER "${CPACK_PACKAGE_NAME}-${OCE_VERSION}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}" CPACK_PACKAGE_FILE_NAME )
endif()

###############################################################################
# RPM-specific CPack variables.                                               #
# to enable, run cmake with -DCPACK_GENERATOR="RPM", or uncomment             #
#set(CPACK_GENERATOR "RPM")                                                   #
# For RPM, package names and versions are guesses and may need changed.       #
#                                                                             #
# As of cmake 2.8.4, RPM requires use of a variable that is also used for     #
# DEB,so simultaneously building multiple package types (i.e.                 #
# -DCPACK_GENERATOR="DEB;RPM") doesn't work well. The RPM won't end up in the #
# correct directory, and packages specified after RPM won't be built.         #
###############################################################################
if( CPACK_GENERATOR MATCHES ".*RPM.*" )
	set( CPACK_RPM_PACKAGE_REQUIRES "libc6 >= 2.3, libfreetype6 >= 2.2.1, libgcc1 >= 4.1.1, libgl1-mesa-glx, libgl2ps0, libglu1-mesa, libgomp1 >= 4.2.1, libstdc++6 >= 4.4.0, libx11-6, libxext6, libxt6, tcl8.5 >= 8.5.0, tk8.5 >= 8.5.0")
	set( CPACK_RPM_PACKAGE_PROVIDES "libopencascade-foundation-6.5.0, libopencascade-modeling-6.5.0, libopencascade-visualization-6.5.0, libopencascade-ocaf-lite-6.5.0, libopencascade-ocaf-6.5.0, opencascade-draw" )
	set( CPACK_PACKAGE_RELOCATABLE "FALSE" )
	if( BIT EQUAL 64 )
		set( CPACK_RPM_PACKAGE_ARCHITECTURE "x86_64" )
	else()
		set( CPACK_RPM_PACKAGE_ARCHITECTURE "i586" )
	endif()
	#CPackRPM ignores CPACK_RPM_FILE_NAME. Must set two other vars instead, and they interfere
	string( TOLOWER "${CPACK_PACKAGE_NAME}-${OCE_VERSION}_${CPACK_RPM_PACKAGE_ARCHITECTURE}.rpm" CPACK_OUTPUT_FILE_NAME )
	if( NOT CPACK_GENERATOR STREQUAL "RPM" )
		message( WARNING "Generating an RPM with other package type(s). Due to a bug in CPackRPM, the package will not get copied to the current directory. It will be found in _CPack_Packages/Linux/RPM, and other packages may fail to build." )
	else()
		#this variable is used by other packagers, don't set it unless RPM is built by itself.
		set( CPACK_PACKAGE_FILE_NAME ${CPACK_OUTPUT_FILE_NAME} )
	endif()
endif()

include(CPack)

########################################################################################
# Uninstall code                                                                       #
# From http://www.cmake.org/Wiki/CMake_FAQ#Can_I_do_.22make_uninstall.22_with_CMake.3F #
# ######################################################################################
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/adm/cmake/config/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

# Final bundle step for dependencies
if(OCE_USE_BUNDLE)
	include(oce-win-bundle/depends.cmake)
endif()
