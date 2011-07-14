set(TOOLKIT TKernel)

set(TOOLKIT_MODULES
	FSD
	MMgt
	OSD
	Plugin
	Quantity
	Resource
	SortTools
	Standard
	StdFail
	Storage
	TColStd
	TCollection
	TShort
	Units
	UnitsAPI
	IncludeLibrary
	Dico
	NCollection
	Message
)
if(CMAKE_THREAD_LIBS_INIT)
	set(TOOLKIT_LIBS ${CMAKE_THREAD_LIBS_INIT})
endif(CMAKE_THREAD_LIBS_INIT)
set(TOOLKIT_LIBS ${TOOLKIT_LIBS} ${CMAKE_DL_LIBS} ${LM})
if(WIN32)
	set(TOOLKIT_LIBS ${TOOLKIT_LIBS} ${CSF_SOCKETLibs_LIB} ${CSF_advapi32_LIB} ${CSF_gdi32_LIB} ${CSF_user32_LIB} ${CSF_kernel32_LIB} ${CSF_psapi_LIB})
else(WIN32)
	#  An implementation for Mac OS X has been added in src/OSD/gettime_osx.h
	if(NOT APPLE)
		include( CheckFunctionExists )
		check_function_exists( clock_gettime CLOCK_GETTIME_IN_LIBC )
		if(NOT CLOCK_GETTIME_IN_LIBC)
			include( CheckLibraryExists )
			check_library_exists(rt clock_gettime "" CLOCK_GETTIME_IN_LIBRT)
			if(NOT CLOCK_GETTIME_IN_LIBRT)
				message(FATAL_ERROR "Could not find clock_gettime.")
			endif(NOT CLOCK_GETTIME_IN_LIBRT)
			set(TOOLKIT_LIBS ${TOOLKIT_LIBS} rt)
		endif(NOT CLOCK_GETTIME_IN_LIBC)
	endif(NOT APPLE)
endif(WIN32)

# Adde-DHAVE_TBB in TKernel in order to benefit from Standard_MMgrTBBalloc
if(OCE_TBB_MALLOC_SUPPORT AND TBB_INCLUDE_DIR AND TBB_MALLOC_LIBRARY)
	add_definitions(-DHAVE_TBB)
	set(TOOLKIT_INCLUDE_DIRECTORIES ${TBB_INCLUDE_DIR})
	if(CMAKE_CONFIGURATION_TYPES OR NMAKE)
		set(TOOLKIT_LIBS_DEBUG ${TOOLKIT_LIBS_DEBUG} ${TBB_MALLOC_LIBRARY_DEBUG})
		set(TOOLKIT_LIBS_OPTIMIZED ${TOOLKIT_LIBS_OPTIMIZED} ${TBB_MALLOC_LIBRARY})
	else(CMAKE_CONFIGURATION_TYPES OR NMAKE)
		set(TOOLKIT_LIBS ${TOOLKIT_LIBS} ${TBB_MALLOC_LIBRARY})
	endif(CMAKE_CONFIGURATION_TYPES OR NMAKE)
endif(OCE_TBB_MALLOC_SUPPORT AND TBB_INCLUDE_DIR AND TBB_MALLOC_LIBRARY)

include(../BuildToolkit.cmake)

# Modules are dlopen'd by OSD_SharedLibrary::DlOpen.  ELF libraries may
# contain either RPATH or RUNPATH sections to have default library paths.
# RPATH is transitive, so DRAWEXE's RPATH will be used when loading modules.
# But the new RUNPATH is not transitive, thus TKernel must contain a RUNPATH
# section pointing to the right location.
# The problem is that TKernel does not depend on any other built modules,
# so CMake won't add it automatically.  We have to force CMake to add this
# section, hence the BUILD_WITH_INSTALL_RPATH property.
# This is harmless on non-ELF platforms.
if (OCE_BUILD_TKERNEL_WITH_INSTALL_RPATH)
	set_target_properties_install_rpath(${TOOLKIT} "${OCE_INSTALL_LIB_DIR_RPATH};${OCE_INSTALL_PACKAGE_LIB_DIR_RPATH}")
	set_target_properties(${TOOLKIT} PROPERTIES BUILD_WITH_INSTALL_RPATH ON)
endif ()

