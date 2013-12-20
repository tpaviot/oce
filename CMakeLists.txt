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
set(OCE_VERSION_MINOR 14)
# OCE_VERSION_PATCH is used for bugfixes releases only
# (uncomment following line)
#set(OCE_VERSION_PATCH 0)
#  Empty for official releases, set to -dev, -rc1, etc for development releases
set(OCE_VERSION_DEVEL -dev)

# bugfix release: add ${OCE_VERSION_PATCH} to OCE_VERSION
set(OCE_VERSION ${OCE_VERSION_MAJOR}.${OCE_VERSION_MINOR}${OCE_VERSION_DEVEL})

set(OCE_ABI_SOVERSION 7)
set(OCE_ABI_VERSION ${OCE_ABI_SOVERSION}.0.0)

# Set the minimum version of cmake required to 2.6
cmake_minimum_required( VERSION 2.6 )

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
	if( NOT DEFINED OCE_BUILD_TYPE )
    # If CMAKE_BUILD_TYPE is set, initialize OCE_BUILD_TYPE to that.
    # Otherwise, default to a Release build.
    if( CMAKE_BUILD_TYPE )
      set( OCE_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE STRING "Set from CMAKE_BUILD_TYPE" )
    else()
		  set( OCE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Release Debug RelWithDebInfo MinSizeRel None" )
	    set( CMAKE_BUILD_TYPE ${OCE_BUILD_TYPE} CACHE INTERNAL "Build type, immutable" FORCE )
    endif(CMAKE_BUILD_TYPE)
	endif( NOT DEFINED OCE_BUILD_TYPE )
	#  The "set_property(CACHE" capability first appeared in CMake version 2.8.0
	#  We test against > 2.8 though, otherwise test is much less readable
	if (${CMAKE_VERSION} VERSION_GREATER 2.8)
		set_property(CACHE OCE_BUILD_TYPE PROPERTY STRINGS "Release" "Debug" "RelWithDebInfo" "MinSizeRel" "None")
	endif (${CMAKE_VERSION} VERSION_GREATER 2.8)
endif(NOT CMAKE_CONFIGURATION_TYPES)

if(CMAKE_BUILD_TOOL STREQUAL "nmake")
	set(NMAKE TRUE)
endif(CMAKE_BUILD_TOOL STREQUAL "nmake")

if(MSVC)
	option_with_default( OCE_INSTALL_PDB_FILES "Install PDB files (debug informations)" ON )
endif(MSVC)

############################
# Library name definitions #
############################

if(MSVC)
	set( CMAKE_LIBRARY_PREFIX "" )
	set( CMAKE_LIBRARY_DEBUG_POSTFIX "d" )
else(MSVC)
	set( CMAKE_LIBRARY_PREFIX "lib" )
	set( CMAKE_LIBRARY_DEBUG_POSTFIX "" )
endif(MSVC)

if(APPLE)
	if(OCE_NO_LIBRARY_VERSION)
		set( CMAKE_LIBRARY_EXTENSION ${CMAKE_SHARED_LIBRARY_SUFFIX} )
	else(OCE_NO_LIBRARY_VERSION)
		set( CMAKE_LIBRARY_EXTENSION ".${OCE_ABI_SOVERSION}${CMAKE_SHARED_LIBRARY_SUFFIX}" )
	endif(OCE_NO_LIBRARY_VERSION)
elseif(WIN32)
	# Don't encode library versions on Windows systems
	set( CMAKE_LIBRARY_EXTENSION ${CMAKE_SHARED_LIBRARY_SUFFIX} )
else()
	if(OCE_NO_LIBRARY_VERSION)
		set( CMAKE_LIBRARY_EXTENSION ${CMAKE_SHARED_LIBRARY_SUFFIX} )
	else(OCE_NO_LIBRARY_VERSION)
		set( CMAKE_LIBRARY_EXTENSION "${CMAKE_SHARED_LIBRARY_SUFFIX}.${OCE_ABI_SOVERSION}" )
	endif(OCE_NO_LIBRARY_VERSION)
endif()

if(MSVC OR MINGW)
	option_with_default( OCE_USE_BUNDLE "Use OCE Windows Bundle that has been built and installed" OFF )
	option_with_default( OCE_USE_BUNDLE_SOURCE "Use OCE Windows Bundle source and incorporate into current project" OFF )
endif(MSVC OR MINGW)

if(BORLAND)
	option_with_default( OCE_INSTALL_TDS_FILES "Instal TDS files (debug informations)" ON )
endif(BORLAND)

if(OCE_USE_BUNDLE OR OCE_USE_BUNDLE_SOURCE)
	option_with_default( OCE_BUNDLE_AUTOINSTALL "Autoinstall bundle DLLs" ON )
	mark_as_advanced(OCE_BUNDLE_AUTOINSTALL)
endif(OCE_USE_BUNDLE OR OCE_USE_BUNDLE_SOURCE)

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
option_with_default( OCE_DISABLE_TKSERVICE_FONT "Disable TKService Font (only without Visualization)" OFF )
mark_as_advanced(OCE_DISABLE_TKSERVICE_FONT)
option_with_default( OCE_EXTRA_WARNINGS "Enable Maximum Warnings Level" OFF )
mark_as_advanced(OCE_EXTRA_WARNINGS)
if( NOT "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.8 )
	option_with_default( OCE_TESTING "Enable unittesting framework" OFF )
	mark_as_advanced(OCE_TESTING)
endif( NOT "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.8 )
option_with_default( OCE_ADD_HEADERS "Add headers to project files" OFF )
mark_as_advanced(OCE_ADD_HEADERS)
option_with_default( OCE_DISABLE_BSPLINE_MESHER "Disable BSpline Mesher" OFF )
mark_as_advanced(OCE_DISABLE_BSPLINE_MESHER)
if(APPLE)
	option_with_default( OCE_OSX_USE_COCOA "Use native OSX Cocoa backend" ON )
endif(APPLE)
if (NOT WIN32)
	option_with_default( OCE_RPATH_FILTER_SYSTEM_PATHS "Filter out system paths from RPATH" ON )
	mark_as_advanced(OCE_RPATH_FILTER_SYSTEM_PATHS)
endif (NOT WIN32)

#
# By default, OSX uses X11 OpenGl implementation
#
if (APPLE)
	if (NOT OCE_OSX_USE_COCOA)
		set(MACOSX_USE_GLX TRUE)
	endif(NOT OCE_OSX_USE_COCOA)
endif(APPLE)
# The default for the DEB define is ON for all the platforms , in debug mode.
# In MSVC it is not desirable to have it ON by default, since users must
# compile/use the OCE debug libraries to build it's own programs in DEBUG mode.
# DEB should be enabled by developers only, in this case
if ((MSVC OR BORLAND) AND CMAKE_CONFIGURATION_TYPES)
	set (DEB_DEFAULT "OFF")
else ()
	set (DEB_DEFAULT "ON")
endif ((MSVC OR BORLAND) AND CMAKE_CONFIGURATION_TYPES)

option_with_default( OCE_ENABLE_DEB_FLAG "Enables DEB define in debug configuration" ${DEB_DEFAULT} )
mark_as_advanced(OCE_ENABLE_DEB_FLAG)

if(NOT MSVC)
	option_with_default( OCE_COVERAGE "Build with coverage testing" OFF )
	mark_as_advanced(OCE_COVERAGE)
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
endif(MSVC_IDE)

set_directory_properties(PROPERTIES COMPILE_DEFINITIONS_RELEASE NDEBUG)
set_directory_properties(PROPERTIES COMPILE_DEFINITIONS_MINSIZEREL NDEBUG)
set_directory_properties(PROPERTIES COMPILE_DEFINITIONS_RELWITHDEBINFO  NDEBUG)

if(OCE_ENABLE_DEB_FLAG)
	set_directory_properties(PROPERTIES COMPILE_DEFINITIONS_DEBUG "DEB=1;_DEBUG")
else ()
	set_directory_properties(PROPERTIES COMPILE_DEFINITIONS_DEBUG "_DEBUG")
endif (OCE_ENABLE_DEB_FLAG)

if(OCE_MULTITHREAD_LIBRARY STREQUAL "NONE")
    add_definitions(-DIGNORE_NO_ATOMICS)
endif (OCE_MULTITHREAD_LIBRARY STREQUAL "NONE")

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

if (OCE_USE_BUNDLE OR OCE_USE_BUNDLE_SOURCE)
	find_path(OCE_BUNDLE_ROOT_PATH oce-bundle-root.empty "Path for the OCE-win-bundle")
endif(OCE_USE_BUNDLE OR OCE_USE_BUNDLE_SOURCE)

if(OCE_VISU_DEP AND NOT OCE_DISABLE_TKSERVICE_FONT)
	set(OCE_REQUIRES_FREETYPE TRUE)
endif()

if(OCE_VISU_DEP)
	## TKService requires OpenGL on Unix, see src/Xw/Xw_Window.cxx
	if (NOT (WIN32 OR (APPLE AND OCE_OSX_USE_COCOA)))
		find_package(OpenGL REQUIRED)
	endif (NOT (WIN32 OR (APPLE AND OCE_OSX_USE_COCOA)))
endif(OCE_VISU_DEP)

if(OCE_REQUIRES_FREETYPE)
	## TKService requires FreeType
	if(NOT OCE_USE_BUNDLE AND NOT OCE_USE_BUNDLE_SOURCE)
		find_package(Freetype REQUIRED)
	else (NOT OCE_USE_BUNDLE AND NOT OCE_USE_BUNDLE_SOURCE)
		find_library(FREETYPE_LIBRARY freetype)
	endif(NOT OCE_USE_BUNDLE AND NOT OCE_USE_BUNDLE_SOURCE)

	if(CMAKE_CONFIGURATION_TYPES OR NMAKE)
		find_library(FREETYPE_LIBRARY_DEBUG freetyped "Location of freetype debug library")
	endif(CMAKE_CONFIGURATION_TYPES OR NMAKE)
endif(OCE_REQUIRES_FREETYPE)

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
	set(INSTALL_RESOURCE_FILES ${INSTALL_RESOURCE_FILES} ${TEXTURES_RGB_FILES})
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
		src/XSTEPResource/STEP )
endif(OCE_DATAEXCHANGE)

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
		src/DrawResources/DRAW.doc
		src/DrawResources/DRAW.info
		src/DrawResources/DrawDefault
		src/DrawResources/DrawPlugin
		src/DrawResources/idoc
		src/DrawResources/lamp.ico
		src/DrawResources/mkdoc
		src/DrawResources/tdoc )
endif(OCE_DRAW)

if (OCE_USE_BUNDLE AND OCE_BUNDLE_ROOT_PATH)
	message("Using previously built and installed OCE Bundle")
	if (OCE_VISUALISATION)
		set(FREETYPE_INCLUDE_DIR_freetype2 ${OCE_BUNDLE_ROOT_PATH}/include/freetype CACHE PATH "" FORCE)
		set(FREETYPE_INCLUDE_DIR_ft2build ${OCE_BUNDLE_ROOT_PATH}/include/freetype CACHE PATH "" FORCE)
		set(FREETYPE_INCLUDE_DIRS ${FREETYPE_INCLUDE_DIR_freetype2} ${FREETYPE_INCLUDE_DIR_ft2build})
		set(FREETYPE_LIBRARY ${OCE_BUNDLE_ROOT_PATH}/Win${BIT}/lib/freetype.lib CACHE FILEPATH "" FORCE)
		set(FREETYPE_LIBRARIES ${OCE_BUNDLE_ROOT_PATH}/Win${BIT}/lib/freetype.lib CACHE FILEPATH "" FORCE)
		set(FREETYPE_LIBRARY_DEBUG ${OCE_BUNDLE_ROOT_PATH}/Win${BIT}/lib/freetyped.lib CACHE FILEPATH "" FORCE)

		if(OCE_WITH_GL2PS)
			set(GL2PS_LIBRARY ${OCE_BUNDLE_ROOT_PATH}/Win${BIT}/lib/gl2ps.lib CACHE FILEPATH "" FORCE)
			set(GL2PS_LIBRARY_DEBUG ${OCE_BUNDLE_ROOT_PATH}/Win${BIT}/lib/gl2psd.lib CACHE FILEPATH "" FORCE)
			set(GL2PS_INCLUDE_DIR ${OCE_BUNDLE_ROOT_PATH}/include/gl2ps CACHE PATH "" FORCE)
		endif(OCE_WITH_GL2PS)

		if(OCE_WITH_FREEIMAGE)
			set(FREEIMAGE_LIBRARY ${OCE_BUNDLE_ROOT_PATH}/Win${BIT}/lib/FreeImage.lib CACHE FILEPATH "" FORCE)
			set(FREEIMAGE_LIBRARY_DEBUG ${OCE_BUNDLE_ROOT_PATH}/Win${BIT}/lib/FreeImaged.lib CACHE FILEPATH "" FORCE)
			set(FREEIMAGEPLUS_LIBRARY ${OCE_BUNDLE_ROOT_PATH}/Win${BIT}/lib/FreeImagePlus.lib CACHE FILEPATH "" FORCE)
			set(FREEIMAGEPLUS_LIBRARY_DEBUG ${OCE_BUNDLE_ROOT_PATH}/Win${BIT}/lib/FreeImagePlusd.lib CACHE FILEPATH "" FORCE)
			set(FREEIMAGE_INCLUDE_DIR ${OCE_BUNDLE_ROOT_PATH}/include/FreeImage CACHE PATH "" FORCE)
		endif(OCE_WITH_FREEIMAGE)
	endif (OCE_VISUALISATION)
endif(OCE_USE_BUNDLE AND OCE_BUNDLE_ROOT_PATH)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/build_inc
	${CMAKE_CURRENT_SOURCE_DIR}/inc)

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
include(CheckFunctionExists)
check_function_exists(finite HAVE_FINITE)
if (NOT WIN32)
	# Check headers
	# I think these should all be check cxx headers, as I think there is no c
	# compilation anywhere in OCE
	include(CheckIncludeFile)
	#include(CheckIncludeFiles)
	check_include_file(string.h HAVE_STRING_H)
	check_include_file(dlfcn.h HAVE_DLFCN_H)
	check_include_file(dl.h HAVE_DL_H)
	check_include_file(ieeefp.h HAVE_IEEEFP_H)
	check_include_file(time.h HAVE_TIME_H)
	check_include_file(sys/time.h HAVE_SYS_TIME_H)
	check_include_file(pwd.h HAVE_PWD_H)
	check_include_file(sys/statvfs.h HAVE_SYS_STATVFS_H)
	check_include_file(sys/vfs.h HAVE_SYS_VFS_H)
	check_include_file(sys/param.h HAVE_SYS_PARAM_H)
	check_include_file(osfcn.h HAVE_OSFCN_H)
	check_include_file(netdb.h HAVE_NETDB_H)
	check_include_file(sys/ioctl.h HAVE_SYS_IOCTL_H)
	check_include_file(net/if.h HAVE_NET_IF_H)
	check_include_file(sys/systeminfo.h HAVE_SYS_SYSTEMINFO_H)
	check_include_file(sys/utsname.h HAVE_SYS_UTSNAME_H)
	check_include_file(sysent.h HAVE_SYSENT_H)
	check_include_file(unistd.h HAVE_UNISTD_H)
	check_include_file(sys/unistd.h HAVE_SYS_UNISTD_H)
	check_include_file(sys/socket.h HAVE_SYS_SOCKET_H)
	check_include_file(ndir.h HAVE_NDIR_H)
	check_include_file(sys/ndir.h HAVE_SYS_NDIR_H)
	check_include_file(sys/dir.h HAVE_SYS_DIR_H)
	check_include_file(signal.h HAVE_SIGNAL_H)
	check_include_file(sys/signal.h HAVE_SYS_SIGNAL_H)
	check_include_file(sigfpe.h HAVE_SIGFPE_H)
	check_include_file(floatingpoint.h HAVE_FLOATINGPOINT_H)
	check_include_file(sys/machsig.h HAVE_SYS_MACHSIG_H)
	check_include_file(sys/siginfo.h HAVE_SYS_SIGINFO_H)
	check_include_file(malloc.h HAVE_MALLOC_H)
	check_include_file(strings.h HAVE_STRINGS_H)
	check_include_file(sys/stat.h HAVE_SYS_STAT_H)
	check_include_file(sys/sem.h HAVE_SYS_SEM_H)
	check_include_file(sys/ipc.h HAVE_SYS_IPC_H)
	check_include_file(sys/times.h HAVE_SYS_TIMES_H)
	check_include_file(dirent.h HAVE_DIRENT_H)
	include(CheckIncludeFileCXX)
	check_include_file_cxx(iomanip.h OCE_HAVE_IOMANIP_H)
	check_include_file_cxx(limits OCE_HAVE_LIMITS)
	check_include_file_cxx(climits OCE_HAVE_CLIMITS)
	check_include_file_cxx(limits.h OCE_HAVE_LIMITS_H)
	check_include_file_cxx(values.h HAVE_VALUES_H)
	check_include_file_cxx(fstream OCE_HAVE_FSTREAM)
	check_include_file_cxx(ios HAVE_IOS)
	check_include_file_cxx(iomanip OCE_HAVE_IOMANIP)
	check_include_file_cxx(iostream OCE_HAVE_IOSTREAM)
	check_include_file_cxx(fstream.h OCE_HAVE_FSTREAM_H)
	check_include_file_cxx(ios.h HAVE_IOS_H)
	check_include_file_cxx(iostream.h OCE_HAVE_IOSTREAM_H)
	check_include_file_cxx(stdlib.h HAVE_STDLIB_H)
	check_include_file_cxx(sys/types.h HAVE_SYS_TYPES_H)
	check_include_file_cxx(sys/select.h HAVE_SYS_SELECT_H)
	check_include_file_cxx(X11/extensions/readdisplay.h HAVE_X11_EXTENSIONS_READDISPLAY_H)
	check_include_file_cxx(X11/extensions/multibuf.h HAVE_X11_EXTENSIONS_MULTIBUF_H)
	check_include_file_cxx(sys/filio.h HAVE_SYS_FILIO_H)
	check_include_file_cxx(sys/mman.h HAVE_SYS_MMAN_H)
	check_include_file_cxx(libc.h HAVE_LIBC_H)
	check_include_file_cxx(mm_malloc.h HAVE_MM_MALLOC_H)
	check_include_file_cxx(atomic.h HAVE_ATOMIC_H)
	# Check library functions
	check_function_exists(alloca HAVE_ALLOCA)
	check_function_exists(memcmp HAVE_MEMCMP)
	check_function_exists(signal HAVE_SIGNAL)
	check_function_exists(statfs HAVE_STATFS)
	check_function_exists(statvfs HAVE_STATVFS)
	check_function_exists(localtime_r HAVE_LOCALTIME_R)
	check_function_exists(posix_memalign HAVE_POSIX_MEMALIGN)
	set(CMAKE_REQUIRED_LIBRARIES sunmath)
	check_function_exists(ieee_handler HAVE_SUNMATH)
	set(CMAKE_REQUIRED_LIBRARIES)
	include(CheckTypeSize)
	set(CMAKE_EXTRA_INCLUDE_FILES sys/time.h)
	check_type_size(tm TM_IN_SYS_TIME)
	set(CMAKE_EXTRA_INCLUDE_FILES)
	include (CheckCSourceCompiles)
	check_c_source_compiles("
		#include <sys/time.h>
		#include <sys/sem.h>
		int main(){union semun c;return 0;}
		"
		SEMUN_DEFINED)
	if (SEMUN_DEFINED)
		check_c_source_compiles("
			#include <sys/time.h>
			#include <sys/sem.h>
			int main(){union semun c;c.__buf = 0;return 0;}
			"
			SEMUN_BUF_DEFINED)
	endif (SEMUN_DEFINED)
	check_c_source_compiles("
		#include <sys/sem.h>
		static struct sembuf event_flag;
		int main(){int status; int *semid;status = semop(*semid,event_flag,1);return 0;}
		"
		SEMOP_NO_REFERENCE)

	check_c_source_compiles("
		#include <sys/sem.h>
		int get_semaphore(int *semid,int *event,int *value)
		{
			int status;
			status = semctl((*semid),*event,GETVAL,value);
			return 0;
		}
		int main(){ int *a,*b,*c;
		if(get_semaphore(a,b,c))
			return 0;
		return 0;}
		"
		SEMCTL_NO_REFERENCE)

	include (CheckCXXSourceCompiles)
	check_cxx_source_compiles("
		#include <ios>
		int main(){static const int input = (std::ios::in)|(std::ios::nocreate);
		static const int output = (std::ios::out);return 0;}
		"
		DEF_IOS_OK)
	check_cxx_source_compiles("
		#include <iostream>
		int main(){std::cout << std::cout.form(\"%9.3e\", 3.14159627e-4) << std::endl;return 0;}
		"
		OSTREAM_FORM_OK)
	include(TestBigEndian)
	test_big_endian(WORDS_BIGENDIAN)
	set(STDC_HEADERS TRUE) # Only for really old systems, being lazy
	set(STACK_DIRECTION 0) # Don't have a test for this, TODO?

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
			add_definitions(-DHAVE_IOS )
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
	elseif (BORLAND) # The compiler used is BORLAND
		set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/win${BIT}/bin/${CMAKE_BUILD_TYPE})
	else()
		IF (MINGW)
			message(STATUS "Found MINGW compiler: ${MINGW}")
		endif(MINGW)
		set(LIBRARY_OUTPUT_PATH win${BIT}/bin/${CMAKE_BUILD_TYPE})
	endif()
	set(EXECUTABLE_OUTPUT_PATH ${LIBRARY_OUTPUT_PATH})
else(WIN32)
	set(LIBRARY_OUTPUT_PATH ${PLATFORM}/${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_BUILD_TYPE}-${BIT})
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
endif(MINGW)

# DISABLE SECURE CRT WARNINGS AND OTHER MS CRT SPECIFC THINGS
if (MSVC)
	add_definitions("/D_CRT_SECURE_NO_WARNINGS")
	add_definitions("/D_CRT_NONSTDC_NO_WARNINGS")
endif(MSVC)

if(MSVC_IDE)
	if(NOT OCE_USE_MSVC_EXPRESS)
		#Use solution folders.
		set_property(GLOBAL PROPERTY USE_FOLDERS ON)
		set(USE_SOLUTION_FOLDERS TRUE)
	else( NOT OCE_USE_MSVC_EXPRESS)
		set_property(GLOBAL PROPERTY USE_FOLDERS OFF)
	endif( NOT OCE_USE_MSVC_EXPRESS)
endif(MSVC_IDE)

# Libraries are installed by default in /usr/local/lib on UNIX
# based platforms and c:/OCE-VERSION/Win[32|64]/lib on windows based
# platforms

if(WIN32)
	set(_PSUFFIX "Win${BIT}/")
else(WIN32)
	set(_PSUFFIX "")
endif(WIN32)

# If OCE_USE_BUNDLE_SOURCE, then we need to add oce-win-bundle and set it
# to build into the same destination directories as OCE. This cannot run
# until LIBRARY_OUTPUT_PATH is set above
if (OCE_USE_BUNDLE_SOURCE AND OCE_BUNDLE_ROOT_PATH)
	# Embed oce-win-bundle project into this CMake project
	message("Using OCE Bundle in same CMake project")
	add_subdirectory( ${OCE_BUNDLE_ROOT_PATH} ${CMAKE_BINARY_DIR}/oce-win-bundle )

	# The installation directory of the bundle must match the one of OCE
	set(OCE_WIN_BUNDLE_INSTALL_DIR ${OCE_INSTALL_PREFIX} CACHE PATH "" FORCE)
	
	# Look for includes in bundle source directory.
	# Put oce-win-bundle libraries and dlls in same place OCE libraries and dlls are going,
	# and set variables to point OCE to them.
	if (OCE_VISUALISATION)
		set(FREETYPE_INCLUDE_DIR_freetype2 ${OCE_BUNDLE_ROOT_PATH}/libs/freetype CACHE PATH "" FORCE)
		set(FREETYPE_INCLUDE_DIR_ft2build ${OCE_BUNDLE_ROOT_PATH}/libs/freetype/include CACHE PATH "" FORCE)
		set(FREETYPE_INCLUDE_DIRS ${FREETYPE_INCLUDE_DIR_freetype2} ${FREETYPE_INCLUDE_DIR_ft2build})
		IF(MINGW OR MSVC)
			set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OCE_INSTALL_PREFIX}/Win${BIT}/lib CACHE PATH "" FORCE)
		endif(MINGW OR MSVC)
		
		get_target_property( FREETYPE_ARCHIVE_OUTPUT_DIRECTORY freetype ARCHIVE_OUTPUT_DIRECTORY )
		
		if(MINGW)
			set(FREETYPE_LIBRARY ${FREETYPE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/libfreetype.dll.a CACHE FILEPATH "" FORCE)
			set(FREETYPE_LIBRARIES ${FREETYPE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/libfreetype.dll.a CACHE FILEPATH "" FORCE)
			set(FREETYPE_LIBRARY_DEBUG ${FREETYPE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/libfreetyped.dll.a CACHE FILEPATH "" FORCE)
		else(MINGW)
			set(FREETYPE_LIBRARY ${FREETYPE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/freetype.lib CACHE FILEPATH "" FORCE)
			set(FREETYPE_LIBRARIES ${FREETYPE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/freetype.lib CACHE FILEPATH "" FORCE)
			set(FREETYPE_LIBRARY_DEBUG ${FREETYPE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/freetyped.lib CACHE FILEPATH "" FORCE)
		endif(MINGW)

		if(OCE_WITH_GL2PS)
			get_target_property( GL2PS_ARCHIVE_OUTPUT_DIRECTORY gl2ps ARCHIVE_OUTPUT_DIRECTORY )
			
			if(MINGW)
				set(GL2PS_LIBRARY ${GL2PS_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/libgl2ps.dll.a CACHE FILEPATH "" FORCE)
				set(GL2PS_LIBRARY_DEBUG ${GL2PS_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/libgl2psd.dll.a CACHE FILEPATH "" FORCE)
			else(MINGW)
				set(GL2PS_LIBRARY ${GL2PS_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/gl2ps.lib CACHE FILEPATH "" FORCE)
				set(GL2PS_LIBRARY_DEBUG ${GL2PS_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/gl2psd.lib CACHE FILEPATH "" FORCE)
			endif(MINGW)
			
			set(GL2PS_INCLUDE_DIR ${OCE_BUNDLE_ROOT_PATH}/libs/gl2ps CACHE PATH "" FORCE)
		endif(OCE_WITH_GL2PS)

		if(OCE_WITH_FREEIMAGE)
			get_target_property( FREEIMAGE_ARCHIVE_OUTPUT_DIRECTORY FreeImage ARCHIVE_OUTPUT_DIRECTORY )

			if(MINGW)
				set(FREEIMAGE_LIBRARY ${FREEIMAGE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/libFreeImage.dll.a CACHE FILEPATH "" FORCE)
				set(FREEIMAGE_LIBRARY_DEBUG ${FREEIMAGE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/libFreeImaged.dll.a CACHE FILEPATH "" FORCE)
			else(MINGW)
				set(FREEIMAGE_LIBRARY ${FREEIMAGE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/FreeImage.lib CACHE FILEPATH "" FORCE)
				set(FREEIMAGE_LIBRARY_DEBUG ${FREEIMAGE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/FreeImaged.lib CACHE FILEPATH "" FORCE)
			endif(MINGW)

			get_target_property( FREEIMAGEPLUS_ARCHIVE_OUTPUT_DIRECTORY FreeImage ARCHIVE_OUTPUT_DIRECTORY )

			if(MINGW)
				set(FREEIMAGEPLUS_LIBRARY ${FREEIMAGEPLUS_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/libFreeImagePlus.dll.a CACHE FILEPATH "" FORCE)
				set(FREEIMAGEPLUS_LIBRARY_DEBUG ${FREEIMAGEPLUS_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/libFreeImagePlusd.dll.a CACHE FILEPATH "" FORCE)
			else(MINGW)
				set(FREEIMAGEPLUS_LIBRARY ${FREEIMAGEPLUS_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/FreeImagePlus.lib CACHE FILEPATH "" FORCE)
				set(FREEIMAGEPLUS_LIBRARY_DEBUG ${FREEIMAGEPLUS_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/FreeImagePlusd.lib CACHE FILEPATH "" FORCE)
			endif(MINGW)

			set(FREEIMAGE_INCLUDE_DIR ${OCE_BUNDLE_ROOT_PATH}/libs/FreeImage/Source ${OCE_BUNDLE_ROOT_PATH}/libs/FreeImage/Wrapper/FreeImagePlus CACHE PATH "" FORCE)
		endif(OCE_WITH_FREEIMAGE)
	endif (OCE_VISUALISATION)
endif(OCE_USE_BUNDLE_SOURCE AND OCE_BUNDLE_ROOT_PATH)

# Binaries
if(NOT DEFINED OCE_INSTALL_BIN_DIR)
	set(OCE_INSTALL_BIN_DIR ${_PSUFFIX}bin)
endif(NOT DEFINED OCE_INSTALL_BIN_DIR)

# Libraries
if(NOT DEFINED OCE_INSTALL_LIB_DIR)
	set(OCE_INSTALL_LIB_DIR ${_PSUFFIX}lib${LIB_SUFFIX})
endif(NOT DEFINED OCE_INSTALL_LIB_DIR)

if(MSVC)
	if(NOT DEFINED OCE_INSTALL_PACKAGE_LIB_DIR)
		set(OCE_INSTALL_PACKAGE_LIB_DIR ${OCE_INSTALL_LIB_DIR})
	endif(NOT DEFINED OCE_INSTALL_PACKAGE_LIB_DIR)
else(MSVC)
	if(NOT DEFINED OCE_INSTALL_PACKAGE_LIB_DIR)
		set(OCE_INSTALL_PACKAGE_LIB_DIR ${OCE_INSTALL_LIB_DIR}/oce-${OCE_VERSION})
	endif(NOT DEFINED OCE_INSTALL_PACKAGE_LIB_DIR)
endif(MSVC)

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
if (NOT MSVC)
	set(OCE_DEFAULT_CSF_GraphicShr ${OCE_INSTALL_PREFIX}/${OCE_INSTALL_LIB_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}TKOpenGl${CMAKE_LIBRARY_DEBUG_POSTFIX}${CMAKE_LIBRARY_EXTENSION})
else(NOT MSVC)
	# With Visual generator, CMake generates projects which can be built both in Debug and Release mode.
	# Therefore the MSVC library name has to be assembled in oce_build_paths.h.cmake.
	set(OCE_DEFAULT_CSF_GraphicShr ${CMAKE_SHARED_LIBRARY_PREFIX}TKOpenGl)
endif(NOT MSVC)

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
		list(APPEND OCE_LIBRARIES ${module})
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
process_module( "Kernel" "TKernel;TKMath;TKAdvTools" )

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
	process_module( "Visualization" "" "TKOpenGl;TKMeshVS;TKNIS;TKVoxel" )
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
	if(OCE_TESTING)
	process_module( "Draw" "" "TKDraw;TKTopTest;TKViewerTest;TKXSDRAW;TKDCAF;TKXDEDRAW;TKTObjDRAW;TKQADraw;DRAWEXE" )
	else(OCE_TESTING)
	process_module( "Draw" "" "TKDraw;TKTopTest;TKViewerTest;TKXSDRAW;TKDCAF;TKXDEDRAW;TKTObjDRAW;DRAWEXE" )
	endif(OCE_TESTING)
endif(OCE_DRAW)

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/adm/cmake/config/ProjectConfig.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/OCEConfig.cmake @ONLY )
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/adm/cmake/config/ProjectConfigVersion.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/OCEConfigVersion.cmake @ONLY )
install(FILES ${PROJECT_BINARY_DIR}/OCEConfig.cmake ${PROJECT_BINARY_DIR}/OCEConfigVersion.cmake
	DESTINATION ${OCE_INSTALL_CMAKE_DATA_DIR} COMPONENT Development )

install(EXPORT OCE-libraries DESTINATION ${OCE_INSTALL_CMAKE_DATA_DIR} COMPONENT Development)

if(OCE_USE_BUNDLE_SOURCE AND OCE_BUNDLE_ROOT_PATH)
	# Add dependencies between OCE and oce-win-bundle
	add_dependencies( TKService FreeImage )
	add_dependencies( TKOpenGl freetype gl2ps )
endif(OCE_USE_BUNDLE_SOURCE AND OCE_BUNDLE_ROOT_PATH)

############
# PostBuild Step
############
# In win32, dependent libraries are required to run tests.

if(MSVC AND OCE_TESTING)

		# Try to find TCL .dll filename
		if (OCE_DRAW)
			get_filename_component(TCL_BIN_DIR ${TCL_TCLSH} PATH)
			get_filename_component(TCL_LIB_NAME_DIR ${TCL_LIBRARY} NAME_WE)
		endif()

		# Post-build target. In reality it is not a post-build step	, but it doesn't matter
		add_custom_target(PostBuild ALL ${CMAKE_COMMAND} -E echo Copying dependent files DEPENDS ALL)

		if ( CMAKE_CONFIGURATION_TYPES )

			# This loop copies the DLLs in each configuration binary dir.
			foreach (config ${CMAKE_CONFIGURATION_TYPES})
				add_custom_command(TARGET PostBuild POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${LIBRARY_OUTPUT_PATH}/${config}/ VERBATIM )

				if (OCE_DRAW)
					add_custom_command(TARGET PostBuild POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${TCL_BIN_DIR}/${TCL_LIB_NAME_DIR}.dll ${LIBRARY_OUTPUT_PATH}/${config}/ VERBATIM)
				endif()

				# With USE_BUNDLE_SOURCE, the dll's referenced below are already in the
				# correct locations.
				if(NOT OCE_USE_BUNDLE_SOURCE)
					set(TMP_SRCDIR ${OCE_BUNDLE_ROOT_PATH}/Win${BIT}/bin/)
					set(TMP_DESTDIR ${LIBRARY_OUTPUT_PATH}/${config})
					string(REGEX REPLACE "/" "\\\\" TMP_SRCDIR ${TMP_SRCDIR})
					string(REGEX REPLACE "/" "\\\\" TMP_DESTDIR ${TMP_DESTDIR})
					set (TMP_FILELIST FreeImage gl2ps freetype FreeImagePlus)

					if (${config} MATCHES "Debug")
						set(TMP_SUFFIX "d")
					else ()
						set(TMP_SUFFIX)
					endif()

					foreach (TMP_FILE ${TMP_FILELIST} )
						add_custom_command(TARGET PostBuild POST_BUILD COMMAND xcopy /Y ${TMP_SRCDIR}${TMP_FILE}${TMP_SUFFIX}.dll ${TMP_DESTDIR} VERBATIM )
					endforeach()
				endif()

				# Switch between bin and bind dirs
				if (${config} MATCHES "Debug")

					# Install TBB libraries
					if(OCE_MULTITHREAD_LIBRARY STREQUAL "TBB" AND TBB_BIN_DIR)
						add_custom_command(TARGET PostBuild POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${TBB_BIN_DIR}/tbb_debug.dll" ${LIBRARY_OUTPUT_PATH}/${config}/ VERBATIM)
					endif(OCE_MULTITHREAD_LIBRARY STREQUAL "TBB" AND TBB_BIN_DIR)

					if(OCE_TBB_MALLOC_SUPPORT AND TBB_BIN_DIR)
						add_custom_command(TARGET PostBuild POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${TBB_BIN_DIR}/tbbmalloc_debug.dll" ${LIBRARY_OUTPUT_PATH}/${config}/ VERBATIM)
					endif(OCE_TBB_MALLOC_SUPPORT AND TBB_BIN_DIR)
				else ()

					# Install TBB libraries
					if(OCE_MULTITHREAD_LIBRARY STREQUAL "TBB" AND TBB_BIN_DIR)
						add_custom_command(TARGET PostBuild POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${TBB_BIN_DIR}/tbb.dll" ${LIBRARY_OUTPUT_PATH}/${config}/ VERBATIM)
					endif(OCE_MULTITHREAD_LIBRARY STREQUAL "TBB" AND TBB_BIN_DIR)

					if(OCE_TBB_MALLOC_SUPPORT AND TBB_BIN_DIR)
						add_custom_command(TARGET PostBuild POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${TBB_BIN_DIR}/tbbmalloc.dll" ${LIBRARY_OUTPUT_PATH}/${config}/ VERBATIM)
					endif(OCE_TBB_MALLOC_SUPPORT AND TBB_BIN_DIR)
				endif()
			endforeach()
		else (CMAKE_CONFIGURATION_TYPES )
			# Nmake support : just one configuration
			add_custom_command(TARGET PostBuild POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${LIBRARY_OUTPUT_PATH}/ VERBATIM )

			if (OCE_DRAW)
				add_custom_command(TARGET PostBuild POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${TCL_BIN_DIR}/${TCL_LIB_NAME_DIR}.dll ${LIBRARY_OUTPUT_PATH}/ VERBATIM)
			endif()

			if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
				add_custom_command(TARGET PostBuild POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${OCE_BUNDLE_ROOT_PATH}/Win${BIT}/bin/ ${LIBRARY_OUTPUT_PATH} VERBATIM )

				# Install TBB libraries
				if(OCE_MULTITHREAD_LIBRARY STREQUAL "TBB" AND TBB_BIN_DIR)
					add_custom_command(TARGET PostBuild POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${TBB_BIN_DIR}/tbb_debug.dll" ${LIBRARY_OUTPUT_PATH}/${config}/ VERBATIM)
				endif(OCE_MULTITHREAD_LIBRARY STREQUAL "TBB" AND TBB_BIN_DIR)

				if(OCE_TBB_MALLOC_SUPPORT AND TBB_BIN_DIR)
					add_custom_command(TARGET PostBuild POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${TBB_BIN_DIR}/tbbmalloc_debug.dll" ${LIBRARY_OUTPUT_PATH}/${config}/ VERBATIM)
				endif(OCE_TBB_MALLOC_SUPPORT AND TBB_BIN_DIR)
			else ()
				add_custom_command(TARGET PostBuild POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${OCE_BUNDLE_ROOT_PATH}/Win${BIT}/bin/ ${LIBRARY_OUTPUT_PATH}/ VERBATIM )

				# Install TBB libraries
				if(OCE_MULTITHREAD_LIBRARY STREQUAL "TBB" AND TBB_BIN_DIR)
					add_custom_command(TARGET PostBuild POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${TBB_BIN_DIR}/tbb.dll" ${LIBRARY_OUTPUT_PATH}/${config}/ VERBATIM)
				endif(OCE_MULTITHREAD_LIBRARY STREQUAL "TBB" AND TBB_BIN_DIR)

				if(OCE_TBB_MALLOC_SUPPORT AND TBB_BIN_DIR)
					add_custom_command(TARGET PostBuild POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${TBB_BIN_DIR}/tbbmalloc.dll" ${LIBRARY_OUTPUT_PATH}/${config}/ VERBATIM)
				endif(OCE_TBB_MALLOC_SUPPORT AND TBB_BIN_DIR)
			endif()
		endif (CMAKE_CONFIGURATION_TYPES)

endif(MSVC AND OCE_TESTING)

##############
# Bundle AUTOINSTALL
##############

if (OCE_BUNDLE_AUTOINSTALL AND NOT OCE_USE_BUNDLE_SOURCE)
	if (OCE_VISUALISATION)
		install(FILES ${OCE_BUNDLE_ROOT_PATH}/Win${BIT}/bin/freetyped.dll DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Debug)
		install(FILES ${OCE_BUNDLE_ROOT_PATH}/Win${BIT}/bin/freetype.dll DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel)
	endif(OCE_VISUALISATION)

	if (OCE_VISU_DEP AND OCE_WITH_GL2PS )
		install(FILES ${OCE_BUNDLE_ROOT_PATH}/Win${BIT}/bin/gl2psd.dll DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Debug)
		install(FILES ${OCE_BUNDLE_ROOT_PATH}/Win${BIT}/bin/gl2ps.dll DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel)
	endif(OCE_VISU_DEP AND OCE_WITH_GL2PS)

	if (OCE_VISU_DEP AND OCE_WITH_FREEIMAGE)
		install(FILES ${OCE_BUNDLE_ROOT_PATH}/Win${BIT}/bin/FreeImaged.dll DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Debug)
		install(FILES ${OCE_BUNDLE_ROOT_PATH}/Win${BIT}/bin/FreeImage.dll DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel)
		install(FILES ${OCE_BUNDLE_ROOT_PATH}/Win${BIT}/bin/FreeImagePlusd.dll DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Debug)
		install(FILES ${OCE_BUNDLE_ROOT_PATH}/Win${BIT}/bin/FreeImagePlus.dll DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel)
	endif(OCE_VISU_DEP AND OCE_WITH_FREEIMAGE)

	# Install TCL
	if (OCE_DRAW)
		get_filename_component(TCL_BIN_DIR ${TCL_TCLSH} PATH)
		get_filename_component(TCL_LIB_NAME_DIR ${TCL_LIBRARY} NAME_WE)
		install(FILES ${TCL_BIN_DIR}/${TCL_LIB_NAME_DIR}.dll DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Debug )
		install(FILES ${TCL_BIN_DIR}/${TCL_LIB_NAME_DIR}.dll DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel )
	endif(OCE_DRAW)

	# Install TBB libraries
	if(OCE_MULTITHREAD_LIBRARY STREQUAL "TBB" AND TBB_BIN_DIR)
		install(FILES "${TBB_BIN_DIR}/tbb.dll" DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel)
		install(FILES "${TBB_BIN_DIR}/tbb_debug.dll" DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Debug)
	endif(OCE_MULTITHREAD_LIBRARY STREQUAL "TBB" AND TBB_BIN_DIR)

	if(OCE_TBB_MALLOC_SUPPORT AND TBB_BIN_DIR)
		install(FILES "${TBB_BIN_DIR}/tbbmalloc.dll" DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Release RelWithDebInfo MinSizeRel)
		install(FILES "${TBB_BIN_DIR}/tbbmalloc_debug.dll" DESTINATION ${OCE_INSTALL_BIN_DIR} CONFIGURATIONS Debug)
	endif(OCE_TBB_MALLOC_SUPPORT AND TBB_BIN_DIR)
endif(OCE_BUNDLE_AUTOINSTALL AND NOT OCE_USE_BUNDLE_SOURCE)


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
	set(OCE_BUILD_TYPE "Debug" CACHE STRING "Build type required by testing framework" FORCE)
endif(OCE_COVERAGE)

###############################################################################
# OCE Packaging                                                               #
# $make package                                                               #
###############################################################################

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "OpenCASCADE Community Edition")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.txt")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
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
