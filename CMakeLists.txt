# Copyright (2010) Thomas Paviot, tpaviot@gmail.com.
#
# This file is distributed under the terms of the OpenCASCADE Technology Public License 6.5, March 2011
# Complete text of this license can be read online: http://www.opencascade.org/getocc/license/
#

# REQUIREMENTS: this script needs CMake 2.6 or higher. Downloads are available at http://www.cmake.org

# How to build OpenCASCADE using CMake under Unix (Linux, Darwin etc.)?
# 1. Copy this file, as-is, to the top-level OpenCASCADE folder
# 2. Make a build directory somewhere outside the OpenCASCADE source tree
# 3. cmake "relative/path/to/OpenCASCADE"
# 4. make
# 5. make install (or sudo make install)

# How to build OpenCASCADE using CMake under Windows (Linux, Darwin etc.)?
# 1. Copy this file, as-is, to the top-level folder
# 2. Launch the cmake-gui, and select the top-level folder
# 3. You can choose whatever you want as an install directory
# 4. Click 'Configure'
# 5. Choose your generator
# 6. When configure is achived, you can change the variable with a red background
# 7. Click 'Generate'
# 8. From your IDE, open the generated makefile and run the compilation.

# VERSION 0.2
# History
# 0.1 : initial release
# 0.2 : added *.c in source files, scanning ./drv directory, 3 more ToolKits, install
# 0.3a: continuation of 0.2 filling in todos

PROJECT(OpenCASCADE)

SET(OpenCASCADE_VERSION_MAJOR 6)
SET(OpenCASCADE_VERSION_MINOR 5)
SET(OpenCASCADE_VERSION_PATCH 0)

# Set the minimum version of cmake required to 2.6
CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )

IF( "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.5 )
	MESSAGE( FATAL_ERROR "CMake >= 2.6.0 required" )
ENDIF( "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.5 )

IF( NOT DEFINED OPENCASCADE_BUILD_TYPE )
	SET( OPENCASCADE_BUILD_TYPE "Release" CACHE STRING "Build type" ) # By default set release build
ENDIF( NOT DEFINED OPENCASCADE_BUILD_TYPE )
SET( CMAKE_BUILD_TYPE ${OPENCASCADE_BUILD_TYPE} CACHE INTERNAL "Build type,
	immutable" FORCE )

IF( NOT DEFINED OPENCASCADE_BUILD_SHARED_LIB )
	SET( OPENCASCADE_BUILD_SHARED_LIB ON )
ENDIF( NOT DEFINED OPENCASCADE_BUILD_SHARED_LIB )
IF( NOT DEFINED OPENCASCADE_MODEL )
	SET( OPENCASCADE_MODEL ON )
ENDIF( NOT DEFINED OPENCASCADE_MODEL )
IF( NOT DEFINED OPENCASCADE_OCAF )
	SET( OPENCASCADE_OCAF ON )
ENDIF( NOT DEFINED OPENCASCADE_OCAF )
IF( NOT DEFINED OPENCASCADE_DATAEXCHANGE )
	SET( OPENCASCADE_DATAEXCHANGE ON )
ENDIF( NOT DEFINED OPENCASCADE_DATAEXCHANGE )
IF( NOT DEFINED OPENCASCADE_DRAW )
	SET( OPENCASCADE_DRAW OFF )
ENDIF( NOT DEFINED OPENCASCADE_DRAW )
IF( NOT DEFINED OPENCASCADE_VISUALISATION )
	SET( OPENCASCADE_VISUALISATION ON )
ENDIF( NOT DEFINED OPENCASCADE_VISUALISATION )
IF( NOT DEFINED OPENCASCADE_VISUALISATION_FULL )
	SET( OPENCASCADE_VISUALISATION_FULL ON )
ENDIF( NOT DEFINED OPENCASCADE_VISUALISATION_FULL )

OPTION( OPENCASCADE_BUILD_SHARED_LIB "Build shared OpenCASCADE libs"
	${OPENCASCADE_BUILD_SHARED_LIB} )
OPTION( OPENCASCADE_MODEL "Build model components" ${OPENCASCADE_MODEL} )
OPTION( OPENCASCADE_OCAF "Build application framework" ${OPENCASCADE_OCAF} )
OPTION( OPENCASCADE_DATAEXCHANGE "Build data exchange"
	${OPENCASCADE_DATAEXCHANGE} )
OPTION( OPENCASCADE_DRAW "Build test harness \(DRAW\)" ${OPENCASCADE_DRAW} )
OPTION( OPENCASCADE_VISUALISATION "Build visualisation component needed by other modules"
	${OPENCASCADE_VISUALISATION} )
OPTION( OPENCASCADE_VISUALISATION_FULL "Build full visualisation component"
	${OPENCASCADE_VISUALISATION_FULL} )

IF( NOT DEFINED OPENCASCADE_WITH_TBB )
	SET( OPENCASCADE_WITH_TBB OFF )
ENDIF( NOT DEFINED OPENCASCADE_WITH_TBB )
IF( NOT DEFINED OPENCASCADE_WITH_GL2PS )
	SET( OPENCASCADE_WITH_GL2PS OFF )
ENDIF( NOT DEFINED OPENCASCADE_WITH_GL2PS )
IF( NOT DEFINED OPENCASCADE_WITH_FREEIMAGE )
	SET( OPENCASCADE_WITH_FREEIMAGE OFF )
ENDIF( NOT DEFINED OPENCASCADE_WITH_FREEIMAGE )
OPTION( OPENCASCADE_WITH_TBB "Build with TBB" ${OPENCASCADE_WITH_TBB} )
OPTION( OPENCASCADE_WITH_GL2PS "Build with GL2PS" ${OPENCASCADE_WITH_GL2PS} )
OPTION( OPENCASCADE_WITH_FREEIMAGE "Build with FreeImage" ${OPENCASCADE_WITH_FREEIMAGE} )

IF( NOT DEFINED OPENCASCADE_INSTALL_PREFIX )
	IF( WIN32 )
		SET(OPENCASCADE_INSTALL_PREFIX
			"c:/OpenCASCADE-${OpenCASCADE_VERSION_MAJOR}.${OpenCASCADE_VERSION_MINOR}.${OpenCASCADE_VERSION_PATCH}")
	ELSE( WIN32 )
		SET(OPENCASCADE_INSTALL_PREFIX
			"/usr/local")
	ENDIF( WIN32 )
ENDIF( NOT DEFINED OPENCASCADE_INSTALL_PREFIX )

SET( OPENCASCADE_INSTALL_PREFIX ${OPENCASCADE_INSTALL_PREFIX} CACHE
	PATH "Install prefix prepended to target to create install location" )
SET( CMAKE_INSTALL_PREFIX "${OPENCASCADE_INSTALL_PREFIX}" CACHE INTERNAL "Prefix
	prepended to install directories if target destination is not absolute,
	immutable" FORCE )

IF( OPENCASCADE_BUILD_SHARED_LIB )
	SET( OPENCASCADE_LIBRARY_TYPE SHARED )
	SET( OPENCASCADE_INSTALL_TYPE LIBRARY )
	IF( WIN32 )
		SET( OPENCASCADE_INSTALL_TYPE RUNTIME )
	ENDIF( WIN32 )
ELSE( OPENCASCADE_BUILD_SHARED_LIB )
	SET( OPENCASCADE_LIBRARY_TYPE STATIC )
	SET( OPENCASCADE_INSTALL_TYPE ARCHIVE )
	IF ( WIN32 )
		ADD_DEFINITIONS("-DHAVE_NO_DLL")
	ENDIF( WIN32 )
ENDIF( OPENCASCADE_BUILD_SHARED_LIB )

#
# Check components dependencies
#
SET(OPENCASCADE_FOUNDATION TRUE)
IF(OPENCASCADE_DRAW AND NOT OPENCASCADE_DATAEXCHANGE)
	SET(OPENCASCADE_DATAEXCHANGE ON CACHE BOOL "Build data exchange" FORCE)
ENDIF(OPENCASCADE_DRAW AND NOT OPENCASCADE_DATAEXCHANGE)
IF(OPENCASCADE_DATAEXCHANGE AND NOT OPENCASCADE_OCAF)
	SET(OPENCASCADE_OCAF ON CACHE BOOL "Build application framework" FORCE)
ENDIF(OPENCASCADE_DATAEXCHANGE AND NOT OPENCASCADE_OCAF)
IF(OPENCASCADE_OCAF AND NOT OPENCASCADE_VISUALISATION)
	SET(OPENCASCADE_VISUALISATION ON CACHE BOOL "Build visualisation component needed by other modules" FORCE)
ENDIF(OPENCASCADE_OCAF AND NOT OPENCASCADE_VISUALISATION)
IF(OPENCASCADE_VISUALISATION AND NOT OPENCASCADE_MODEL)
	SET(OPENCASCADE_MODEL ON CACHE BOOL "Build model components" FORCE)
ENDIF(OPENCASCADE_VISUALISATION AND NOT OPENCASCADE_MODEL)
IF(OPENCASCADE_VISUALISATION_FULL AND NOT OPENCASCADE_VISUALISATION)
	SET(OPENCASCADE_VISUALISATION ON CACHE BOOL "Build model components needed by other modules" FORCE)
ENDIF(OPENCASCADE_VISUALISATION_FULL AND NOT OPENCASCADE_VISUALISATION)
IF(OPENCASCADE_DRAW AND NOT OPENCASCADE_VISUALISATION_FULL)
	SET(OPENCASCADE_VISUALISATION_FULL ON CACHE BOOL "Build full visualisation component" FORCE)
ENDIF(OPENCASCADE_DRAW AND NOT OPENCASCADE_VISUALISATION_FULL)

SET(INSTALL_RESOURCE_FILES)
FILE(GLOB OS_TCL_SCRIPTS RELATIVE ${OpenCASCADE_SOURCE_DIR} src/OS/*.tcl)
SET(INSTALL_RESOURCE_FILES ${INSTALL_RESOURCE_FILES}
	${OS_TCL_SCRIPTS}
	src/UnitsAPI/Lexi_Expr.dat
	src/UnitsAPI/Units.dat )

FIND_PACKAGE(Threads)
FIND_PATH(TBB_INCLUDE_DIR tbb/tbb.h DOC "Location of header files for TBB (containing tbb/tbb.h)" ${CMAKE_SYSTEM_INCLUDE_PATH})
IF(TBB_INCLUDE_DIR)
	FIND_LIBRARY( TBB_LIBRARY tbb "Path to the TBB library" )
ENDIF(TBB_INCLUDE_DIR)
MARK_AS_ADVANCED(TBB_INCLUDE_DIR TBB_LIBRARY)


IF(OPENCASCADE_VISUALISATION AND OPENCASCADE_WITH_FREEIMAGE)
	FIND_PATH(FREEIMAGE_INCLUDE_DIR FreeImagePlus.h DOC "Location of header files for FreeImage" ${CMAKE_SYSTEM_INCLUDE_PATH})
	IF(FREEIMAGE_INCLUDE_DIR)
		FIND_LIBRARY( FREEIMAGE_LIBRARY freeimageplus "Path to the freeimage library" )
	ENDIF(FREEIMAGE_INCLUDE_DIR)
	MARK_AS_ADVANCED(FREEIMAGE_INCLUDE_DIR FREEIMAGE_LIBRARY)
ENDIF(OPENCASCADE_VISUALISATION AND OPENCASCADE_WITH_FREEIMAGE)

#
# X11 is needed on Unix to compile OSD/OSD_FontMgr.cxx
#
IF (NOT WIN32)
	FIND_PACKAGE(X11 REQUIRED)
ENDIF (NOT WIN32)

IF(OPENCASCADE_VISUALISATION_FULL)
	FIND_LIBRARY( X11_Xmu_LIB Xmu PATHS /usr/openwin/lib )
	FIND_PACKAGE(OpenGL REQUIRED)
	FIND_PACKAGE(Freetype REQUIRED)
	FIND_PATH(FTGL_V212_INCLUDE_DIR FTGL/FTFace.h DOC "Location of header files for FTGL 2.1.2" ${CMAKE_SYSTEM_INCLUDE_PATH})
	FIND_PATH(FTGL_INCLUDE_DIR FTGL/ftgl.h "Location of header files for FTGL > 2.1.2" ${CMAKE_SYSTEM_INCLUDE_PATH})
	IF(NOT FTGL_V212_INCLUDE_DIR AND FTGL_INCLUDE_DIR)
		ADD_DEFINITIONS(-DHAVE_FTGL_NEWER212)
	ENDIF(NOT FTGL_V212_INCLUDE_DIR AND FTGL_INCLUDE_DIR)
	FIND_LIBRARY(FTGL_LIBRARY ftgl "Location of ftgl library (any version)")
	FIND_PATH(GL2PS_INCLUDE_DIR gl2ps.h DOC "Location of header files for GL2PS (containing gl2ps.h)" ${CMAKE_SYSTEM_INCLUDE_PATH})
	IF(GL2PS_INCLUDE_DIR)
		FIND_LIBRARY( GL2PS_LIBRARY gl2ps "Path to the gl2ps library" )
	ENDIF(GL2PS_INCLUDE_DIR)
	MARK_AS_ADVANCED(X11_Xmu_LIB FTGL_V212_INCLUDE_DIR FTGL_INCLUDE_DIR FTGL_LIBRARY GL2PS_INCLUDE_DIR GL2PS_LIBRARY)

	MESSAGE(STATUS "X11 LIBS: ${X11_LIBRARIES}")
	MESSAGE(STATUS "OPENGL LIBS: ${OPENGL_LIBRARIES}")
	MESSAGE(STATUS "FREETYPE LIBS: ${FREETYPE_LIBRARIES}")
	MESSAGE(STATUS "FREETYPE INCLUDES: ${FREETYPE_INCLUDE_DIRS}")
	MESSAGE(STATUS "THREAD LIB??: ${CMAKE_THREAD_LIBS_INIT}")

	FILE(GLOB TEXTURES_RGB_FILES RELATIVE ${OpenCASCADE_SOURCE_DIR} src/Textures/*.rgb)
	FILE(GLOB FONTMFT_MFT_FILES RELATIVE ${OpenCASCADE_SOURCE_DIR} src/FontMFT/*.mft)
	SET(INSTALL_RESOURCE_FILES ${INSTALL_RESOURCE_FILES} ${FONTMFT_MFT_FILES} ${TEXTURES_RGB_FILES})
ENDIF(OPENCASCADE_VISUALISATION_FULL)

IF(OPENCASCADE_OCAF)
	FILE(GLOB XMLOCAFRESOURCE_XSD_FILES RELATIVE ${OpenCASCADE_SOURCE_DIR} src/XmlOcafResource/*.xsd)
	SET(INSTALL_RESOURCE_FILES ${INSTALL_RESOURCE_FILES}
		${XMLOCAFRESOURCE_XSD_FILES}
		src/StdResource/MDTV-Standard.xwd
		src/StdResource/Plugin
		src/StdResource/Standard
		src/StdResource/Standard.us
		src/StdResource/StandardLite
		src/StdResource/TObj
		src/StdResource/XCAF
		src/StdResource/dftree.tcl )
ENDIF(OPENCASCADE_OCAF)

IF(OPENCASCADE_DATAEXCHANGE)
	SET(INSTALL_RESOURCE_FILES ${INSTALL_RESOURCE_FILES}
		src/SHMessage/SHAPE.fr
		src/SHMessage/SHAPE.us
		src/XSMessage/IGES.fr
		src/XSMessage/IGES.us
		src/XSMessage/XSTEP.fr
		src/XSMessage/XSTEP.us
		src/XSTEPResource/IGES
		src/XSTEPResource/STEP )
ENDIF(OPENCASCADE_DATAEXCHANGE)

IF(OPENCASCADE_DRAW)
	FIND_PACKAGE(TCL REQUIRED)
	FILE(GLOB DRAWRESOURCES_TCL_FILES RELATIVE ${OpenCASCADE_SOURCE_DIR} src/DrawResources/*.tcl)
	SET(INSTALL_RESOURCE_FILES ${INSTALL_RESOURCE_FILES}
		${DRAWRESOURCES_TCL_FILES}
		src/DrawResources/DRAW.doc
		src/DrawResources/DRAW.info
		src/DrawResources/DrawDefault
		src/DrawResources/DrawPlugin
		src/DrawResources/demo
		src/DrawResources/demo.bat
		src/DrawResources/idoc
		src/DrawResources/lamp.ico
		src/DrawResources/mdltest
		src/DrawResources/mkdoc
		src/DrawResources/tdoc
		src/DrawResources/test2xl
		src/DrawResources/vmdltest
		src/DrawResources/wing.brep )
ENDIF(OPENCASCADE_DRAW)

SET( CMAKE_DEBUG_POSTFIX "d" )

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}/inc
	${CMAKE_CURRENT_SOURCE_DIR}/inc)

###################################
# Architecture-specific libraries #
###################################
IF(WIN32)
	SET(LM)
	SET(CSF_gdi32_LIB gdi32)
	SET(CSF_advapi32_LIB advapi32)
	SET(CSF_user32_LIB user32)
	SET(CSF_kernel32_LIB kernel32)
	SET(CSF_SOCKETLibs_LIB ws2_32)
	SET(CSF_wsock32_LIB ws2_32)
ELSE(WIN32)
	SET(LM "-lm")
	SET(WIN32_LIBS "")
	SET(CSF_gdi32_LIB "")
	SET(CSF_advapi32_LIB "")
	SET(CSF_user32_LIB "")
	SET(CSF_kernel32_LIB "")
	SET(CSF_SOCKETLibs_LIB "")
	SET(CSF_wsock32_LIB "")
ENDIF(WIN32)

###################################################
# Check required headers, functions and libraries #
###################################################
IF (NOT WIN32)
    # Check headers
    # I think these should all be check cxx headers, as I think there is no c
    # compilation anywhere in OpenCASCADE
    INCLUDE(CheckIncludeFile)
    #INCLUDE(CheckIncludeFiles)
    CHECK_INCLUDE_FILE(alloca.h HAVE_ALLOCA_H)
    CHECK_INCLUDE_FILE(dlfcn.h HAVE_DLFCN_H)
    CHECK_INCLUDE_FILE(dl.h HAVE_DL_H)
    CHECK_INCLUDE_FILE(ieeefp.h HAVE_IEEEFP_H)
    CHECK_INCLUDE_FILE(time.h HAVE_TIME_H)
    CHECK_INCLUDE_FILE(sys/time.h HAVE_SYS_TIME_H)
    CHECK_INCLUDE_FILE(pwd.h HAVE_PWD_H)
    CHECK_INCLUDE_FILE(sys/statvfs.h HAVE_SYS_STATVFS_H)
    CHECK_INCLUDE_FILE(sys/vfs.h HAVE_SYS_VFS_H)
    CHECK_INCLUDE_FILE(sys/param.h HAVE_SYS_PARAM_H)
    CHECK_INCLUDE_FILE(osfcn.h HAVE_OSFCN_H)
    CHECK_INCLUDE_FILE(netdb.h HAVE_NETDB_H)
    CHECK_INCLUDE_FILE(sys/ioctl.h HAVE_SYS_IOCTL_H)
    CHECK_INCLUDE_FILE(net/if.h HAVE_NET_IF_H)
    CHECK_INCLUDE_FILE(sys/systeminfo.h HAVE_SYS_SYSTEMINFO_H)
    CHECK_INCLUDE_FILE(sys/utsname.h HAVE_SYS_UTSNAME_H)
    CHECK_INCLUDE_FILE(sysent.h HAVE_SYSENT_H)
    CHECK_INCLUDE_FILE(unistd.h HAVE_UNISTD_H)
    CHECK_INCLUDE_FILE(sys/unistd.h HAVE_SYS_UNISTD_H)
    CHECK_INCLUDE_FILE(sys/socket.h HAVE_SYS_SOCKET_H)
    CHECK_INCLUDE_FILE(ndir.h HAVE_NDIR_H)
    CHECK_INCLUDE_FILE(sys/ndir.h HAVE_SYS_NDIR_H)
    CHECK_INCLUDE_FILE(dir.h HAVE_DIR_H)
    CHECK_INCLUDE_FILE(signal.h HAVE_SIGNAL_H)
    CHECK_INCLUDE_FILE(sys/signal.h HAVE_SYS_SIGNAL_H)
    CHECK_INCLUDE_FILE(sigfpe.h HAVE_SIGFPE_H)
    CHECK_INCLUDE_FILE(floatingpoint.h HAVE_FLOATINGPOINT_H)
    CHECK_INCLUDE_FILE(sys/machsig.h HAVE_SYS_MACHSIG_H)
    CHECK_INCLUDE_FILE(sys/siginfo.h HAVE_SYS_SIGINFO_H)
    CHECK_INCLUDE_FILE(malloc.h HAVE_MALLOC_H)
    CHECK_INCLUDE_FILE(strings.h HAVE_STRINGS_H)
    CHECK_INCLUDE_FILE(sys/stat.h HAVE_SYS_STAT_H)
    CHECK_INCLUDE_FILE(sys/sem.h HAVE_SYS_SEM_H)
    CHECK_INCLUDE_FILE(sys/ipc.h HAVE_SYS_IPC_H)
    CHECK_INCLUDE_FILE(sys/times.h HAVE_SYS_TIMES_H)
    CHECK_INCLUDE_FILE(dirent.h HAVE_DIRENT_H)
    CHECK_INCLUDE_FILE(getopt.h HAVE_GETOPT_H)
    CHECK_INCLUDE_FILE(sys/vnode.h HAVE_SYS_VNODE_H)
    INCLUDE(CheckIncludeFileCXX)
    CHECK_INCLUDE_FILE_CXX(float.h HAVE_FLOAT_H)
    CHECK_INCLUDE_FILE_CXX(iomanip.h HAVE_IOMANIP_H)
    CHECK_INCLUDE_FILE_CXX(limits.h HAVE_LIMITS_H)
    CHECK_INCLUDE_FILE_CXX(values.h HAVE_VALUES_H)
    CHECK_INCLUDE_FILE_CXX(istream HAVE_ISTREAM)
    CHECK_INCLUDE_FILE_CXX(ostream HAVE_OSTREAM)
    CHECK_INCLUDE_FILE_CXX(fstream HAVE_FSTREAM)
    CHECK_INCLUDE_FILE_CXX(ios HAVE_IOS)
    CHECK_INCLUDE_FILE_CXX(iomanip HAVE_IOMANIP)
    CHECK_INCLUDE_FILE_CXX(iostream HAVE_IOSTREAM)
    CHECK_INCLUDE_FILE_CXX(stream.h HAVE_STREAM_H)
    CHECK_INCLUDE_FILE_CXX(strstream.h HAVE_STRSTREAM_H)
    CHECK_INCLUDE_FILE_CXX(istream.h HAVE_ISTREAM_H)
    CHECK_INCLUDE_FILE_CXX(ostream.h HAVE_OSTREAM_H)
    CHECK_INCLUDE_FILE_CXX(fstream.h HAVE_FSTREAM)
    CHECK_INCLUDE_FILE_CXX(iostream.h HAVE_IOSTREAM_H)
    CHECK_INCLUDE_FILE_CXX(stdlib.h HAVE_STDLIB_H)
    CHECK_INCLUDE_FILE_CXX(siginfo.h HAVE_SIGINFO_H)
    CHECK_INCLUDE_FILE_CXX(bits/sigset.h HAVE_BITS_SIGSET_H)
    CHECK_INCLUDE_FILE_CXX(bstring.h HAVE_BSTRING_H)
    CHECK_INCLUDE_FILE_CXX(sys/types.h HAVE_SYS_TYPES_H)
    CHECK_INCLUDE_FILE_CXX(sys/select.h HAVE_SYS_SELECT_H)
    CHECK_INCLUDE_FILE_CXX(X11/extensions/transovl.h HAVE_X11_EXTENSIONS_TRANSOVL_H)
    CHECK_INCLUDE_FILE_CXX(X11/extensions/readdisplay.h HAVE_X11_EXTENSIONS_READDISPLAY_H)
    CHECK_INCLUDE_FILE_CXX(X11/extensions/multibuf.h HAVE_X11_EXTENSIONS_MULTIBUF_H)
    CHECK_INCLUDE_FILE_CXX(sys/filio.h HAVE_SYS_FILIO_H)
    CHECK_INCLUDE_FILE_CXX(sys/mman.h HAVE_SYS_MMAN_H)
    CHECK_INCLUDE_FILE_CXX(libc.h HAVE_LIBC_H)
    # Check library functions
    INCLUDE(CheckFunctionExists)
    CHECK_FUNCTION_EXISTS(alloca HAVE_ALLOCA)
    CHECK_FUNCTION_EXISTS(memcmp HAVE_MEMCMP)
    CHECK_FUNCTION_EXISTS(signal HAVE_SIGNAL)
    CHECK_FUNCTION_EXISTS(gethostname HAVE_GETHOSTNAME)
    CHECK_FUNCTION_EXISTS(putenv HAVE_PUTENV)
    CHECK_FUNCTION_EXISTS(re_comp HAVE_RE_COMP)
    CHECK_FUNCTION_EXISTS(regcomp HAVE_REGCOMP)
    CHECK_FUNCTION_EXISTS(strcspn HAVE_STRCSPN)
    CHECK_FUNCTION_EXISTS(strdup HAVE_STRDUP)
    CHECK_FUNCTION_EXISTS(strtol HAVE_STRTOL)
    CHECK_FUNCTION_EXISTS(statfs HAVE_STATFS)
    CHECK_FUNCTION_EXISTS(statvfs HAVE_STATVFS)
    CHECK_FUNCTION_EXISTS(finite HAVE_FINITE)
    CHECK_FUNCTION_EXISTS(mallinfo HAVE_MALLINFO)
    SET(CMAKE_REQUIRED_LIBRARIES sunmath)
    CHECK_FUNCTION_EXISTS(ieee_handler HAVE_SUNMATH)
    SET(CMAKE_REQUIRED_LIBRARIES)
    SET(RETSIGTYPE void) # Don't know how to figure this out yet
    INCLUDE(CheckTypeSize)
    SET(CMAKE_EXTRA_INCLUDE_FILES sys/time.h)
    CHECK_TYPE_SIZE(tm TM_IN_SYS_TIME)
    SET(CMAKE_EXTRA_INCLUDE_FILES) 
    INCLUDE (CheckCSourceCompiles)
    CHECK_C_SOURCE_COMPILES("
    #include <sys/time.h>
    #include <sys/sem.h>
    int main(){union semun c;return 0;}
    "
    SEMUN_DEFINED)
    IF (SEMUN_DEFINED)
    	CHECK_C_SOURCE_COMPILES("
    	#include <sys/time.h>
    	#include <sys/sem.h>
    	int main(){union semun c;c.__buf = 0;return 0;}
    	"
    	SEMUN_BUF_DEFINED)
    ENDIF (SEMUN_DEFINED)
    CHECK_C_SOURCE_COMPILES("
    #include <sys/sem.h>
    static struct sembuf event_flag;
    int main(){int status; int *semid;status = semop(*semid,event_flag,1);return 0;}
    "
    SEMOP_NO_REFERENCE)

    CHECK_C_SOURCE_COMPILES("
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

    INCLUDE (CheckCXXSourceCompiles)
    CHECK_CXX_SOURCE_COMPILES("
    #include <ios>
    int main(){static const int input = (std::ios::in)|(std::ios::nocreate);
    static const int output = (std::ios::out);return 0;}
    "
    DEF_IOS_OK)
    CHECK_CXX_SOURCE_COMPILES("
    #include <sys/types.h>
    size_t a;
    int main(){return 0;}
    "
    SYS_TYPES_DEFINES_SIZE_T)
    IF(NOT SYS_TYPES_DEFINES_SIZE_T)
	SET(SYS_TYPES_DEFINES_SIZE_T 0)
    ENDIF(NOT SYS_TYPES_DEFINES_SIZE_T)
    CHECK_CXX_SOURCE_COMPILES("
    #include <iostream>
    int main(){std::cout << std::cout.form(\"%9.3e\", 3.14159627e-4) << std::endl;return 0;}
    "
    OSTREAM_FORM_OK)	
    INCLUDE(TestBigEndian)
    TEST_BIG_ENDIAN(WORDS_BIGENDIAN)
    SET(STDC_HEADERS TRUE) # Only for really old systems, being lazy
    SET(STACK_DIRECTION 0) # Don't have a test for this, TODO?


# TODO: check all headers/functions/libraries that are checked in configure.ac original OCC script
# TODO: generate the config.h file from these checks
ENDIF(NOT WIN32)

CONFIGURE_FILE( ${CMAKE_CURRENT_SOURCE_DIR}/oce_config.h.cmake
	${CMAKE_CURRENT_BINARY_DIR}/inc/config.h )

############################
# Check 32/64 bit platform #
############################
IF (${CMAKE_SIZEOF_VOID_P} MATCHES "8") # It is 64bit, otherwise 32 bit systems match 4
	SET(OPENCASCADE_64BIT ON CACHE BOOL "Build 64bit libraries")
ELSE (${CMAKE_SIZEOF_VOID_P} MATCHES "8")
	SET(OPENCASCADE_64BIT OFF CACHE BOOL "Build 64bit libraries")
ENDIF(${CMAKE_SIZEOF_VOID_P} MATCHES "8")

IF (OPENCASCADE_64BIT)
	ADD_DEFINITIONS(-D_OCC64)
	
	IF (NOT MSVC)
    SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -m64)
  ENDIF(NOT MSVC)
  
	MESSAGE(STATUS "Build 64bit")
	SET(MODE "64bit")
	SET(BIT 64)
ELSE (OPENCASCADE_64BIT)
	MESSAGE(STATUS "Build 32bit")
	SET(BIT 32)
ENDIF (OPENCASCADE_64BIT)

#######################################################
# Check platforms - Define specific compilation flags #
#######################################################
IF(UNIX)
  IF(APPLE)
    ######### MacOSX ###########
    MESSAGE(STATUS "MacOSX platform detected")
    SET(PLATFORM Darwin)
  ELSE(APPLE)
    ######### Unix/Linux ###########
    MESSAGE(STATUS "Unix/Linux platform detected")
    SET(PLATFORM Unix)
  ENDIF(APPLE)
  ADD_DEFINITIONS(-DHAVE_CONFIG_H -DCSFDB -DLIN -DOCC_CONVERT_SIGNALS)
ELSE(UNIX)
  IF(WIN32)
    ######### Windows ###########
    MESSAGE(STATUS "Windows system detected")
    ADD_DEFINITIONS(-DWNT -DWIN32 -D_WINDOWS -DCSFDB)
    SET(PLATFORM win)
  ELSE(WIN32)
    MESSAGE(STATUS "Unknown platform")
  ENDIF(WIN32)
ENDIF(UNIX)
# TODO: better detection of different Unices (Linux, Solaris etc.)
# TODO: add CXX compiler flags for each platform

################################################
# Define output path for generated libraries:  #
# platform/compiler-build_type-bits           #
# for instance:                                #
#     ./win32/bin/vc7.1-release-64             #
#     ./win32/bin/vc9-debug-32                 #
#     ./Unix/i386-debug-64                      #
################################################
IF(WIN32)
    IF(${MSVC}) # The compiler used is MSVC
        MESSAGE(STATUS "Found MSVC compiler: ${MSVC} ${MSVC_VERSION}")
        SET(LIBRARY_OUTPUT_PATH win${BIT}/${MSVC_VERSION}-${CMAKE_BUILD_TYPE}/bin)
    ELSE(${MSVC})
        SET(LIBRARY_OUTPUT_PATH win${BIT}/bin/${CMAKE_BUILD_TYPE})
    ENDIF(${MSVC})
ELSE(WIN32)
    SET(LIBRARY_OUTPUT_PATH ${PLATFORM}/${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_BUILD_TYPE}-${BIT})
ENDIF(WIN32)
MESSAGE(STATUS "output_path: ${LIBRARY_OUTPUT_PATH}")
# TODO: under win32/64, dlls and libs should not be in the same path

IF(MINGW)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mthreads")
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mthreads")
	SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mthreads -Wl,--export-all-symbols")
	SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -mthreads -Wl,--export-all-symbols")
	# For the file Message_MsgFile.cxx of TKernel we must additionally set the __TCollection_DLL define to resolve the needed HashCode() method
	SET_SOURCE_FILES_PROPERTIES("src/Message/Message_MsgFile.cxx" PROPERTIES COMPILE_FLAGS "-D__Message_DLL -D__TCollection_DLL")
ENDIF(MINGW)

# Libraries are installed by default in /usr/local/lib on UNIX
# based platforms and c:/OpenCASCADE-6.5.0/lib on windows based
# platforms
SET(OpenCASCADE_INSTALL_BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)
SET(OpenCASCADE_INSTALL_LIB_DIR ${CMAKE_INSTALL_PREFIX}/lib)
SET(OpenCASCADE_INSTALL_PACKAGE_LIB_DIR ${CMAKE_INSTALL_PREFIX}/lib/OpenCASCADE)
SET(OpenCASCADE_INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include/OpenCASCADE)
SET(OpenCASCADE_INSTALL_SCRIPT_DIR ${CMAKE_INSTALL_PREFIX}/share/OpenCASCADE)
SET(OpenCASCADE_INSTALL_DATA_DIR ${CMAKE_INSTALL_PREFIX}/share/OpenCASCADE)

FOREACH(RESOURCE_FILE ${INSTALL_RESOURCE_FILES})
        GET_FILENAME_COMPONENT(RESOURCE_PATH ${RESOURCE_FILE} PATH)
        INSTALL(FILES ${RESOURCE_FILE}
                DESTINATION ${OpenCASCADE_INSTALL_DATA_DIR}/${RESOURCE_PATH})
ENDFOREACH(RESOURCE_FILE ${INSTALL_RESOURCE_FILES})

CONFIGURE_FILE( ${OpenCASCADE_SOURCE_DIR}/env.sh.cmake
	${OpenCASCADE_BINARY_DIR}/env.sh @ONLY )
CONFIGURE_FILE( ${OpenCASCADE_SOURCE_DIR}/env.csh.cmake
	${OpenCASCADE_BINARY_DIR}/env.csh @ONLY )

INSTALL(FILES
		${OpenCASCADE_SOURCE_DIR}/env.bat
		${OpenCASCADE_BINARY_DIR}/env.csh
		${OpenCASCADE_BINARY_DIR}/env.sh
		${OpenCASCADE_SOURCE_DIR}/env_build.bat
		${OpenCASCADE_SOURCE_DIR}/msvc.bat
	DESTINATION ${OpenCASCADE_INSTALL_SCRIPT_DIR})

MACRO(PROCESS_OCC_MODULE modules)
	FOREACH(module ${modules})
		SET(TOOLKIT_MODULES "")
		SET(TOOLKIT_DEPENDS "")
		SET(TOOLKIT_INCLUDE_DIRECTORIES "")
		SET(TOOLKIT_LIBS "")
		ADD_SUBDIRECTORY( adm/cmake/${module} )
	ENDFOREACH(module ${modules})
ENDMACRO(PROCESS_OCC_MODULE modules)
####################################################################################
# Process modules of each ToolKit                                                  #
####################################################################################
# Foundation
PROCESS_OCC_MODULE( "TKernel;TKMath;TKAdvTools" )

# Modeling Data
IF (OPENCASCADE_MODEL)
	PROCESS_OCC_MODULE( "TKG2d;TKG3d;TKGeomBase;TKBRep" )
ENDIF (OPENCASCADE_MODEL)

# Modeling Algorithms
IF (OPENCASCADE_MODEL)
	PROCESS_OCC_MODULE( "TKGeomAlgo;TKTopAlgo;TKPrim;TKBO;TKHLR;TKMesh;TKShHealing;TKXMesh;TKBool;TKFillet;TKFeat;TKOffset" )
ENDIF (OPENCASCADE_MODEL)

# Visualisation
IF(OPENCASCADE_VISUALISATION)
	PROCESS_OCC_MODULE( "TKService;TKV2d;TKV3d" )
ENDIF(OPENCASCADE_VISUALISATION)
IF(OPENCASCADE_VISUALISATION_FULL)
	PROCESS_OCC_MODULE( "TKOpenGl;TKMeshVS;TKNIS;TKVoxel" )
ENDIF(OPENCASCADE_VISUALISATION_FULL)

# Application framework
IF(OPENCASCADE_OCAF)
	PROCESS_OCC_MODULE( "TKCDF;PTKernel;TKLCAF;FWOSPlugin;TKPShape;TKCAF;TKBinL;TKXmlL;TKPLCAF;TKTObj;TKShapeSchema;TKBin;TKXml;TKPCAF;TKBinTObj;TKXmlTObj;TKStdLSchema;TKStdSchema" )
ENDIF(OPENCASCADE_OCAF)

# Data exchange
IF(OPENCASCADE_DATAEXCHANGE)
	PROCESS_OCC_MODULE( "TKVRML;TKXCAF;TKSTL;TKXSBase;TKXCAFSchema;TKXmlXCAF;TKBinXCAF;TKSTEPBase;TKIGES;TKSTEPAttr;TKSTEP209;TKXDEIGES;TKSTEP;TKXDESTEP" )
ENDIF(OPENCASCADE_DATAEXCHANGE)

# Draw
IF(OPENCASCADE_DRAW)
	PROCESS_OCC_MODULE( "TKDraw;TKTopTest;TKViewerTest;TKXSDRAW;TKDCAF;TKXDEDRAW;TKTObjDRAW" )
ENDIF(OPENCASCADE_DRAW)

# DRAWEXE application
IF(OPENCASCADE_DRAW)
	PROCESS_OCC_MODULE( DRAWEXE )
ENDIF(OPENCASCADE_DRAW)

